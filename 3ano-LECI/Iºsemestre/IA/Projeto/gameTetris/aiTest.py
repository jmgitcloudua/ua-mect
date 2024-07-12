from enum import Enum
from random import Random
from game import *
import math
from threading import Lock

class Bitmap:
    """
    Base class for classes that store information about cells.
    """

    cells = None

    def collides(self, other):
        return any(cell in other for cell in self)

    def __iter__(self):
        return iter(self.cells)

    def __contains__(self, cell):
        return cell in self.cells
class Board(Bitmap):
    """
    Class that keeps track of occupied cells and the current falling block,
    as well as the score of the player. Can be used to duplicate the current
    state and explore possible future moves.
    """

    width = None
    height = None
    score = None
    lock = None

    falling = None
    next = None

    players_turn = None

    def __init__(self, width, height, score=0):
        self.width = width
        self.height = height
        self.score = score
        self.cells = set()
        self.cellcolor = {}
        self.lock = Lock()

    def line_full(self, line):
        """
        Checks if the given line is fully occupied by cells.
        """

        return all((x, line) in self for x in range(0, self.width))

    def remove_line(self, line):
        """
        Removes all blocks on a given line and moves down all blocks above.
        """

        self.cellcolor = {
            (x, y) if y > line else (x, y+1): c
            for (x, y), c in self.cellcolor.items() if y != line
        }

        self.cells = {
            (x, y) if y > line else (x, y+1)
            for (x, y) in self if y != line
        }

    def clean(self):
        """
        Cleans all fully occupied lines from the bottom down, and moves lines
        above the cleaned lines down as well.
        """

        scores = [0, 100, 400, 800, 1600]
        removed = 0

        line = self.height-1
        while line > 0:
            while self.line_full(line):
                self.remove_line(line)
                removed += 1
            line -= 1

        return scores[removed]

    @property
    def alive(self):
        """
        Checks if the falling block has collided with another existing block.
        If this is true, then the game is over.
        """

        with self.lock:
            return self.falling is None or not self.falling.collides(self)

    def place_next_block(self):
        # The next block is now falling
        self.falling = self.next

        # Place the next block, if it exists.
        if self.falling is not None:
            self.falling.initialize(self)

        self.next = None

    def run_adversary(self, adversary):
        """
        Asks the adversary for a new block and places it on the board. Returns
        the shape of the newly placed block.
        """

        # Ask the adversary for a new next block.
        self.next = self.Block(adversary.choose_block(self))
        return self.next.shape

    def run_player(self, player):
        """
        Asks the player for the next action and executes that on the board.
        Returns a tuple of a boolean and the move made, where the boolean
        indicates whether or not the current block has dropped.
        """

        while True:
            actions = player.choose_action(self.clone())

            try:
                actions = iter(actions)
            except TypeError:
                # We were given a single move.
                actions = [actions]

            landed = False
            for action in actions:
                if action is None:
                    landed = self.skip()
                if isinstance(action, Direction):
                    landed = self.move(action)
                elif isinstance(action, Rotation):
                    landed = self.rotate(action)

                yield action

                if landed:
                    return

    def run(self, player, adversary):
        """
        Run the game with the given adversary and player. Will yield control
        back to the calling function every time a move has been made. Yields
        shapes (of new blocks) and moves (directions/rotations) as produced
        by the adversary or the player respectively.
        """

        # Initialize by choosing the "next" block first.
        yield self.run_adversary(adversary)

        # Place this block on the board
        self.place_next_block()

        while True:
            # The adversary can now choose a new next block.
            yield self.run_adversary(adversary)

            # The block may have caused the end of the game.
            if not self.alive:
                return

            # Ask the player for the next move(s) to make.
            yield from self.run_player(player)

    def land_block(self):
        # A fallen block becomes part of the cells on the board.
        self.cells |= self.falling.cells
        for pos in self.falling.cells:
            self.cellcolor[pos] = self.falling.color
        self.falling = None

        # Clean up any completed rows and adjust score.
        self.score += self.clean()

        self.place_next_block()

    def move(self, direction):
        """
        Moves the current block in the direction given, and applies the
        implicit move down as well. Returns True if either this move or the
        subsequent move down caused the block to be dropped, False otherwise.
        """

        """ if self.falling is None:
            raise NoBlockException """

        with self.lock:
            if self.move(direction):
                self.land_block()
                return True

            # Block has not fallen yet; apply the implicit move down.
            if self.falling.move(Direction.Down, self):
                self.land_block()
                return True
            else:
                return False

    def rotate(self, rotation):
        """
        Rotates the current block as requested, and applies the implicit move
        down as well. Returns True if the subsequent move down caused the block
        to be dropped, False otherwise.
        """

        if self.falling is None:
            raise NoBlockException

        with self.lock:
            self.falling.rotate(rotation, self)

            # Apply the implicit move down.
            if self.falling.move(Direction.Down, self):
                self.land_block()
                return True
            else:
                return False

    def skip(self):
        """
        Skips the current turn, and applies the implicit move down. Returns
        True if this move caused the block to be dropped, False otherwise.
        """

        if self.falling is None:
            raise NoBlockException

        with self.lock:
            res = self.falling.move(Direction.Down, self)
            if res:
                self.land_block()
            return res

    def clone(self):
        """
        Creates a copy of the board; can be used to simulate possible moves.
        """

        board = Board(self.width, self.height, self.score)
        board.cells = set(self)

        # Copy the falling block, if any.
        if self.falling is not None:
            board.falling = self.falling.clone()

        # Copy the next block, if any.
        if self.next is not None:
            board.next = self.next.clone()

        return board

class Direction(Enum):
    """
    Possible directions to move a block, plus dropping.
    """

    Left = 'LEFT'
    Right = 'RIGHT'
    Down = 'DOWN'
    Drop = 'DROP'


class Rotation(Enum):
    """
    Possible rotations available to the player.
    """

    Clockwise = 'CLOCKWISE'
    Anticlockwise = 'ANTICLOCKWISE'

class UnknownInstructionException(Exception):
    pass


class BlockLimitException(Exception):
    pass


class NoBlockException(Exception):
    def __init__(self):
        super().__init__("This board has no block to manipulate.")

class Position:
    x = None
    y = None

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y




class Player:
    def __init__(self,seed=None):
        self.random = Random(seed)
        self.best_position = 0
        self.best_rotation = 0
        self.total_score = 0

        #Weighting
        # self.holes_weight = -0.35663
        # self.smoothness_weight = -0.184483
        # self.complete_lines_weight = 0.76066
        # self.aggregateHeight_weight = -0.510066

        # self.holes_weight = -0.401
        # self.smoothness_weight = -0.100
        # self.complete_lines_weight = 0.5
        # self.aggregateHeight_weight = -0.400
        self.holes_weight = -0.40000001
        self.smoothness_weight = -0.100000000
        self.complete_lines_weight = 0.5
        self.aggregateHeight_weight = -0.400000000
        
    def calculate_aggregate_height(self,board):
        #Sum of the height of each column defined as the distance from
        #the top tile to the bottom tile
        column_height = []
        for column in range(board.width):
            for row in range(board.height):
            #Append to height for each row and column that is filled with a block
                if (column,row) in board.cells:
                    column_height.append(board.height-row)
                    break
                #Edge case
                elif row == board.height - 1 and (row,column) not in board.cells:
                    column_height.append(0)
        return column_height

    def calculate_smoothness(self,height,board):
        #Smoothness is defined by the absolute difference in the heights of 
        #adjacent columns
        smoothness = 0 
        # Iterate through all columns 
        for i in range(0,board.width-1):
            smoothness += abs(height[i] - height[i+1])
        return smoothness
    
    def calculate_complete_lines (self,board):
        #calculate complete lines on the board 
        complete_lines=0
        # for column in range(board.height):
        #     if (board.line_full(column)):
        #         complete_lines +=1
        for row in range(board.height):
            check = True
            for column in range(board.width):
                # Checks if any tile is empty, if so, the line is not complete, break out of loop
                if (row, column) not in board.cells:
                    check = False
                    break
            if check == True:
                complete_lines += 1
        if complete_lines < 0:
            complete_lines = 0
        return complete_lines

    def calculate_holes (self,board):
        # calculates the number of holes, defined as an empty space
        # such that at least one tile in the same column is above it on the board
        holes = 0

        for row in range(board.height):
            for column in range(board.width):
                # Check if for a certain row and column, tile is filled ( != 0 ), but its tile above
                # (row + 1 , column) is empty ( ==0 )
                if(row,column) not in board.cells and (row - 1,column) in board.cells:
                    holes+=1
        return holes

    def find_best_move(self,board):
        best_score = -math.inf
        #Only possible to place blocks in 10 different positions
        for position in range(0,Game(10,30).dimensions.x):
            #Only 3 types of possible rotations
            for rotation in range(0,4):
                # Cloning the board for each iteration
                sandbox = Board(Game(10,30).dimensions.x,Game(10,30).dimensions.y).clone()
                # Moves block in cloned board to its resepctive rotation and position
                # to calculate its score
                for i in range(0,rotation):
                    if sandbox.rotate(Rotation.Clockwise) is True:
                        break;
                if position == 0:
                    for i in range(0,5):
                        if sandbox.move(Direction.Left) is True:
                            break;
                elif position == 1:
                    for i in range(0,4):
                        if sandbox.move(Direction.Left) is True:
                            break;
                elif position == 2:
                    for i in range(0,3):
                        if sandbox.move(Direction.Left) is True:
                            break;
                elif position == 3:
                    for i in range(0,2):
                        if sandbox.move(Direction.Left) is True:
                            break;
                elif position ==4:
                    if sandbox.move(Direction.Left) is True:
                            break;
                elif position ==6:
                    if sandbox.move(Direction.Right) is True:
                            break;
                elif position ==7:
                    for i in range(0,2):
                        if sandbox.move(Direction.Right) is True:
                            break;
                elif position ==8:
                    for i in range(0,3):
                        if sandbox.move(Direction.Right) is True:
                            break;
                elif position ==9:
                    for i in range(0,4):
                        if sandbox.move(Direction.Right) is True:
                            break;
                else:
                    pass

                try:
                    sandbox.move(Direction.Drop)
                except NoBlockException:
                    pass
                
                #Assigns variables to the return value of its function
                #Height
                height = self.calculate_aggregate_height(sandbox)
                total_height = sum(height)
                #Smoothness
                smoothness = self.calculate_smoothness(height,board)
                #Completed Lines
                completeLines = self.calculate_complete_lines(sandbox)
                #Holes
                holes = self.calculate_holes(sandbox)
                #Now, combine scores multiplied by its respective weighting
                total_height_score = total_height * self.aggregateHeight_weight
                smoothness_score = smoothness * self.smoothness_weight
                completeLines_score = completeLines * self.complete_lines_weight
                holes_score = holes * self.holes_weight

                #Then, collate all scores
                self.total_score = total_height_score + smoothness_score + completeLines_score + holes_score
               
                #Update best score each time
                if self.total_score >= best_score:
                    best_score = self.total_score
                    self.best_position = position
                    self.best_rotation = rotation 

        return (self.best_position,self.best_rotation)

    def do_move(self,board,best_position,best_rotation):
            do_move = []
            for i in range(0,best_rotation):
                do_move.append(Rotation.Clockwise)
            if best_position == 0:
                for i in range(0,5):
                    do_move.append(Direction.Left)
            elif best_position == 1:
                for i in range(0,4):
                    do_move.append(Direction.Left)
            elif best_position == 2:
                for i in range(0,3):
                    do_move.append(Direction.Left)
            elif best_position == 3:
                for i in range(0,2):
                    do_move.append(Direction.Left)
            elif best_position == 4:
                do_move.append(Direction.Left)
            elif best_position ==6:
                do_move.append(Direction.Right)
            elif best_position ==7:
                for i in range(0,2):
                    do_move.append(Direction.Right)
            elif best_position ==8:
                for i in range(0,3):
                    do_move.append(Direction.Right)
            elif best_position == 9:
                for i in range(0,4):
                    do_move.append(Direction.Right)
            else:
                pass
            do_move.append(Direction.Drop)
            return do_move

    def choose_action(self, board):
        self.find_best_move(board)
        #Executes the best move 
        return self.do_move(board,self.best_position,self.best_rotation)

class RandomPlayer(Player):
    def __init__(self, seed=None):
        self.random = Random(seed)

    def choose_action(self, board):
        return self.random.choice([
            Direction.Left,
            Direction.Right,
            Direction.Down,
            Rotation.Anticlockwise,
            Rotation.Clockwise,
        ])


SelectedPlayer = Player


def bestPosition(self, piece, game):
        board = Game(10,30)
        bestRotation = -1
        # bestOffset = None
        # bestScore = None
        best_fitness = -9999
        # piece_index = 
        best_piece_index = -1
        best_x = -1
        offsets = board.dimensions

        ## Dá-nos o nº de rotações da peça que está a cair 
        n_rotation = 0 
        for key in rotations:
            x = rotations[key]
            if x[0] == piece:
                n_rotation = len(rotations[key])

        for rotation in range(n_rotation):    #* percorrer a rotação de cada peça 
            for x in range(board.dimensions.x):    #* percorrer cada coluna 
                # pass
                new_board = self.get_future_board_with_piece(board, game, piece, (x, offsets[1]))
                fitness = self.get_fitness_score(new_board)
                if fitness > best_fitness:
                    best_fitness = fitness
                    # best_piece_index = piece_index
                    bestRotation = rotation
                    best_x = x
                ## verficar para cada peça o score 

        for _ in range(bestRotation):
            return "r"
        temp_x = offsets[0]
        while temp_x != best_x:
            direction = 1 if temp_x < best_x else -1
            magnitude = 1 if abs(temp_x - best_x) == 1 else 2
            temp_x += direction * magnitude
            if direction == 1:
                return "d" 
            else: 
                return "a"
        return "s"

        # return ""
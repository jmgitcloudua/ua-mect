def fitness_score(game):
	score = -0.25*get_bumpiness(game) + (0.8*numLines(game))**2 + 0.8*get_hole_count(game) +c*get_hole_count(game)
	return score

def numLines(game):
	lines = 0
	for item, count in sorted(Counter(y for [x,y] in game).most_common()):
		if count == len(bottom) - 2:
			lines += 1
	return lines










def get_fitness_score(game):

    board =Game(10,30)


    game, score_count = get_board_and_lines_cleared(game)
    score = WEIGHT_LINE_CLEARED * score_count
    score += a* sum(get_col_heights(game))
    score += c * get_hole_count(game)
    score += d * get_bumpiness(game)
    return score



# Get height of each column
def get_col_heights(game):
    heights = [0] * Game(10,30).dimensions.x
    cols = list(range(1,9))
    for neg_height, row in enumerate(game):
        for i, val in enumerate(row):
            if val == 0 or i not in cols:
                continue
            heights[i] = Game(10,30).dimensions.y - neg_height
            cols.remove(i)
    return heights


# Count of empty spaces below covers
def get_hole_count(game):
    holes = 0
    cols = [0] * Game(10,30).dimensions.x
    for neg_height, row in enumerate(game):
        height = Game(10,30).dimensions.y - neg_height
        for i, val in enumerate(row):
            if val == 0 and cols[i] > height:
                holes += 1
                continue
            if val != 0 and cols[i] == 0:
                cols[i] = height
    return holes


# Get the unevenness of the board
def get_bumpiness(game):
    bumpiness = 0
    heights = get_col_heights(game)
    for i in range(1, 9):
        bumpiness += abs(heights[i - 1] - heights[i])
    return bumpiness


# Get potential lines cleared
# WARNING: MODIFIES BOARD!!!
def get_board_and_lines_cleared(game):
    score_count = 0
    row = 0
    while True:
        if row >= len(game):
            break
        if 0 in game[row]:
            row += 1
            continue
        # Delete the "filled" row
        del game[row]
        # Insert empty row at top
        game.insert(0, [0] * Game(10,30).dimensions.x)
        score_count += 1
    return game, score_count
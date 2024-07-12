#Victor Souza, 89330
#Dicussed wit Diogo Dias, 85085

from tree_search import *
from cidades import *


class MyNode(SearchNode):
    def __init__(self, state, parent, cost, heuristic=None, arg5=None):
        super().__init__(state, parent)
        self.cost = cost
        self.heuristic = heuristic
        self.eval = round(cost + heuristic)
        self.children = []


class MyTree(SearchTree):

    def __init__(self, problem, strategy='breadth', seed=0):
        super().__init__(problem, strategy, seed)
        root = MyNode(problem.initial, None, 0, problem.domain.heuristic(problem.initial, problem.goal),
                      problem.domain.heuristic(problem.initial, problem.goal))
        self.all_nodes = [root]
        self.solution_tree = None
        self.close_nodes = []
        self.used_shortcuts = []

    def astar_add_to_open(self, lnewnodes):
        self.open_nodes = sorted(
            self.open_nodes+lnewnodes,
            key=lambda id: self.all_nodes[id].cost + self.all_nodes[id].heuristic)

    def propagate_eval_upwards(self, node):
        #IMPLEMENT HERE
        min_eval = None
        for child in node.children:
            if(min_eval == None or child.eval < min_eval):
                min_eval = child.eval

        node.eval = round(min_eval)

        if node.parent != None:
            self.propagate_eval_upwards(self.all_nodes[node.parent])

    def search2(self, atmostonce=False):
        #IMPLEMENT HERE
        if(not atmostonce):
            while self.open_nodes != []:
                nodeID = self.open_nodes.pop(0)
                node = self.all_nodes[nodeID]
                if self.problem.goal_test(node.state):
                    self.solution = node
                    self.terminals = len(self.open_nodes)+1
                    self.solution.cost = node.cost
                    return self.get_path(node)
                lnewnodes = []
                self.non_terminals += 1
                for a in self.problem.domain.actions(node.state):
                    newstate = self.problem.domain.result(node.state, a)
                    if newstate not in self.get_path(node):
                        newnode = MyNode(
                            newstate,
                            nodeID,
                            node.cost +
                            self.problem.domain.cost(node.state, a),
                            self.problem.domain.heuristic(newstate, self.problem.goal))

                        node.children.append(newnode)
                        self.all_nodes.append(newnode)
                        lnewnodes.append(len(self.all_nodes)-1)

                if node.children != []:
                    self.propagate_eval_upwards(node)

                self.add_to_open(lnewnodes)
            return None

        else:
            while self.open_nodes != []:
                nodeID = self.open_nodes.pop(0)
                self.close_nodes.append(nodeID)

                node = self.all_nodes[nodeID]

                if self.problem.goal_test(node.state):
                    self.solution = node
                    self.terminals = len(self.open_nodes)+1
                    self.solution.cost = node.cost
                    return self.get_path(node)
                lnewnodes = []
                self.non_terminals += 1
                for a in self.problem.domain.actions(node.state):
                    newstate = self.problem.domain.result(node.state, a)
                    union = self.open_nodes + self.close_nodes
                    states = []

                    for id_n in union:
                        if(not (self.all_nodes[id_n].state in states)):
                            states.append(self.all_nodes[id_n].state)

                    if (not (newstate in states)):
                        newnode = MyNode(
                            newstate,
                            nodeID,
                            node.cost +
                            self.problem.domain.cost(node.state, a),
                            self.problem.domain.heuristic(newstate, self.problem.goal))
                        node.children.append(newnode)
                        self.all_nodes.append(newnode)
                        lnewnodes.append(len(self.all_nodes)-1)

                    else:
                        best_cost = {'cost': None, 'newnode': False}
                        newnode_cost = node.cost + \
                            self.problem.domain.cost(node.state, a)

                        for id_n2 in union:
                            if (newstate == self.all_nodes[id_n2].state):
                                if (best_cost.get('cost') == None or newnode_cost < best_cost.get('cost')):
                                    best_cost['cost'] = newnode_cost
                                    best_cost['newnode'] = True
                                elif (self.all_nodes[id_n2].cost < best_cost.get('cost')):
                                    best_cost['cost'] = newnode_cost
                                    best_cost['newnode'] = False

                        if best_cost.get('newnode'):
                            newnode = MyNode(
                                newstate,
                                nodeID,
                                node.cost +
                                self.problem.domain.cost(node.state, a),
                                self.problem.domain.heuristic(newstate, self.problem.goal))
                            node.children.append(newnode)
                            self.all_nodes.append(newnode)
                            lnewnodes.append(len(self.all_nodes)-1)

                if node.children != []:
                    self.propagate_eval_upwards(node)

                self.add_to_open(lnewnodes)
            return None

    def repeated_random_depth(self, numattempts=3, atmostonce=False):
        #IMPLEMENT HERE
        min_cost = None

        for i in range(numattempts):
            test_tree = MyTree(self.problem, 'rand_depth', i)
            test_tree.search2()

            if(min_cost == None or test_tree.solution.cost < min_cost):
                self.solution_tree = test_tree
                min_cost = test_tree.solution.cost
                list_states = self.solution_tree.get_path(test_tree.solution)

        return list_states

    def make_shortcuts(self):
        #IMPLEMENT HERE
        first_solution = self.solution
        path = self.get_path(first_solution)

        i = 0
        while i < len(path)-2:
            j = i+2
            actions = self.problem.domain.actions(path[i])
            state = path[j]

            for a in actions:
                if state == self.problem.domain.result(path[i], a):
                    del path[i+1]
                    self.used_shortcuts.append((path[i], path[i+1]))
            i += 1

        return path


class MyCities(Cidades):

    def maximum_tree_size(self, depth):   # assuming there is no loop prevention
        #IMPLEMENT HERE
        cities = [city for city in self.coordinates]
        num_cities = len(cities)
        num_neighbors = len(self.connections)*2
        avg_num = num_neighbors/num_cities

        return ((avg_num**(depth+1)) - 1)/(avg_num - 1)

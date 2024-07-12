#encoding: utf8

from semantic_network import *
from bayes_net import *
from constraintsearch import *

from itertools import product


class MyBN(BayesNet):

    def individual_probabilities(self):
        # IMPLEMENTAR AQUI
        dicts = {}
        for k in self.dependencies.keys():
            dicts[k] = (self.indivProb(k,True))
        return dicts
       
    # auxiliar fucntion
    def indivProb(self, item, value):
        #all_conjunctions = [c for c in self._gen_conjuction(list(self.dependencies.keys())) if (item, value) in c]
        all_conjunctions = [c for c in (list(zip(self.dependencies.keys(), list(line))) for line in (product([True, False], repeat=len(self.dependencies.keys())))) if (item, value) in c]
        return sum([self.jointProb(c) for c in all_conjunctions])
    
    def _gen_conjuctions(self, variables):
        if len(variables) == 1:
            return [[variables[0], True],[variables[0], False]]
        lst = 0
        for c in self._gen_conjuction(variables[1:]):
            lst += (c + [variables[0], True])
            lst += (c + [variables[0], False])
        return lst  
    
    
    """   def indivProb(self,var,val):
        prob = 0
        ancestors = self.conjunction(self.ancestors(var))
        for conj in ancestors:
            prob += self.jointProb(conj + [(var, val)])
        return prob

    def conjunction(self, lvars):
        l = product([True,False], repeat=len(lvars))
        return list(map(lambda c : list(zip(lvars, c)),l))

    def ancestors(self, var):
        lvars = [ v for (v,x) in list(self.dependencies[var].keys())[0] ]
        res = lvars

        for v in lvars:
            res += self.ancestors(v)

        return list(set(res)) """ 



class MySemNet(SemanticNetwork):
    def __init__(self):
        SemanticNetwork.__init__(self)

    def translate_ontology(self):
        #IMPLEMENTAR AQUI
        dicts = {}
        #get all of subtype relation and save in dictionary
        for d in self.declarations:
            if isinstance(d.relation, Subtype):
                if d.relation.entity2 in dicts:
                    if d.relation.entity1 not in dicts[d.relation.entity2]:
                        dicts[d.relation.entity2].append(d.relation.entity1)
                else:
                    dicts[d.relation.entity2] = [d.relation.entity1]
        #sort list with all dic keys
        result = list(dicts.keys())
        result.sort()

        # for each key contrust the solution
        for j in range(len(result)):
            dicts[result[j]].sort()
            word = "Qx "
            for i in range(len(dicts[result[j]])):
                if i != len(dicts[result[j]]) - 1:
                    word += dicts[result[j]][i].capitalize() + "(x) or "
                else:
                    word += dicts[result[j]][i].capitalize() + "(x) => "
            word += result[j].capitalize() +"(x)"
            result[j] = word
        return result


    def query_inherit(self,entity,assoc):
        # IMPLEMENTAR AQUI
        # list to store all inverted declarations
        inv = []
        for d in self.declarations:
            # check if assoc is inverse and if inverse is declared
            if isinstance(d.relation, Association) and d.relation.inverse == assoc:
                if d not in inv and d.relation.entity2 == entity:
                    inv.append(d)
        #get local declaration
        getDecl = [d for d in self.query_local(e1=entity, relname=assoc) if isinstance(d.relation, Association)]
        #list to find inherited declarations
        listParents = [d.relation.entity2 for d in self.query_local(e1=entity) if not isinstance(d.relation, Association)]
        #get inherited declarations
        for p in listParents:
            result = self.query_inherit(p, assoc)
            if result != None:
                getDecl += result

        # if there weren't inverted declarations return local+inherited
        if inv == []:
            return getDecl
        # otherwise return local+inherited
        else:
            return list(set(getDecl + inv))



    def query(self,entity,relname):
        #IMPLEMENTAR AQUI
        # if relation is a member
        if relname == 'member':
            return list(set([d.relation.entity2 for d in self.declarations if isinstance(d.relation, Member) and d.relation.entity1 == entity]))
        #if relation is a subtype
        elif relname =='subtype':
            return list(set([d.relation.entity2 for d in self.declarations if isinstance(d.relation, Subtype) and d.relation.entity1 == entity]))
        else:
            # dictionary used to find the most common propertie
            dicts = {}
            # get all of the associtation with realname
            for d in self.query_local(relname=relname):
                if isinstance(d.relation, Association):
                    if d.relation.assoc_properties() not in dicts:
                        dicts[d.relation.assoc_properties()] = 1
                    else:
                        dicts[d.relation.assoc_properties()] += 1
            #get the most common propertie of the disctionary
            propertie = max(dicts, key=dicts.get)

            #if cardinality is multiple
            if propertie[0] == 'multiple':
                # return process without cancelling
                return list(set([d.relation.entity2 for d in self.query_inherit(entity, relname) if d.relation.assoc_properties() == propertie]))
            #if cardinality is single
            if propertie[0] == 'single':
                #Dictionary to verify the most common declaration
                dicts = {}
                res = []
                #Get the most common declaration for all of those that were declared with the same association in the entity
                for d in [d for d in self.query_local(e1=entity, relname=relname) if isinstance(d.relation, Association) and d.relation.assoc_properties() == propertie]:
                    if d.relation.entity2 in dicts:
                        dicts[d.relation.entity2] +=1
                    else:
                        dicts[d.relation.entity2] = 1
                res.append(max(dicts, key=dicts.get))

                #Cancel the inheritance, if the associations exist in the entity the similar ones are cancelled in predecessors
                if res == []:
                    parents = [d.relation.entity2 for d in self.query_local(e1=entity) if not isinstance(d.relation,Association)]
                    for p in parents:
                        res += self.query(p, relname)
                return res

            return None
            
class MyCS(ConstraintSearch):

    def search_all(self,domains=None,xpto=None):
        # Pode usar o argumento 'xpto' para passar mais
        # informação, caso precise
        #
        # IMPLEMENTAR AQUI
        if domains == None:
            domains = self.domains
        #use xpto to save all solution
        xpto = []

        # se alguma variavle tiver na lista de valores vazia, falha
        if any([lv == [] for lv in domains.values()]):
            return None
        # se nenhuma variavel tiver mais do que um valor possivel, sucesso
        if all([len(lv) == 1 for lv in list(domains.values())]):
            return {v:lv[0] for (v,lv) in domains.items()}
        
        # continuação da pesquisa
        for var in domains.keys():
            if len(domains[var]) > 1:
                for val in domains[var]:
                    newdomains = dict(domains)
                    newdomains[var] = [val]
                    edges = [(v1,v2) for (v1,v2) in self.constraints if v2 == var ]
                    newdomains = self.constraint_propagation(newdomains, edges)
                    solution = self.search_all(newdomains)
                    # se a solution foi encontrada
                    if solution != None:
                        # se a solution nao foi adicionada na lista
                        if solution not in xpto:
                        # se a solution eh um dicionario
                            if isinstance(solution, dict):
                                #adiciona na lista
                                xpto.append(solution)
                                # se solution eh uma lista com valores anteriores
                            else:
                            # adiciona cada valor da solution
                                [xpto.append(v) for v in solution]
                return xpto

        




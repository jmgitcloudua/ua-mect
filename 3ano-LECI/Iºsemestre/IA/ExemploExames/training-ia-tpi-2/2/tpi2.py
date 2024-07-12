# encoding: utf8

from semantic_network import *
from bayes_net import *
from constraintsearch import *
from itertools import product


class MyBN(BayesNet):
    def individual_probabilities(self):
        # IMPLEMENTAR AQUI
        """dicts = {}
        for k in self.dependencies.keys():
            dicts[k] = self.indivProb(k, True)
        return dicts"""
        pass

    # Auxliar functions
    def indivProb(self, item, value):
        all_conjunctions = [
            c
            for c in (
                list(zip(self.dependencies.keys(), list(line)))
                for line in product([True, False], repeat=len(self.dependencies.keys()))
            )
            if (item, value) in c
        ]
        return sum([self.jointProb(c) for c in all_conjunctions])


class MySemNet(SemanticNetwork):
    def __init__(self):
        SemanticNetwork.__init__(self)

    def translate_ontology(self):
        # IMPLEMENTAR AQUI
        dicts = {}
        # Get all subtype and save in disctionary
        for d in self.declarations:
            if isinstance(d.relation, Subtype):
                if d.relation.entity2 in dicts:
                    if d.relation.entity1 not in dicts[d.relation.entity2]:
                        dicts[d.relation.entity2].append(d.relation.entity1)
                else:
                    dicts[d.relation.entity2] = [d.relation.entity1]
        # Sort list with all dictionary keys
        result = list(dicts.keys())
        result.sort()

        # For each keys construct the solution
        for j in range(len(result)):
            dicts[result[j]].sort()
            word = "Qx "
            for i in range(len(dicts[result[j]])):
                if i != len(dicts[result[j]]) - 1:
                    word += dicts[result[j]][i].capitalize() + "(x) or "
                else:
                    word += dicts[result[j]][i].capitalize() + "(x) => "
            word += result[j].capitalize() + "(x)"
            result[j] = word
        return result

    def query_inherit(self, entity, assoc):
        # IMPLEMENTAR AQUI
        inv = []
        for d in self.declarations:
            # check if association is inverse and if invsere is declared
            if isinstance(d.relation, Association) and d.relation.inverse:
                if d not in inv and d.relation.entity2 == entity:
                    inv.append(d)
        # Get the local declarations
        getLocalDec = [
            d
            for d in self.query_local(e1=entity, relname=assoc)
            if isinstance(d.relation, Association)
        ]
        # List to find inherited declarations
        listParents = [
            d.relation.entity2
            for d in self.query_local(e1=entity)
            if not isinstance(d.relation, Association)
        ]
        for p in listParents:
            result = self.query_inherit(p, assoc)
            if result != None:
                getLocalDec += result

        # If there weren't inverted declaration runt local+inherit
        if inv == []:
            return getLocalDec
        else:
            return list(set(getLocalDec + inv))

    def query(self, entity, relname):
        # IMPLEMENTAR AQUI
        if relname == "member":
            return list(
                set(
                    [
                        d.relation.entity2
                        for d in self.declarations
                        if isinstance(d.relation, Member)
                        and d.relation.entity1 == entity
                    ]
                )
            )
        elif relname == "subtype":
            return list(
                set(
                    [
                        d.relation.entity2
                        for d in self.declarations
                        if isinstance(d.relation, Subtype)
                        and d.relation.entity1 == entity
                    ]
                )
            )
        else:
            dicts = {}
            for d in self.query_local(relname=relname):
                if isinstance(d.relation, Association):
                    if d.relation.assoc_properties() not in dicts:
                        dicts[d.relation.assoc_properties()] = 1
                    else:
                        dicts[d.relation.assoc_properties()] += 1

            propertie = max(dicts, key=dicts.get)

            if propertie[0] == "multiple":
                return list(
                    set(
                        [
                            d.relation.entity2
                            for d in self.query_inherit(entity, relname)
                            if d.relation.assoc_properties() == propertie
                        ]
                    )
                )

            if propertie[0] == "single":
                dicts = {}
                res = []
                for d in [
                    d
                    for d in self.query_local(e1=entity, relname=relname)
                    if isinstance(d.relation, Association)
                    and d.relation.assoc_properties() == propertie
                ]:
                    if d.relation.entity2 in dicts:
                        dicts[d.relation.entity2] += 1
                    else:
                        dicts[d.relation.entity2] = 1
                res.append(max(dicts, key=dicts.get))

                if res == []:
                    parents = [
                        d.relation.entity2
                        for d in self.query_local(e1=entity)
                        if not isinstance(d.relation, Association)
                    ]
                    for p in parents:
                        res += self.query(p, relname)
                    return res
        return None


class MyCS(ConstraintSearch):
    def search_all(self, domains=None, xpto=None):
        # Pode usar o argumento 'xpto' para passar mais
        # informação, caso precise
        #
        # IMPLEMENTAR AQUI
        if domains == None:
            domains = self.domains
        xpto = []

        if any([lv == [] for lv in domains.values()]):
            return None
        if all([len(lv) == 1 for lv in list(domains.values())]):
            return {v: lv[0] for (v, lv) in domains.items()}

        for var in domains.keys():
            if len(domains[var]) > 1:
                for val in domains[var]:
                    newdomains = dict(domains)
                    newdomains[var] = [val]
                    edges = [(v1, v2) for (v1, v2) in self.constraints if v2 == var]
                    newdomains = self.constraint_propagation(newdomains, edges)
                    solution = self.search_all(newdomains)

                    if solution != None:
                        if solution not in xpto:
                            if isinstance(solution, dict):
                                xpto.append(solution)
                            else:
                                [xpto.append(v) for v in solution]
                return xpto

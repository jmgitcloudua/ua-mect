#encoding: utf8

#Name: Jodionisio Muachifi | Nmec: 97147 | LECI


import math
from typing import Counter
from itertools import product
from semantic_network import *
from bayes_net import *




class MySemNet(SemanticNetwork):
    def __init__(self):
        SemanticNetwork.__init__(self)
        # IMPLEMENT HERE (if needed)
        pass
    
    #------Auxliar Function (for exercice 1)
    def confidence_value(self,correct, wrong):
        neg_val = 1 - math.pow(0.75, correct)
        pos_val = math.pow(0.75, wrong)
        res = neg_val * pos_val
        return res
    #-----end Auxliar Function

    def source_confidence(self,user):
        # IMPLEMENT HERE
        correct = 0
        wrong = 0

        list_decl = list(set([d.relation for d in self.query_local(user=user) if isinstance(d.relation, AssocOne)]))
        
        if len(list_decl) == 0:
            return 0
        
        else:
            for d in list_decl:
                list_rel = list([m.relation.entity2 for m in self.query_local(e1=d.entity1,relname = d.name)])
                mostCommom = Counter(list_rel)
                mostCommom_plus = list([x for x,y in mostCommom.items() if y == max(mostCommom.values())])
                if d.entity2 in mostCommom_plus:
                    correct += 1
                else:
                    wrong += 1

        return self.confidence_value(correct, wrong)

    #---Auxliar Function (for exercice 2)
    def confidence_rec(self, n, T):
        value_1 = n/(2*T)
        value_2 = (1 - n/(2*T))
        value_3 = (1 - pow(0.95, n))
        value_4 = pow(0.95, T - n)
        res = value_1 + value_2 * value_3 * value_4
        return res 
    #----end Auxliar Function 


    def query_with_confidence(self,entity,assoc):
        # IMPLEMENT HERE
        
        parents =  { d.relation.entity2 for d in self.query_local(e1=entity) if isinstance(d.relation, Member) or isinstance(d.relation, Subtype) }

        if entity == 'madonna' and assoc =='feeding':
            DEBUG = True

        associations:list[AssocOne] = [ d.relation.entity2 for d in self.query_local(e1=entity, relname=assoc) if isinstance(d.relation, AssocOne) or isinstance(d.relation, AssocSome) ]
        
        # Compute also the total number of declarations of assoc in entity, T
        T = len(associations)
        
        # Compute the number of occurrences, n, for each alternative value (i.e. second argument) of assoc in entity.
        counter = Counter(associations)

        # Compute the confidence in each value
        local_confs = { e: self.confidence_rec(counter.get(e), T) for e in associations }

        # If there are no inherited results, the local results should be returned
        if  not parents:
            return local_confs

        # get inherited confidences
        parent_confs = {}
        for p in parents:
            # get parent's confidences
            p_confs = self.query_with_confidence(p, assoc)

            for decl in p_confs:
                if decl not in parent_confs:
                    parent_confs[decl] = p_confs[decl]
                else:
                    parent_confs[decl] += p_confs[decl]
        
                # average the confidence results
        # (i.e. divide by number of parents)
        parent_confs = { v:parent_confs[v]/len(parents) for v in parent_confs }

        # If there are no local results, the inherited results should be returned with a discount of 10%
        # (i.e. multiply confidences by 0.9)
        if not local_confs:
            parent_confs = {c:parent_confs[c]*0.9 for c in parent_confs}
            return parent_confs

        # the final confidence values are computed by weighted average, with
        # 0.9 for the local confidences and 0.1 for the inherited confidences
        #keys = set(local_confs.keys()).update(parent_confs.keys())

        keys = []
        keys.extend(local_confs.keys())
        keys.extend(parent_confs.keys())
        keys = set(keys)

        if not keys:
            return local_confs

        for k in keys:
            f_value = 0
            if k in local_confs and k in parent_confs:
                f_value += 0.9*local_confs[k]
                f_value += 0.1 * parent_confs[k]
            elif k in local_confs:
                f_value += local_confs[k]
            elif k in parent_confs:
                f_value += 0.1 * parent_confs[k]
            local_confs[k]=f_value

        return local_confs
                    


class MyBN(BayesNet):

    def __init__(self):
        BayesNet.__init__(self)
        # IMPLEMENT HERE (if needed)
        pass

    #-----Auxiliar functions ( for exercice 3)
    def conjunction(self, lvars):
        lst = product([True,False], repeat=len(lvars))
        return list(map(lambda c : list(zip(lvars, c)),lst))

    def ancestors(self, var):
        list_vars = [ v for (v,x) in list(self.dependencies[var].keys())[0] ]
        result = list_vars

        for v in list_vars:
            result += self.ancestors(v)

        return list(set(result))

    def indivProb(self,var,val):
        prob = 0
        ancestors = self.conjunction(self.ancestors(var))
        for conj in ancestors:
            prob += self.jointProb(conj + [(var, val)])
        return prob
    #------end Auxliar Functions

    def individual_probabilities(self):
        # IMPLEMENT HERE
        dicts = {}
        for m in self.dependencies.keys():
            dicts[m] = self.indivProb(m, True)
        return dicts
  
    



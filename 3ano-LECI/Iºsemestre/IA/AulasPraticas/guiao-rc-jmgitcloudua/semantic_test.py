from semantic_network import *


a = Association('socrates','professor','filosofia')
s = Subtype('homem','mamifero')
m = Member('socrates','homem')

da = Declaration('descartes',a)
ds = Declaration('darwin',s)
dm = Declaration('descartes',m)

z = SemanticNetwork()
z.insert(da)
z.insert(ds)
z.insert(dm)
z.insert(Declaration('darwin',Association('mamifero','mamar','sim')))
z.insert(Declaration('darwin',Association('homem','gosta','carne')))

# novas declaracoes

z.insert(Declaration('darwin',Subtype('mamifero','vertebrado')))
z.insert(Declaration('descartes', Member('aristoteles','homem')))

b = Association('socrates','professor','matematica')
z.insert(Declaration('descartes',b))
z.insert(Declaration('simao',b))
z.insert(Declaration('simoes',b))

z.insert(Declaration('descartes', Member('platao','homem')))

e = Association('platao','professor','filosofia')
z.insert(Declaration('descartes',e))
z.insert(Declaration('simao',e))

z.insert(Declaration('descartes',Association('mamifero','altura',1.2)))
z.insert(Declaration('descartes',Association('homem','altura',1.75)))
z.insert(Declaration('simao',Association('homem','altura',1.85)))
z.insert(Declaration('darwin',Association('homem','altura',1.75)))

z.insert(Declaration('descartes', Association('socrates','peso',80)))
z.insert(Declaration('darwin', Association('socrates','peso',75)))
z.insert(Declaration('darwin', Association('platao','peso',75)))


z.insert(Declaration('damasio', Association('filosofo','gosta','filosofia')))
z.insert(Declaration('damasio', Member('socrates','filosofo')))

z.query_local(user='descartes', rel='member')

z.show_query_result()

print("-------------Predecessor-----------------")
z1 = z.predecessor('vertebrado','socrates')
z2 = z.predecessor('vertebrado','filosofo')
print(z1)
print(z2)

print("\n")
print("------------Predecessor Path-----------------")
z3 = z.predecessor_path('vertebrado','socrates')
z4 = z.predecessor_path('vertebrado','filosofo')
print(z3)
print(z4)

print("\n")
print("------------Query-----------------")
z5 = z.query('socrates','altura')
print(z5)

print("\n")
print("-------------Query 2-------------------")
z6 = z.query2('platao')
print(z6)

print("\n")
print("--------------Query Cancel-----------------")
z7 = z.query_cancel('socrates','altura')
print(z7)

print("\n")
print("---------------Query Down-----------------")
z8 = z.query_down('vertebrado', 'altura')
z9 = z.query_down('mamifero', 'altura')
z10 = z.query_down('homem', 'altura')
print(z8)
print(z9)

print("\n")
print("----------------Query Induce---------------")
z11 = z.query_induce('vertebrado', 'altura')
print(z11)

print("\n")
""" print("----------------Query Local Assoc---------------")
z12 = z.query_local_assoc('socrates', 'pai')
z13 = z.query_local_assoc('homem', 'gosta')
z14 = z.query_local_assoc('socrates', 'pulsacao')
print(z12)
print(z13)
print(z14) """
print("----------------Query Assoc Value---------------")
z12 = z.query_assoc_value('socrates', 'altura')
z13 = z.query_assoc_value('socrates', 'peso')
print(z12)
print(z13)

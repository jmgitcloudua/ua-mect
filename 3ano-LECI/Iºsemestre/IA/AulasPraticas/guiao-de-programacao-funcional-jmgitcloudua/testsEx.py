from aula1 import *
from aula2 import *


print()
print("«««««« Test Exe 1.1 »»»»»")
xlist = ["apple", "banana", "cherry", "raspberry"]
y = "The length of the list is : {}"
print(y.format(comprimento(xlist)))

print()

print("«««««« Test Exe 1.2 »»»»»")
xlist = [8, 4, 2, 12, 20, 40]
y = "The sum is : {}"
print(y.format(soma(xlist)))

print()

print("«««««« Test Exe 1.3 »»»»»")
xlist = ["apple", "banana", "cherry", "raspberry"]
u = existe(xlist, "apple")
print("The value is : ", end="")
print(u)

print()

print("«««««« Test Exe 1.4 »»»»»")
xlist = ["apple", "banana", "cherry", "raspberry"]
ylist = [100, 200, 50, 25]
res = concat(xlist, ylist)
print("The list concatenated is : ", end="")
print(res)

print()

print("«««««« Test Exe 1.5 »»»»»")
xlist = ["apple", "banana", "cherry", "raspberry"]
u = inverte(xlist)
print("The inverted list is : ", end="")
print(u)

print()

print("«««««« Test Exe 1.6 »»»»»")
nlist = [22, 33, 2882, 5005, 292, 2882]
v = capicua(nlist)
print("The capicua list is : ", end="")
print(v)

print()

print("«««««« Test Exe 1.7 »»»»»")
xlist = [[1, 2, 3], [7, 8, 5], [10, 9, 10]]
y = explode(xlist)
print("The concatenated list of list is : ", end="")
print(y)

print()

print("«««««« Test Exe 1.8 »»»»»")
nlist = [1, 2, 3, 4]
y = substitui(nlist, 3, 5)
print("The replace list  is : ", end="")
print(y)

print()


print("«««««« Test Exe 1.9 »»»»»")
lista1 = [1, 2, 3, 4, 8, 7]
lista2 = [12, 14, 11]
lista3 = junta_ordenado(lista1, lista2)
print("The union of ordered list  is : ", end="")
print(lista3)

print()

print("«««««« Test Exe 1.10 »»»»»")
setList = [1, 2, 4]
resList = subconjuntos(setList)
print("The set of list is : ", end="")
print(resList)

print()

print("«««««« Test Exe 2.1 »»»»»")
separarLista = [(1, 'a'), (2, 'b'), (3, 'c')]
resLista = separar(separarLista)
print("The separate list is : ", end="")
print(resLista)

print()

print("«««««« Test Exe 2.2 »»»»»")
rList = [1, 6, 2, 5, 5, 2, 5, 2]
resList = remove_e_conta(rList, 2)
print("The remove and count element is : ", end="")
print(resList)

print()

print("«««««« Test Exe 2.3 »»»»»")
countList = [1, 6, 2, 5, 5, 2, 5, 2]
resList = contar_elementos(countList)
print("The pair frequent count element is : ", end="")
print(resList)

print()

print("«««««« Test Exe 3.1 »»»»»")
lista = [1, 6, 2, 5, 5, 2, 5, 2]
resLista = cabeca(lista)
print("The header element is : ", end="")
print(resLista)

print()

print("«««««« Test Exe 3.2 »»»»»")
lista = ["banana", "cherry", "raspberry"]
resLista = cauda(lista)
print("The tail element is : ", end="")
print(resLista)

print()

print("«««««« Test Exe 3.3 »»»»»")
l1 = ["banana", "cherry", "raspberry"]
l2 = ["meat", "fish", "chicken"]
resLista = juntar(l1, l2)
print("The union element is : ", end="")
print(resLista)

print()

print("«««««« Test Exe 3.4 »»»»»")
lista = [40, 20, 60, 10, 18]
resLista = menor(lista)
print("The min element of the list is : ", end="")
print(resLista)

print()

print("«««««« Test Exe 3.5 »»»»»")
lista = [40, 20, 60, 10, 18]
resLista = min_lista(lista)
print("The min element and there list are : ", end="")
print(resLista)

print()

print("«««««« Test Exe 3.6 »»»»»")
lista = [40, 20, 60, 10, 18]
resLista = max_min(lista)
print("The min and max element of the list are : ", end="")
print(resLista)

print()


print("«««««« Test Exe 3.7 »»»»»")
lista = [40, 20, 60, 10, 18]
resLista = mins_lista(lista)
print("The triples and two elements of the list are : ", end="")
print(resLista)

print()


print("«««««« Test Exe 3.7 »»»»»")
lista = [40, 20, 60, 10, 18]
resLista = media_mediana(lista)
print("The mean, median are : ", end="")
print(resLista)

print()

print("«««««« Test Exe 4.1 »»»»»")
x = impar(53)
print("The result(even num) is : ", end="")
print(x)

print()

print("«««««« Test Exe 4.2 »»»»»")
x = positivo(-10)
print("The result(positive) is : ", end="")
print(x)

print()

print("«««««« Test Exe 4.3 »»»»»")
x = comparar_modulo(-10, -16)
print("The result abs(x) < abs(y) is : ", end="")
print(x)

print()

print("«««««« Test Exe 4.4 »»»»»")
x = cart2pol(4, 3)
print("The result cart2pol is : ", end="")
print(x)

print()

'''
print("«««««« Test Exe 4.5 »»»»»")
func = ex5(lambda x, y: x+y, lambda x, y: x*y, lambda x, y: x < y)
print("The result (f, g, h) is : ", end="")
print(func)
'''

print()


print("«««««« Test Exe 4.6 »»»»»")
lista = [4, 2, 5, 8, 10, 20]
x = quantificador_universal(lista, lambda n: n > 10)
print("The result (universal quantifier) is : ", end="")
print(x)

print()

print("«««««« Test Exe 4.7 »»»»»")
lista = [4, 2, 5, 8, 10, 20]
x = quantificador_existencial(lista, lambda n: n < 10)
print("The result (existential quantifier) is : ", end="")
print(x)

print()


print("«««««« Test Exe 4.8 »»»»»")
lista1 = [1, 2, 3]
lista1 = [7, 8, 9]
x = subconjunto(lista1, lista2)
print("The result (subset) is : ", end="")
print(x)

print()


print("«««««« Test Exe 5.1a »»»»»")
lista = [1, 2, 3, -8, 20]
x = selection_sort(lista)
print("The result (selection sort) is : ", end="")
print(x)

print()

print("«««««« Test Exe 5.1b »»»»»")
lista = [20, 48, 3, -81, 20]
print("The result (bubble sort) is : ", end="")
bubble_sort(lista)
for i in range(len(lista)):
    print("% d" % lista[i], end="")


print()
print()

print("«««««« Test Exe 5.1c »»»»»")
# Driver code to test above
arr = [10, 7, 8, 9, 1, 5]
n = len(arr)
quickSort(arr, 0, n-1)
print("Sorted array(quick sort) is: ", end="")
for i in range(n):
    print("%d" % arr[i], end=" "),


print()
print()

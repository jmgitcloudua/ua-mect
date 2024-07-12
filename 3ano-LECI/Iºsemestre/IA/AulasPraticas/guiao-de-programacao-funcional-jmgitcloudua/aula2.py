import math

# Exercicio 4.1
impar = lambda x:  True if (x % 2 != 0) else False


# Exercicio 4.2
positivo = lambda x: True if(x > 0) else False


# Exercicio 4.3
comparar_modulo = lambda x, y: True if (abs(x) < abs(y)) else False


# Exercicio 4.4
cart2pol = lambda x, y: (math.sqrt(pow(x, 2) + pow(y, 2)), math.atan2(y, x))


# Exercicio 4.5
ex5 = lambda f, g, h: lambda x, y, z:  h(f(x, y), g(y, z))


# Exercicio 4.6
def quantificador_universal(lista, f):
    if lista == []:
        return True
    if f(lista[0]):
        return quantificador_universal(lista[1:], f)
    return False


# Exercicio 4.7
def quantificador_existencial(lista, f):
    if(lista == []):
        return False

    if(f(lista[0])):
        return True
    return quantificador_existencial(lista[1:], f)


# Exercicio 4.8
def subconjunto(l1, l2):
    if(l1 == []):
        return True

    if l1[0] in l2:
        return subconjunto(l1[1:], l2)
    return False


# Exercicio 4.9
def ordem(lista, f):
    if lista == []:
        return None
    if len(lista) == 1:
        return lista[0]

    o = ordem(lista[1:], f)
    return lista[0] if f(lista[0], o) else o


'''
version 2
# Exercicio 4.9
def ordem(lista, f):
    if(lista == []):
        return None

    min = ordem(lista[0:len(lista)-1], f)

    if(min == None):
        min = lista[0]
    elif(f(min, lista[len(lista)-1]) == False):
        min = lista[len(lista)-1]
    return min

'''


# Exercicio 4.10
def filtrar_ordem(lista, f):
    minElem = ordem(lista, f)

    result = []
    for value in lista:
        if value != minElem:
            result.append(value)
    return (minElem, result)


# Exercicio 5.1a
def selection_sort(lista):
    if(lista == []):
        return []

    (m, l) = get_min(lista)
    return [m] + selection_sort(l)


# Função auxiliar para Ex5.1a
def get_min(lista):
    m = min(lista)
    result = []
    for i in lista:
        if i != m:
            result.append(i)

    return (m, result)


# Exercicio 5.1b
def bubble_sort(lista):
    n = len(lista)
    trocas = True
    while(trocas):
        trocas = False
        n -= 1
        for i in range(0, n):
            if(lista[i] > lista[i+1]):
                tmp = lista[i]
                lista[i] = lista[i+1]
                lista[i+1] = tmp
                trocas = True


# Exercicio 5.2
def ordenar_seleccao(lista, ordem):
    if(lista == []):
        return []

    (min, l) = filtrar_ordem(lista, ordem)
    return [min] + ordenar_seleccao(l, ordem)


# Python program for implementation of Quicksort Sort

# This function takes last element as pivot, places
# the pivot element at its correct position in sorted
# array, and places all smaller (smaller than pivot)
# to left of pivot and all greater elements to right
# of pivot


def partition(arr, low, high):
    i = (low-1)		 # index of smaller element
    pivot = arr[high]	 # pivot

    for j in range(low, high):

        # If current element is smaller than or
        # equal to pivot
        if arr[j] <= pivot:

            # increment index of smaller element
            i = i+1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i+1], arr[high] = arr[high], arr[i+1]
    return (i+1)

# The main function that implements QuickSort
# arr[] --> Array to be sorted,
# low --> Starting index,
# high --> Ending index

# Function to do Quick sort


def quickSort(arr, low, high):
    if len(arr) == 1:
        return arr
    if low < high:

        # pi is partitioning index, arr[p] is now
        # at right place
        pi = partition(arr, low, high)

        # Separately sort elements before
        # partition and after partition
        quickSort(arr, low, pi-1)
        quickSort(arr, pi+1, high)

def interpretacoes(lst):
    if lst == []:
        return [[]]
    y = interpretacoes(lst[1:])
    return [[(lst[0], a)] + z for z in y for a in [True, False]]

lst = ["a", "b"]
print(interpretacoes(lst))
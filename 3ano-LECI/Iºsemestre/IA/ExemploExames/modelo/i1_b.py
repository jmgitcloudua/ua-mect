def g(x): 
    if x==[]: 
        return [[]] 
    y = g(x[1:]) 
    return y + [ [x[0]]+z for z in y ]

lst = [1, 2, 3]
print(g(lst))
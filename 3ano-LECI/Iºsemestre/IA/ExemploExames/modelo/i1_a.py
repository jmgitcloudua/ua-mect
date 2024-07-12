def f(x): 
    if x==[]: 
        return 0 
    if x[0]>0: 
        return x[0] + f(x[1:]) 
    return f(x[1:])

lst = [1, 4 ,8 , -2, 10, -5]
print(f(lst))
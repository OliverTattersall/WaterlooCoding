fun = lambda x,y : x*x + y*y

# print(fun(1,2))

sum = 0
a = 0
b = 2
N = 1000
h = (b-a)/N

for i in range(N):
    tmpsum = 0
    x = h*i
    for j in range(N):
        tmpsum += (fun(x,h*j) + fun(x,h*(j+1)))*h/2

    sum +=tmpsum*h

print(sum)


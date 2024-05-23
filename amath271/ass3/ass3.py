from numpy import linspace 
from matplotlib import pyplot as plt

def simpson(a, b, fun, n = 10000):
    n = 10000000
    h = (b - a)/n
    sum = 0
    for i in range(1, n, 2):
        sum += 4*fun(a + i*h)


    for i in range(2, n, 2):
        sum += 2*fun(a + i*h)

    sum += fun(a) + fun(b)

    sum *= h/3

    return sum



quad = lambda x : x*x

# print(simpson(0, 1, quad))

quartic = lambda x: x*x*x*x

x = linspace(-5, 5, 50)
y = quartic(x)
plt.figure()
plt.plot(x,y)
plt.xlabel("x")
plt.ylabel("U")
plt.title("U vs x for U = kx^4 with k = 1")
# plt.show()
plt.savefig("q2 plot.png")

# q2 = lambda x : 1/(1 - quartic(x)) ** (0.5)

# print(1 - 1e-9)

# print(simpson(0,1 - 1e-9,q2))
# print(4*simpson(0,1 - 1e-9,q2)/ (2 ** (0.5)))


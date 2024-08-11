import cmath 
import math

cs = [complex(1,0), complex(0, 2), complex(0, -3), complex(4,0)]


expX = lambda n, k : -4*n*k*(1-(-1)**(n+k))/((math.pi**2)*(n*n-k*k)**2)



sum = complex(0, 0)
for n in range(1, 5, 1):
    for k in range(1, 5, 1):
        if(n == k):
            sum = sum
            # sum = sum + cs[n - 1].conjugate()*cs[n - 1]*0.5
        else:
            sum = sum + cs[n - 1].conjugate()*cs[k - 1]*expX(n, k)

# print(sum/30)




expP = lambda n,k : complex(0,-2)*k*(n*((-1)**n)*(-1)**k - n)/((k*k - n*n))

sum = complex(0, 0)
for n in range(1, 5, 1):
    for k in range(1, 5, 1):
        if(n == k):
            sum = sum
            # sum = sum + cs[n - 1].conjugate()*cs[n - 1]*0.5
        else:
            sum = sum + cs[n - 1].conjugate()*cs[k - 1]*expP(n, k)

print(sum/30)


def RSAencryption(publickey, M):
    e,n = publickey
    C = M**e % n
    return C

print(RSAencryption((23,377), 20))


def RSAdecryption(publickey, C):
    e,n = publickey
    p = 0
    primes=[]
    for i in range(2,n):
        flag = True
        for j in primes:
            if i%j==0:
                glag=False
                break
        if flag:
            if n%i==0:
                p = i
                break
            primes.append(i)

    q = n//p
    d=0
    for i in range((q-1)*(p-1)):
        if e*i%((q-1)*(p-1))==1:
            d=i
            break
    
    R = C**d%n
    return R
print(RSAdecryption((23,377), 197))
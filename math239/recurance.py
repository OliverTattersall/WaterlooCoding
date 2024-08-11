import functools

sqrt = lambda n : n**0.5
bn = lambda n : 239*n*n + 69*n + 42 + (-2*n+2)*4**n 
cn = lambda n : ((-1 + sqrt(7))*(2+sqrt(7))**n - (1 + sqrt(7))*(2-sqrt(7))**n + 5)/3

@functools.cache
def recur(n):
    basecase = [44, 350, 1104, 2144, 2606]
    if n <= 4:
        return basecase[n]
    
    return 11*recur(n-1) -43*recur(n-2)+73*recur(n-3)-56*recur(n-4)+16*recur(n-5)


@functools.cache
def recur2(n):
    basecases = [1, 5, 13]
    if n <= 2:
        return basecases[n]
    
    return 5*recur2(n-1)-recur2(n-2)-3*recur2(n-3)

# print(cn(462), recur2(462))

# for i in range(1000):
#     if( bn(i) != recur(i)):
#         print(i, " ERROR ")
#         break


# for i in range(400):
#     if ( abs(cn(i) - recur2(i)) > 0.01*recur2(i)):
#         print(i, "Error")
#         break


@functools.cache 
def recur3(n):
    basecases = [1,3,5]
    if n <= 2:
        return basecases[n]
    return 3*recur3(n-2) + 2*recur3(n-3)


for i in range(40):
    if ( ((-1)*(-1)**i + 4*(2)**i)/3 != recur3(i) ):
        print(i, "ERROR")
        break


def createRecur(basecases, recurs):
    @functools.cache
    def rec(n):
        if n < len(basecases):
            return basecases[n]
        sum = 0
        for i in range(len(recurs)):
            sum += recurs[i] * rec(n - i - 1)
        return sum
    return rec 


def test(f1, f2):
    for i in range(400):
        if(f1(i) != f2(i)):
            print (i, "ERRoR")
            return 


rec4 = createRecur([1,3,5], [0, 3, 2])

for i in range(40):
    if (rec4(i) != recur3(i)):
        print(i, "ERRO")
        break

rec5 = createRecur([1,3], [1, 2])


test(rec4, rec5)


rec6 = createRecur([1,8], [9, -20])
form = lambda n : -3*4**n + 4*5**n 
test(rec6, form)


rec7 = createRecur([1,2], [1,2])
form7 = lambda n : 2**n 
test(rec7, form7)


rec8 = createRecur([3, 10], [10, -25])
form8 = lambda n : (3 - n)*5**n 
test(rec8, form8)

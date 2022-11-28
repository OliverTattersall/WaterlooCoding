def modBigNumber(num, m):
    # Store the modulus of big number
    vec = []
    mod = 0
 
    # Do step by step division
    for i in range(0,len(num),1):
        digit = ord(num[i]) - ord('0')
 
        # Update modulo by concatenating
        # current digit.
        mod = mod * 10 + digit
 
        # Update quotient
        quo = int(mod / m)
        vec.append(quo)
 
        # Update mod for next iteration.
        mod = mod % m    
     
    #print("\n")
    print("Remainder :",mod)
 
    print("Quotient :",end = " ")
 
    # Flag used to remove starting zeros
    zeroflag = 0
    for i in range(0,len(vec),1):
        if (vec[i] == 0 and zeroflag == 0):
            continue
        zeroflag = 1
        print(vec[i],end="")
 
    return
 
# Driver Code
if __name__ == '__main__':
    num = str(10**23)
    m = 13
    modBigNumber(num, m)
 
# This code is contributed by
# Surendra_Gangwar
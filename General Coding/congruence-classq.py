
ans = []

for i in range(585):
    ans.append((i, (616*i+135)%585))

# ans=sorted(list(ans), key = lambda x:x[0])

print(ans)
count=0
for j in range(1, 45):
    count=0
    for i in range(585):
        # if i%15!=ans[i][1]%15:
            # print(i)
            # count+=1
        if 13*i%j!=ans[i][1]%j:
            count+=1
    if count==0:
        print(j)
    

# print(count)
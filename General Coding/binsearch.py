
def binarysearch(lst, val):

    first = 0
    end = len(lst) - 1

    while(first <= end):
        med = (end + first) // 2

        if(lst[med] == val):
            return med
        elif(lst[med] < val):
            first = med + 1
        else:
            end = med - 1


    print(first, end)

    return -1

lst = [1,3,5,7,9,11,13,15]
binarysearch(lst, 8)
binarysearch(lst, 4)
binarysearch(lst, 0)
binarysearch(lst, 16)
lst.insert(8, 16)
print(lst)

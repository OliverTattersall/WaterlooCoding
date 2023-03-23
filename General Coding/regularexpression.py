import re

lst = ['ab'*i for i in range(10)]
r5 = re.compile('^[^a]*a[^a]*$')
r4 = re.compile('^[!a]*a[!a]*$')
r3 = re.compile('[^a]*a[^a]*')
r2 = re.compile('^a$')
r = re.compile('a')
print(list(filter(r4.match, lst)))
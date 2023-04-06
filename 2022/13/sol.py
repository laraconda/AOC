import fileinput
from functools import cmp_to_key
import sys

ans = 1

def c(a,b,idx):
    if isinstance(a, int):
        if isinstance(b, int):
            if a < b:
                return -1
            elif b < a:
                return 1
            else:
                return 0
        elif isinstance(b, list):
            return c([a], b, idx)
    elif isinstance(a, list):
        if isinstance(b, list):
            for i in range(min(len(a), len(b))):
                r = c(a[i],b[i],idx)
                if r != 0:
                    return r
            if len(a) < len(b):
                return -1
            elif len(b) < len(a):
                return 1
            else:
                return 0
        elif isinstance(b, int):
            return c(a, [b], idx)
            
    
idx = 1
i = 0
data = sys.stdin.read().splitlines()
packs = list()
for line in data:
    if len(line) != 0:
        line = eval(line)
        packs.append(line)

spacks = sorted(packs, key=cmp_to_key(lambda a,b: c(a,b, 0)))
aa = eval('[[2]]')
bb = eval('[[6]]')
ans = (spacks.index(aa) + 1) * (spacks.index(bb) + 1)

print(ans)

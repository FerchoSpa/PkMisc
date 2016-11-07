import math

nc = 18
count = 0
def isf(a,b,c,d,e):
  co = 0
  if a<13: co += 1
  if b<13: co += 1
  if c<13: co += 1
  if d<13: co += 1
  if e<13: co += 1
  return co >= 3

fl = 0
for i in range(2,nc):
  for j in range(i+1, nc):
    for k in range(j+1, nc):
      for l in range(k+1, nc):
        for m in range(l+1, nc):
          #print i, j, k
          count += 1
          if isf(i, j, k, l, m): fl += 1; print i, j, k, l, m
print count, fl
print math.factorial(nc)/(math.factorial(nc-5)*math.factorial(5))


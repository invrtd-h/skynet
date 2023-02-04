N,M = map(int,input().split())
A=[int(input()) for _ in range(N)]
D= [int(input()) for _ in range(M)]
B =A.sort()

def b_s(tar, A):
  if tar<A[0] or tar>A[-1]:
    return -1
  lo,hi =0, N-1
  while hi-lo>=2:
    mid = (lo+hi)//2
    if A[mid]>=tar:
      hi = mid
    else:
      lo= mid
  if A[lo] == tar:
    return lo
  elif A[hi] == tar:
    return hi
  return -1

for i in range(M):
  print(b_s(D[i],A))

n = int(input())
lo,hi = 1, n

while lo<=hi:
  mid = (lo+hi)//2
  if mid**2<n:
    lo = mid+1
  elif mid**2>n:
    hi=mid-1
  elif mid**2==n:
    print(mid)
    break

##동장님 설명 참고

n,m = map(int, input().split())
A=list(map(int, input().split()))


def f(x: int):
  return sum(x//i for i in A)


lo, hi = 0, 10 ** 13
while hi - lo > 1:
    mid = (lo + hi) // 2
    if f(mid) >= m:
        hi = mid
    else:
        lo = mid
ret = lo if f(lo) >= m else hi
print(ret)

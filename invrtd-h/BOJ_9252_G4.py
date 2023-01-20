a = input()
b = input()

memo = [[-1 for _ in range(len(b))] for _ in range(len(a))]
access = lambda i, j: memo[i][j] if i >= 0 and j >= 0 else 0

for i in range(len(a)):
    for j in range(len(b)):
        if a[i] == b[j]:
            memo[i][j] = access(i - 1, j - 1) + 1
        else:
            memo[i][j] = max(access(i - 1, j), access(i, j - 1))
print(memo[-1][-1])

ret = ''
ix, jx = len(a) - 1, len(b) - 1
while ix >= 0 and jx >= 0:
    if a[ix] == b[jx]:
        ret += a[ix]
        ix -= 1
        jx -= 1
    elif access(ix - 1, jx) > access(ix, jx - 1):
        ix -= 1
    else:
        jx -= 1

print(ret[::-1])

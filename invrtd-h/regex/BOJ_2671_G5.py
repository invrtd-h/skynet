import re
print("SUBMARINE" if re.compile("(100+1+|01)+").fullmatch(input()) else "NOISE")

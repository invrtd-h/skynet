#5585
a = int(input())

b = 1000-a

#500엔 100엔 50엔 10엔 5엔 1엔

oback = b//500
back = (b%500)//100
oship = (b%500)%100//50
ship = (((b%500)%100)%50)//10
oh = ((((b%500)%100)%50)%10)//5
ill = (((((b%500)%100)%50)%10)%5)//1

print(oback+back+oship+ship+oh+ill)

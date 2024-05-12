import math

x = float(input("Insira o valor de X: "))

lim = ((x ** 2 - 2*x + 1) / (x - 1)) * math.sin(1 / (x - 1))

print(f'resultado: {lim}')

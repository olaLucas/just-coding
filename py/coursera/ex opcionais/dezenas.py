numero = int(input("Digite um número inteiro:"))

milhar = numero % 1000
centena = milhar % 100
dezena = ((numero % 1000) % 100) // 10

print("O digito das dezenas é:", dezena)
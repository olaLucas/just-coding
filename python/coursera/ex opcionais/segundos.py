input = int(input("Insira a quantidade de segundos: "))

dias = input // 86400
horas = (input % 86400) // 3600
minutos = ((input % 86400) % 3600) // 60
segundos = (((input % 86400) % 3600) % 60) % 60

print(dias, "dias,", horas, "horas,", minutos, "minutos e", segundos, "segundos.")
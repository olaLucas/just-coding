altura = eval(input("Insira sua altura: "))
peso = eval(input("Insira seu peso: "))

imc = peso / (altura * altura)

if imc < 18:
    print("Abaixo do peso normal.")
elif imc >= 18 and  imc < 25:
    print("Peso normal.")
elif imc >= 25 and imc < 35:
    print("Excesso de peso.")
elif imc >= 30 and imc < 35:
    print("Obesidade classe 1")
elif imc >= 35 and imc <= 40:
    print("Obesidade classe 2")
elif imc > 40:
    print("Obesidade classe 3.")

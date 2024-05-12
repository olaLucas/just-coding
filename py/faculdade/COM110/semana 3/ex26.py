def soma(x, y):
    return x + y

def sub(x, y):
    return x - y

def multi(x, y):
    return x * y

def div(x, y):
    return x / y

def seloption():
    option = -1
    while True:
        print("Selecione alguma opção: ")
        print("1. Adição")
        print("2. Subtração")
        print("3. Multiplicação")
        print("4. Divisão")

        option = int(input(">>> "))
        if option < 1 or option > 4:
            print("Opção inválida! Tente novamente.")
        else:
            break
    pass
    
    return option

def insertNumbers():
    print("Insira dois números: \n")

    x = int(input("X = "))
    y = int(input("Y = "))

    return (x, y)

def main():
    resultado = -1
    option = seloption()
    x, y = insertNumbers()
    
    match option:
        case 1:
            resultado = soma(x, y)
        case 2:
            resultado = sub(x, y)
        case 3:
            resultado = multi(x, y)
        case 4:
            resultado = div(x, y)

    print(f'resultado: {resultado}')

main()


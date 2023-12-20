class cliente:
    def __init__(self) -> None:
        
        self.nome = None
        self.cnpj = None
        self.cep = None
        self.numeroCasa = None
        self.complemento = None
        pass

    def getValues(self, tuple):
        # tuple = (nome, cnpj, cep, numeroCasa, complemento)
        self.nome = tuple[0]
        self.cnpj = tuple[1]
        self.cep = tuple[2]
        self.numeroCasa = tuple[3]
        self.complemento = tuple[4]

        print("Classe Cliente")
        print("Nome", self.nome)
        print("CNPJ", self.cnpj)
        print("CEP", self.cep)
        print("Numero", self.numeroCasa)
        print("Complemento", self.complemento)
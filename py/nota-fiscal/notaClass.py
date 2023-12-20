class nota:
    def __init__(self) -> None:
        self.CNPJ = None
        self.valor = None
        self.discriminacao = None
        self.servico = None
    
    def getValues(self, tuple):
        # tuple = (cnpj, valor, discriminacao, servico)
        self.CNPJ = tuple[0]
        self.valor = tuple[1]
        self.discriminacao = tuple[2]
        self.servico = tuple[3]

        print("Classe nota")
        print("CNPJ: ",self.CNPJ)
        print("Valor:", self.valor)
        print("Discriminação:", self.discriminacao)
        print("Serviço:", self.servico)
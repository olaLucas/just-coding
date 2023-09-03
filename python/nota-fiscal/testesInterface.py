import customtkinter
import tkinter
from notaClass import nota
from clienteClass import cliente

        
class emissaoFrame(customtkinter.CTkFrame):
    def __init__(self, master):
        super().__init__(master)

        # Grid config
        self.configure(fg_color="transparent")
        self.grid_columnconfigure((0,2), weight=1)
        self.grid_rowconfigure((3), weight=1)

        # Frame emissão de notas e widgets
        self.servicoLabel = customtkinter.CTkLabel(
            self, text="Qual tipo de serviço?", font=customtkinter.CTkFont("Roboto", 20), anchor=tkinter.CENTER)
        self.servicoLabel.grid(row=0, column=0, columnspan=3, padx=0, pady=10, sticky="new")
        
        # Serviço radio buttons
        self.servicoRadioVar = customtkinter.StringVar(value="None")
        self.servicoLabels = ["Montagem", "Manutenção"]
        for i in range(len(self.servicoLabels)):
            self.servicoRadios = customtkinter.CTkRadioButton(
                self, text=self.servicoLabels[i], value=self.servicoLabels[i], variable=self.servicoRadioVar, command=self.servicoFunction)
            self.servicoRadios.grid(row=1, column=i, padx=10, pady=5)
            self.servicoRadios.grid(sticky="ne")
            
        # Textbox widget e label
        self.labelDISCRIMINACAO = customtkinter.CTkLabel(
            self, text="Discriminação da nota:", font=customtkinter.CTkFont("Roboto", 22), anchor=tkinter.CENTER)
        self.labelDISCRIMINACAO.grid(row=2, column=0, columnspan=3, padx=0, pady=10, sticky="new")
        self.textboxDISCRIMINACAO = customtkinter.CTkTextbox(self)
        self.textboxDISCRIMINACAO.grid(row=3, column=0, columnspan=3, padx=10, pady=(0,10), sticky="nsew")
    

class entryFrame(customtkinter.CTkFrame):
    def __init__(self, master):
        super().__init__(master)

        # Grid Config
        self.configure(fg_color="transparent")
        self.grid_columnconfigure(0, weight=0)
        self.grid_rowconfigure((0,2), weight=0)

        # Labels e Inputs
        self.CNPJLabel = customtkinter.CTkLabel(self, text="CPF/CNPJ do cliente/loja:", anchor=tkinter.CENTER)
        self.CNPJLabel.grid(row=0, column=0, padx=10, pady=(10,0), sticky="new")

        self.CNPJInput = customtkinter.CTkEntry(self, placeholder_text="Insira o CNPJ aqui")
        self.CNPJInput.grid(row=1, column=0, padx=10, pady=(0,10), sticky="new")

        self.CNPJradioLabel = customtkinter.CTkLabel(self, text="Opções rápidas")
        self.CNPJradioLabel.grid(row=2, column=0, padx=10, pady=(10,5), sticky="nsew")

        # CNPJ Radio Buttons
        self.CNPJProfiles = {
            "Outro"          : "Outro",
            "Marel Gabriel"  : "35.522.657/0001-01",
            "Analia Franco"  : "36.617.616/0001-53",
            "Marel Portugal" : "11.372.614/0004-63"
        }
        
        row = 3
        self.radioVar = customtkinter.StringVar(value="None")
        for key, value in self.CNPJProfiles.items():
            self.button = customtkinter.CTkRadioButton(
                self, text=key, value=value, command=self.radioButtonFunction, variable=self.radioVar)
            self.button.grid(row=row, column=0, padx=10, pady=5, sticky="new")
            row = row + 1

        #Labels e Inputs
        self.valorLabel = customtkinter.CTkLabel(self, text="Valor da nota:", anchor=tkinter.CENTER)
        self.valorLabel.grid(row=7, column=0, padx=10, pady=(10,0), sticky="new")
        self.valorInput = customtkinter.CTkEntry(self, placeholder_text="Insira o valor aqui")
        self.valorInput.grid(row=8, column=0, padx=10, pady=(0,10), sticky="new")

        self.emailLabel = customtkinter.CTkLabel(self, text="Email de envio")
        self.emailLabel.grid(row=9, column=0, padx=10, pady=(10,0), sticky="nsew")
        self.emailInput = customtkinter.CTkEntry(self, placeholder_text="Insira o email aqui")
        self.emailInput.grid(row=10, column=0, padx=10, pady=(0,10), sticky="nsew")

    # Configura o placeholder text / Mostra o CNPJ da loja selecionada
    def radioButtonFunction(self):
        self.CNPJInput.configure(state="normal")
        self.CNPJInput.delete(0,tkinter.INSERT)
        if self.radioVar.get() == "Outro":
            self.CNPJInput.configure(placeholder_text="Insira o CNPJ aqui")
        else:
            self.CNPJInput.insert(tkinter.INSERT, self.radioVar.get())
            self.CNPJInput.configure(state="disabled")


class cadastrar(customtkinter.CTkFrame):
    def __init__(self, master) -> None:
        super().__init__(master)

        # Grid Config
        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure(0, weight=1)
        self.cadastrarStatus = False
        self.enablePergunta()

    # Gera o frame de pergunta na tab cadastrar
    def enablePergunta(self):

        print("cadastrar status:", self.cadastrarStatus)

        # PERGUNTA FRAME
        self.perguntaFrame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.perguntaFrame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

        self.perguntaFrame.grid_rowconfigure(0, weight=1)
        self.perguntaFrame.grid_columnconfigure(0, weight=1)

        self.perguntaLabel = customtkinter.CTkLabel(self.perguntaFrame, text="Deseja cadastrar algum cliente?")
        self.perguntaLabel.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

        self.buttonConfirm = customtkinter.CTkButton(self.perguntaFrame, text="Sim", command=self.disablePergunta)
        self.buttonConfirm.grid(row=1, column=0, padx=10, pady=10)
        
    # Gera o frame de cadastro na tab de cadastrar
    def enableInputCadastrar(self):
        
        print("cadastrar status:", self.cadastrarStatus)

        self.perguntaFrame.destroy()

        self.cadastrarInputFrame = customtkinter.CTkFrame(self, fg_color="transparent")

        self.cadastrarInputFrame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")
        self.cadastrarInputFrame.grid_columnconfigure((0,1), weight=1)
        self.cadastrarInputFrame.grid_rowconfigure((0,1,2,3,4), weight=1)

        self.nomeLabel = customtkinter.CTkLabel(self.cadastrarInputFrame, text="Nome completo")
        self.nomeLabel.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")
        self.nomeInput = customtkinter.CTkEntry(self.cadastrarInputFrame, placeholder_text="Insira o nome aqui")
        self.nomeInput.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

        self.CNPJLabel = customtkinter.CTkLabel(self.cadastrarInputFrame, text="CNPJ/CPF")
        self.CNPJLabel.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")
        self.CNPJInput = customtkinter.CTkEntry(self.cadastrarInputFrame, placeholder_text="Insira o CNPJ/CPF aqui")
        self.CNPJInput.grid(row=1, column=1, padx=10, pady=10, sticky="nsew")

        self.CEPLabel = customtkinter.CTkLabel(self.cadastrarInputFrame, text="CEP")
        self.CEPLabel.grid(row=2, column=0, padx=10, pady=10, sticky="nsew")
        self.CEPInput = customtkinter.CTkEntry(self.cadastrarInputFrame, placeholder_text="Insira o CEP aqui")
        self.CEPInput.grid(row=2, column=1, padx=10, pady=10, sticky="nsew")

        self.numeroLabel = customtkinter.CTkLabel(self.cadastrarInputFrame, text="Numero residencial")
        self.numeroLabel.grid(row=3, column=0, padx=10, pady=10, sticky="nsew")
        self.numeroInput = customtkinter.CTkEntry(self.cadastrarInputFrame, placeholder_text="Insira o numero aqui")
        self.numeroInput.grid(row=3, column=1, padx=10, pady=10, sticky="nsew")

        self.complementoLabel = customtkinter.CTkLabel(self.cadastrarInputFrame, text="Complemento")
        self.complementoLabel.grid(row=4, column=0, padx=10, pady=10, sticky="nsew")
        self.complementoInput = customtkinter.CTkEntry(self.cadastrarInputFrame, placeholder_text="Insira o complemento aqui")
        self.complementoInput.grid(row=4, column=1, padx=10, pady=10, sticky="nsew")

        self.cancelButton = customtkinter.CTkButton(self.cadastrarInputFrame, text="Cancelar", command=self.disableCadastrar, fg_color="red")
        self.cancelButton.grid(row=5, column=0, columnspan=2, padx=10, pady=10)

    # faz as transições dos frames
    def disableCadastrar(self):
        self.cadastrarStatus = False
        self.cadastrarInputFrame.destroy()
        self.enablePergunta()

    def disablePergunta(self):
        self.cadastrarStatus = True
        self.perguntaFrame.destroy()
        self.enableInputCadastrar()
    
    
class tabView(customtkinter.CTkTabview):
    def __init__(self, master) -> None:
        super().__init__(master)

        # adicionando e configurando tab emissão
        self.add("Emissão")
        self.tab("Emissão").grid_columnconfigure(1, weight=1)
        self.tab("Emissão").grid_rowconfigure(0, weight=1)
        self.entry = entryFrame(self.tab("Emissão"))
        self.entry.grid(row=0, column= 0, padx=10, pady=10, sticky="nsew")
        self.emissao = emissaoFrame(self.tab("Emissão"))
        self.emissao.grid(row=0, column=1, columnspan=3, padx=10, pady=10, sticky="nsew")

        # adicionando e configurando tab cadastrar
        self.add("Cadastrar")
        self.tab("Cadastrar").grid_columnconfigure(0, weight=1)
        self.tab("Cadastrar").grid_rowconfigure(0, weight=1)
        self.cadastro = cadastrar(self.tab("Cadastrar"))
        self.cadastro.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

    # retorna os valores dos inputs para a classe Cliente
    def returnClienteValues(self):
        tuple = (
            self.cadastro.nomeInput.get(),
            self.cadastro.CNPJInput.get(),
            self.cadastro.CEPInput.get(),
            self.cadastro.numeroInput.get(),
            self.cadastro.complementoInput.get()
        )

        return tuple

    # retorna os valores dos inputs para a classe Nota
    def returnNotaValues(self):
        tuple = (
            self.entry.CNPJInput.get(),
            self.entry.valorInput.get(),
            self.emissao.textboxDISCRIMINACAO.get("0.0", tkinter.INSERT),
            self.emissao.servicoRadioVar.get(),
        )

        return tuple

        
class Gui(customtkinter.CTk):
    def __init__(self) -> None:
        super().__init__()

        # define o tamanho inicial da janela
        self.geometry("900x550")
        self.title("Teste GUI Emitir")

        # Grid config
        self.grid_columnconfigure((1), weight=1)
        self.grid_rowconfigure((0,1), weight=1)

        # adicionando a tabview na master
        self.tabFrame = tabView(self)
        self.tabFrame.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

        # botão de confirmar
        self.confirmButton = customtkinter.CTkButton(self, text="Confirmar", command=self.confirmFunction)
        self.confirmButton.grid(row=1, column=1, padx=10, pady=5)

    # Envia os valores para as classes responsáveis
    def confirmFunction(self):
        nota.getValues(self.tabFrame.returnNotaValues())

        # checa se a função de cadastrar cliente foi acionada e envia o pega o return dos inputs
        if self.tabFrame.cadastro.cadastrarStatus == True:
            cliente.getValues(self.tabFrame.returnClienteValues())

            
cliente = cliente()
nota = nota()
janela = Gui()
janela.mainloop()
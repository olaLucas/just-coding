import customtkinter
import tkinter

customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("blue")

class captchaGUI(customtkinter.CTk): # GUI do captcha
    def __init__(self) -> None: # constructor da janela
        super().__init__()

        self.geometry("400x400")
        self.title("CAPTCHA")

        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure(0, weight=1)


        # Definindo o frame principal
        self.mainFrame = customtkinter.CTkFrame(self, width=200, height=200)
        self.mainFrame.grid(row=0, column=0, padx=10, pady=10)
        self.mainFrame.grid_columnconfigure((0,1,2), weight=0)

        
        # Colocando os widgets
        self.label = customtkinter.CTkLabel(self.mainFrame, text="Insira o codigo CAPTCHA do site")
        self.label.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

        self.entryVar = None
        self.entry = customtkinter.CTkEntry(self.mainFrame, placeholder_text="Código")
        self.entry.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")

        self.button = customtkinter.CTkButton(self.mainFrame, text="Confirmar", command=self.buttonFunction)
        self.button.grid(row=2, column=0, padx=10, pady=10, sticky="nsew")

        self.buttonVar = None

    def buttonFunction(self): # retorna o codigo digitado na entry e fecha a janela
        self.buttonVar = True
        self.entryVar = self.entry.get()
        self.quit()

class GUI(customtkinter.CTk):
    def __init__(self) -> None: # constructor da janela
        super().__init__()

        self.x_window_size = 350
        self.y_window_size = 200

        self.geometry(f"{self.x_window_size}x{self.y_window_size}")
        self.title("Boas vindas!")

        self.columnconfigure(0, weight=1)
        self.rowconfigure(2, weight=1)

        self.welcomeLabel = customtkinter.CTkLabel(
            self, text="Bem vindo!", font=customtkinter.CTkFont("Menlo LGS", 22), anchor=tkinter.CENTER)
        self.welcomeLabel.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

       
        # Definindo o frame principal
        self.mainFrame = customtkinter.CTkFrame(self, width=400, height=400)
        self.mainFrame.grid(row=1, column=0, padx=10, pady=10, sticky="n")
        self.mainFrame.grid_columnconfigure((0,1), weight=0)
        self.mainFrame.grid_rowconfigure((0,1), weight=0)


        # adicionando os widgets ao mainFrame
        self.label = customtkinter.CTkLabel(
            self.mainFrame, text="O que deseja fazer?", font=customtkinter.CTkFont("Menlo LGS", 22), anchor=tkinter.CENTER)
        self.label.grid(row=0, column=0, columnspan=2, padx=10, pady=10)

        self.checkboxCadastrar = customtkinter.CTkCheckBox(self.mainFrame, text="Cadastrar cliente")
        self.checkboxCadastrar.grid(row=1, column=0, padx=10, pady=10)

        self.checkboxEmitir = customtkinter.CTkCheckBox(self.mainFrame, text="Emitir nota")
        self.checkboxEmitir.grid(row=1, column=1, padx=10, pady=10)


janela = GUI()
janela.mainloop()

#anela = captchaGUI()
#janela.mainloop()
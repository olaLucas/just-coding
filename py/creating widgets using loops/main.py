import customtkinter
import tkinter

class gui(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        self.geometry("400x400")
        self.title("Test")

        self.intvar = tkinter.IntVar()
        labels = ["a","b","c", "d"]
        for i in range(len(labels)):
            self.button = customtkinter.CTkRadioButton(self, text=labels[i], variable=self.intvar, value=i, command=self.buttonPressed)
            self.button.grid(row=i, column=0, padx=10, pady=10)


    def buttonPressed(self):
        print("button pressed: ", self.intvar.get())

janela = gui()
janela.mainloop()
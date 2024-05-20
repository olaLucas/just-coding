from tkinter import Tk, Label, Button, TOP, BOTTOM

def button_pressed(butao):
    print('butao, ', butao)

def closing_window():
    print('exiting')
    root.destroy()

num = [['1', '2', '3', '+'],
       ['4', '5', '6', '-'],
       ['7', '8', '9', '*'],
       ['.', '0', '=', '/']]

root = Tk()
label = Label(root, text = 'Calculadora')
label.grid(row = 0, column = len(num[0]) // 2, pady = 5)

button = list()
button_index = 0
for i in range(3):
    for j in range(4):   
        button.append(Button(root,
                             text=num[j][i],
                             command=button_pressed))
        button[button_index].grid(column=i, row=j, padx=3, pady=3)
        button_index += 1

close_button = Button(text='Close', command=closing_window)
close_button.grid(row = len(num) + 1, 
                  column = len(num[0]) // 2, 
                  pady = 5)

root.mainloop()                

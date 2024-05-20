from tkinter import Tk, Label, Frame, Button
from os import sys

'''
using Zeller's Congruence
h = (q + [13(m+1)/5] + K + [K/4] [J/4] - 2J) mod 7
h = week day
q = month day
m = month
K = century year
J = century
'''
def zeller(y, m, q):
   
    # consider january and february as 13th and 14th month of the previously year
    if m < 3:
        y -= 1
        m += 12

    J = y // 100
    K = y % 100

    return (q + (13 * (m + 1) // 5) + K + (K // 4) + (J // 4) - 2 * J) % 7 

def monthrange(y, m):
    
    end_day = -1
    months_end_days = { 1: 31, 3: 31, 4: 30, 
                        5: 31, 6: 30, 7: 31, 
                        8: 31, 9: 30, 10: 31, 
                       11: 30, 12: 31 }
    if m != 2:
        end_day = months_end_days.get(m)
    else: # check for ano bissexto :)
        x = 4
        mod = y % 100
        while True:
            if x == mod:
                end_day = 29
                break
            elif x > mod:
                end_day = 28
                break
            else:
                x += 4    

    first_day = zeller(y, m, 1)
    if first_day == 0:
        first_day = 6
    else:
        first_day -= 1

    return (first_day, end_day)

def drawcalendar(frame, start_day, end_day):
    week_days = ['Dom', 'Seg', 'Ter','Qua','Qui', 'Sex', 'Sab']
    for i in range(len(week_days)):
        week_days_label = Label(frame, text = f'{week_days[i]}')
        week_days_label.grid(row = 0, column = i, padx = 3, pady = 3)
        
    j = start_day
    table_row = 1
    day_counter = 1
    while day_counter <= end_day: # row loop
        while j < len(week_days): # column loop
            day = Label(frame, text = f'{day_counter}')
            day.grid(row = table_row, column = j, padx = 3, pady = 3)
            day_counter += 1
            j += 1
            if day_counter > end_day:
                break
        j = 0
        table_row += 1


def calendar(month, year):
    root = Tk()

    months = { 1: 'Jan', 2: 'Fev', 3: 'Mar',
               4: 'Abr', 5: 'Mai', 6: 'Jun',
               7: 'Jul', 8: 'Ago', 9: 'Sep',
              10: 'Out', 11: 'Nov', 12: 'Dec' }

    prev_month = Button(root, text = '<', command = lambda: prev_month(month))
    prev_month.grid(row = 0, column = 0, padx = 3, pady = 3)

    label = Label(root, text = f'{months[month]}, {year}', font = ('JetBrainsMono', 14, 'bold'))
    label.grid(row = 0, column = 1, padx = 3, pady = 3)

    next_month = Button(root, text = '>', command = lambda: next_month(month))
    next_month.grid(row = 0, column = 2, padx = 3, pady = 3)

    days_frame = Frame(root)
    days_frame.grid(row = 1, column = 0, padx = 5, pady = 5)
    
    start_day, month_days = monthrange(year, month)
    drawcalendar(days_frame, start_day, month_days)
    
    root.mainloop()

# TODO: permitir trocar de m√s clicando nos bot√es  

def terminal_args():
    month = 0
    year = 0
    for i in range(len(sys.argv)):
        if sys.argv[i] == '-y' or sys.argv[i] == '--year':
            year = int(sys.argv[i + 1])
            i += 1
        elif sys.argv[i] == '-m' or sys.argv[i] == '--month':
            month = int(sys.argv[i + 1])
            i += 1

    return (month, year)

# caso queira rodar pelo terminal, passando os argumentos como:
# python3 calendar.py --month 2 --year 2024
month, year = terminal_args()
calendar(month, year)

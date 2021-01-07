from tkinter import *

from random import randint

 

def clck(event):

    print(event.widget.row, event.widget.col)

    if event.widget.is_pig_here:

        event.widget.config(bg="green", text="\uD83D\uDC37", font="Arial 50", borderwidth=20)

    else:

        event.widget.config(bg="red", text="\u0460", font="Arial 40", borderwidth=23)

 

root = Tk()

 

for row in range(2):

    for col in range(2):

        lbl = Label(root, text=', '.join([str(row), str(col)]), bg="sky blue", borderwidth=50)

        # Добавляем свои атрибуты: row, col, is_pig_here

        lbl.row = row

        lbl.col = col

        lbl.is_pig_here = randint(0, 1)

        

        lbl.bind("<Button-1>", clck)

        lbl.grid(row=row, column=col, padx=1, pady=1, sticky = 'nesw')       

 

root.mainloop()

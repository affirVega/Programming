from tkinter import *

root = Tk()
for row in range(2):
    for col in range(2):
        lbl = Label(root,
                    text=', '.join([str(row), str(col)]),
                    bg="sky blue",
                    borderwidth=50)    # Ширина гриницы Lable
        lbl.grid(row=row,     # Номер строки начиная с 0
                 column=col,  # Номер столбца начиная с 0
                 padx=1,      # Отступ от левого и правого края ячейки сетки
                 pady=1)      # Отступ от верхнего и нижнего края ячейки сетки 
 
root.mainloop()

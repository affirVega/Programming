from tkinter import *

from PIL import ImageTk

 

def set_img2(event):

    event.widget.config(image=img_2)

 

root = Tk()

img = ImageTk.PhotoImage(file="ball-green.png")

img_2 = ImageTk.PhotoImage(file="ball-blue.png")

 

for row in range(2):

    for col in range(2):

        lbl = Label(root, image = img, borderwidth=0)

        lbl.bind("<Button-1>", set_img2)

        lbl.grid(row=row, column=col, padx=1, pady=1)       

 

root.mainloop()

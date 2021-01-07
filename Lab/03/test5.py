from tkinter import *

from PIL import Image, ImageTk

 

def set_img2(event):

    event.widget.config(image=img_2)

 

root = Tk()

tileset = Image.open("cell-bgr.png")

img = ImageTk.PhotoImage(tileset.crop((1, 0, 67, 66)))

img_2 = ImageTk.PhotoImage(tileset.crop((1, 69, 67, 135)))

 

for row in range(2):

    for col in range(2):

        lbl = Label(root, image = img, borderwidth=0)

        lbl.bind("<Button-1>", set_img2)

        lbl.grid(row=row, column=col, padx=1, pady=1)       

 

root.mainloop()

from tkinter import *
from PIL import ImageTk
 
root = Tk()
img = ImageTk.PhotoImage(file="ball-green.png")
Label(root, image=img, borderwidth=0).pack()
 
root.mainloop()

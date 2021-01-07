from tkinter import *
 
root = Tk()
root.geometry("290x300")
for i in range(4):
    lbl = Label(root, text=str(i), bg="sky blue", borderwidth=50)
    lbl.place(x=60*i,  # Смещение влева на право в пикселах
              y= 60*i) # Смещение сверху вниз в пикселах   
 
root.mainloop()

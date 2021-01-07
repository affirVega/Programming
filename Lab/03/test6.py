from tkinter import *

from PIL import Image, ImageTk

 

root = Tk()

bgr = Image.open("page-bgr.png").convert('RGBA')

ball = Image.open("ball-blue.png").convert('RGBA')

 

# Метод paste изменяет изображение-подложку

bgr.paste(ball,   # Накладываемая картинка

          (0,0),  # Сместить картинку на (x, y) пикселей

          ball)   # Маска прозрачности. Делаем из самого изображения

 

img = ImageTk.PhotoImage(bgr)

 

Label(root, image = img, borderwidth=0).pack()

 

root.mainloop()

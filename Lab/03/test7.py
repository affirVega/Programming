from tkinter import *

from PIL import Image, ImageTk

 

root = Tk()

bgr = Image.open("page-bgr.png").convert('RGBA')

ball = Image.open("ball-blue.png").convert('RGBA')

 

pic_size_same_as_bgr = Image.new("RGBA", bgr.size)

pic_size_same_as_bgr.paste(ball, (70,0)) # Маска не нужна

ball_over_bgr = Image.alpha_composite(bgr, pic_size_same_as_bgr)

 

ball_over_bgr.paste(ball, (0,0), ball) # Для сравнения (можно убрать)

 

img = ImageTk.PhotoImage(ball_over_bgr)

 

Label(root, image = img, borderwidth=0).pack()

 

root.mainloop()

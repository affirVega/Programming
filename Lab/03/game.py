from tkinter import *
from PIL import ImageTk, Image
import random

root = Tk()
# root.wm_attributes("-transparentcolor", 'grey')

_assets = {}
assets = {}
ball_by_index = []

class Cell:
    image: Image
    imagetk: ImageTk.PhotoImage
    label: Label # self <- label.owner
    color: int
    variant: int

CellMatrix = []

N, M = 9, 9

ProcessClicks: bool = True
SelectedCell: Cell = None

def load_assets():
    global _assets, assets
    _assets.update({
        "cell" : Image.open("cell-bgr.png").convert('RGBA'),
        "page" : Image.open("page-bgr.png").convert('RGBA'),
    })
    _assets.update({
        "cell_dark" : _assets["cell"].crop( (2, 1, 66, 65) ),
        "cell_light" : _assets["cell"].crop( (2, 70, 66, 134) ),
    })
    assets.update({
        "cell_dark" : ImageTk.PhotoImage(_assets["cell_dark"]),
        "cell_light" : ImageTk.PhotoImage(_assets["cell_light"]),
        "page" : ImageTk.PhotoImage(_assets["page"])
    })

    _assets_balls = {
        "pink"   : Image.open("ball-pink.png").convert('RGBA'),
        "red"    : Image.open("ball-red.png").convert('RGBA'),
        "yellow" : Image.open("ball-yellow.png").convert('RGBA'),  
        "green"  : Image.open("ball-green.png").convert('RGBA'),
        "aqua"   : Image.open("ball-aqua.png").convert('RGBA'),
        "blue"   : Image.open("ball-blue.png").convert('RGBA'),
        "violet" : Image.open("ball-violet.png").convert('RGBA'),
    }
    ball_by_index = [
        "pink",  
        "red",   
        "yellow",
        "green", 
        "aqua",  
        "blue",  
        "violet"
    ]

    for k, v in _assets_balls.items():
        for i in range(7):
            _assets[f"{k}_{i}"] = v.crop( (0, i*60, 55, i*60 + 55) )
            assets[f"{k}_{i}"] = ImageTk.PhotoImage(_assets[f"{k}_{i}"])

def update_background(canvas):
    bgimg = assets['page']

    root.update() # для обновления размеров

    y = 0
    while y-bgimg.height() < root.winfo_height():
        x = 0
        while x-bgimg.width() < root.winfo_width():
            canvas.create_image(x, y,
                                image=bgimg)
            x += bgimg.width()  
            
        y += bgimg.height()
    
def create_cells():
    global CellMatrix
    gridframe = Frame(root, bg='grey')
    for row in range(N):
        CellMatrix.append(list())
        for col in range(M):
            cell = Cell()
            cell.image = _assets['cell_dark']
            cell.imagetk = assets['cell_dark']
            cell.color = random.randint(0, 6) # [0, 6]
            cell.size = -1

            cell.label = Label(gridframe, image=cell.imagetk, borderwidth=0)
            cell.label.bind('<Button-1>',
                            lambda event, thisrow=row, thiscol=col: cell_click(event, thisrow, thiscol))
            cell.label.grid(row=row, column=col, padx=2, pady=2)

            cell.label.owner = cell
            CellMatrix.append(cell)
    gridframe.grid(column=0, row=0)

def update_cells():
    global CellMatrix
    for row in range(len(CellMatrix)):
        for col in range(len(CellMatrix[0])):
            CellMatrix[row][col].label.update()

def create_info():
    title = Label(root, text="Линии 2")
    score = Label(root, text="Счёт: ")
    


    

def update_everything():
    
    
    
    
    pass

def cell_click(event, row, col):
    global ProcessClicks
    if not ProcessClicks:
        return
    
    print('Event:', event, '\nrow =', row, 'col =', col)
    pass

if __name__ == '__main__':
    load_assets()

    canvas = Canvas(root, borderwidth=0)
    
    create_cells()

    canvas.place(x=-1, y=-1,
                relwidth=1,
                relheight=1)
    
    update_background(canvas)

    try:

        while True:
            root.update()
            update_everything()

    except TclError as e:
        exit()
    except Exception as e:
        print('Error:', e)
        exit()

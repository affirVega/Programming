import random
from tkinter import *
from PIL import Image, ImageTk

root = Tk()

assets = {}
assets_tk = {}
balls = {}
balls_tk = {}

# matrix
game_field = []
window_width, window_height = 0, 0
WINDOW_PADDING_VERTICAL = 20
WINDOW_PADDING_HORIZONTAL = 30

selected_cell = None

class Cell:
    _image: Image
    _image_tk: ImageTk.PhotoImage

    def __init__(self,
            row,
            col,
            canvas_id = -1,
            size = 0,
            color = None,
            selected = False,
            has_cell = True):
        self.row = row
        self.col = col
        self.size = size
        self.color = color
        self.selected = selected

        self._canvas_id = canvas_id
        self._has_cell = has_cell

    def is_empty(self):
        return self.size == -1 or self.color == None 

    def make_empty(self):
        self.size = -1
        self.color = None
    
    def update_image(self, canvas):
        global assets, assets_tk, balls, balls_tk
        self._image = Image.new("RGBA", assets['cell_dark'].size)

        if not self.is_empty():
            self._image.paste(balls[self.color][self.size], (5, 5))

        if self._has_cell:
            if self.selected:
                self._image = Image.alpha_composite(assets['cell_light'], self._image)
            else:
                self._image = Image.alpha_composite(assets['cell_dark'], self._image)
        
        self._image_tk = ImageTk.PhotoImage(self._image)
        if self._canvas_id != -1:
            canvas.itemconfigure(self._canvas_id, image=self._image_tk)

    def on_click(self, event, canvas):
        global selected_cell
        if selected_cell == self:
            return
        
        if selected_cell != None:
            selected_cell.selected = False
            selected_cell.update_image(canvas)
            return
            
        self.selected = True
        self.update_image(canvas)
        selected_cell = self

    def set_random_color(self):
        i = random.randint(0, len(balls) - 1)
        j = 0
        for color in balls.keys():
            if i == j:
                self.color = color
                return
            j += 1
        
def load_assets():
    global assets, assets_tk, balls, balls_tk
    # Load raw images:
    assets.update({
        '_cell' : Image.open("assets/cell-bgr.png").convert('RGBA'),
    })
    temp_balls = {
        "pink"   : Image.open("assets/ball-pink.png").convert('RGBA'),
        "red"    : Image.open("assets/ball-red.png").convert('RGBA'),
        "yellow" : Image.open("assets/ball-yellow.png").convert('RGBA'),  
        "green"  : Image.open("assets/ball-green.png").convert('RGBA'),
        "aqua"   : Image.open("assets/ball-aqua.png").convert('RGBA'),
        "blue"   : Image.open("assets/ball-blue.png").convert('RGBA'),
        "violet" : Image.open("assets/ball-violet.png").convert('RGBA'),
    }

    # create usable images

    for name, image in temp_balls.items():
        balls[name] = list()
        balls_tk[name] = list()
        for size in range(7):
            balls[name].append(image.crop((0, size*60, 55, size*60 + 55)))
            balls_tk[name].append(ImageTk.PhotoImage(image.crop((0, size*60, 55, size*60 + 55))))
    
    assets.update({
        "cell_dark"  : assets["_cell"].crop((2, 1, 67, 66)),
        "cell_light" : assets["_cell"].crop((2, 70, 67, 135)),
        'page' : Image.open("assets/page-bgr.png").convert('RGBA')
    })
    for name, image in assets.items():
        assets_tk[name] = ImageTk.PhotoImage(image)


def create_canvas(width, height):
    root.update()

    global assets, assets_tk
    bgimg = assets_tk['page']

    w = width
    h = height
    canvas = Canvas(root, width=w, height=h)

    x = 0
    while x - bgimg.width() < width:
        y = 0
        while y - bgimg.height() < height:
            canvas.create_image(x, y, image=bgimg)
            y += bgimg.height()
        x += bgimg.width()  
    
    return canvas

def create_game_field(canvas, rows, cols):
    global game_field

    for row in range(rows):
        game_field.append(list())
        for col in range(cols):
            cell = Cell(row, col, has_cell=True)
            game_field[row].append(cell)

def create_info(canvas):
    global window_width, window_height

    text_font = ('Arial', 20)
    text_color = '#ffffff'
    
    local_height = WINDOW_PADDING_VERTICAL
    local_width = window_width + WINDOW_PADDING_HORIZONTAL
    canvas.create_text(
        local_width,
        local_height,
        anchor=NW,
        text='Lines 2: Electric Boogaloo',
        font=text_font,
        fill=text_color)

    local_height += 40
    canvas.create_text(
        local_width,
        local_height,
        anchor=NW,
        text='Счёт: ',
        font=text_font,
        fill='white')
    score_text = canvas.create_text(
        local_width + 70,
        local_height,
        anchor=NW,
        text='0',
        font=text_font,
        fill='white')

    local_height += 40
    Button(root,
            text='Сделать ход',
            command=lambda: print('Сделать ход')).place(
        x=local_width,
        y=local_height,
        anchor=NW)

    local_height += 40
    hints = []
    for i in range(3):
        hints.append(Cell(-1, -1, has_cell=False))
        hints[i]._canvas_id = canvas.create_image(
            local_width + 60*i,
            local_height,
            anchor=NW,
            image=balls_tk['red'][0])

    local_height += 80
    Button(root,
            text='Новая игра',
            command=lambda: print('Новая игра')).place(
        x=local_width,
        y=local_height,
        anchor=NW)
    
    window_width = local_width + WINDOW_PADDING_HORIZONTAL + 300

    return score_text, hints

def place_cells(canvas):
    global game_field, window_width, window_height

    gap = 5
    cell_width  = assets_tk['cell_dark'].width() 
    cell_height = assets_tk['cell_dark'].height() 

    for col in range(len(game_field[0])):
        window_width = WINDOW_PADDING_HORIZONTAL + col*cell_width  + col*gap
        for row in range(len(game_field)):
            window_height = WINDOW_PADDING_VERTICAL + row*cell_height + row*gap

            game_field[row][col].update_image(canvas)
            game_field[row][col]._canvas_id = canvas.create_image(
                window_width, # x
                window_height, # y
                image=game_field[row][col]._image_tk,
                anchor=NW)
            game_field[row][col].update_image(canvas)
            canvas.tag_bind(game_field[row][col]._canvas_id,
                    '<Button-1>',
                    lambda event, r=row, c=col: game_field[r][c].on_click(event, canvas))

    window_width += cell_width
    window_height += cell_height

def generate_hint(canvas, hints):
    for cell in hints:
        cell.set_random_color()
        cell.size = 0
        cell.update_image(canvas)
    pass

def place_hint(canvas, hints):
    free_cells = []
    for row in game_field:
        for cell in row:
            if cell.is_empty():
                free_cells.append(cell)
    for cell in hints:
        to_replace = free_cells[random.randint(0, len(free_cells)-1)]
        to_replace.color = cell.color
        to_replace.update_image(canvas)
    pass

if __name__ == '__main__':
    MATRIX_ROWS = 9
    MATRIX_COLS = 9

    load_assets()
    canvas = create_canvas(1200, 1000)
    canvas.place(x=0, y=0)

    create_game_field(canvas, MATRIX_ROWS, MATRIX_COLS)
    place_cells(canvas)

    score_text, hints = create_info(canvas)
    generate_hint(canvas, hints)
    place_hint(canvas, hints)
    generate_hint(canvas, hints)
    
    root.geometry(f'{window_width + WINDOW_PADDING_HORIZONTAL}x{window_height + WINDOW_PADDING_VERTICAL}')
    root.mainloop()

maze = [
    "####B######################",
    "# #       #   #      #    #",
    "# # # ###### #### ####### #",
    "# # # #       #   #       #",
    "#   # # ######### # ##### #",
    "# # # #   #       #     # #",
    "### ### ### ############# #",
    "# #   #     # #           #",
    "# # #   ####### ###########",
    "# # # #       # #         C",
    "# # ##### ### # # ####### #",
    "# # #     ### # #       # #",
    "#   ##### ### # ######### #",
    "######### ### #           #",
    "# ####### ### #############",
    "A           #   ###   #   #",
    "# ############# ### # # # #",
    "# ###       # # ### # # # #",
    "# ######### # # ### # # # F",
    "#       ### # #     # # # #",
    "# ######### # ##### # # # #",
    "# #######   #       #   # #",
    "# ####### ######### #######",
    "#         #########       #",
    "#######E############D######"
]
#maze_copy = maze[:]
visited = []
exits = []

def crawl_maze(x, y):
    if maze[x][y] == "#" or abs(y) >= len(maze[0]) or abs(x) >= len(maze):
        print("Не верные координаты")
        return
        
    if maze[x][y] != " " and not maze[x][y] in exits:
        exits.append(maze[x][y])
    
    else:
        if maze[x][y+1] != "#" and not (x, y+1) in visited:
            visited.append((x, y+1))
            crawl_maze(x, y+1)
            
        if maze[x][y-1] != "#" and not (x, y-1) in visited:
            visited.append((x, y-1))
            crawl_maze(x, y-1)

        if maze[x+1][y] != "#" and not (x+1, y) in visited:
            visited.append((x+1, y))
            crawl_maze(x+1, y)

        if maze[x-1][y] != "#" and not (x-1, y) in visited:
            visited.append((x-1, y))
            crawl_maze(x-1, y)

def print_maze():
    print("\n     ", end='')
    for i in range(len(maze[0])):
        print(i % 10, end='')
    print()

    for index, line in enumerate(maze):
        print(" {:3d} {}".format(index, line))
    print()

# print_maze()
x, y = map(int, input("Введите координаты: ").split())
crawl_maze(x, y)

# exits.sort()
# print("visited indicies:", visited)

print(exits)
# visited.clear()
# exits.clear()

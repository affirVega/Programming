#include <iostream>
#include <vector>     // for using dynamic arrays
#include <algorithm>  // for std::find
#include <iterator>   // for std::size

using visits_t = std::vector<std::pair<int, int>>;
using exits_t  = std::vector<char>;

const std::string maze[] = {
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
};

void crawl_maze(visits_t& visited, exits_t& exits, int x, int y) {
	
	// if x and y are in bounds of array and are >= 0, skip
	if (   x < 0 || x >= maze[0].length()
		|| y < 0 || y >= std::size(maze)
		|| maze[y][x] == '#') {
		return;
	}

	// if (x, y) dot was visited, skip
	if (std::find(visited.begin(), visited.end(), std::make_pair(x, y)) != visited.end()) {
		return;
	}

	// mark (x, y) dot as visited
	visited.push_back(std::make_pair(x, y));

	// if this dot does not contain ' ' (it can't contain '#'), then it must be exit
	// is this exit doesn't exist, add it
	if (maze[y][x] != ' '
		&& std::find(exits.begin(), exits.end(), maze[y][x]) == exits.end()) {
		exits.push_back(maze[y][x]);
	}
		
	// crawl maze up, down, left and right from this point
	crawl_maze(visited, exits, x+1, y);
	crawl_maze(visited, exits, x-1, y);
	crawl_maze(visited, exits, x, y+1);
	crawl_maze(visited, exits, x, y-1);

}

int main() {
	
	visits_t visited;
	exits_t  exits;

	int x, y;
	std::cout << "Введите координаты x, y через пробел: ";
	std::cin >> x >> y;

	if (   x < 0 || x >= maze[0].length()
		|| y < 0 || y >= std::size(maze)
		|| maze[y][x] == '#') {
		std::cout << "Неверные координаты" << std::endl;
		return 0;
	}
	
	crawl_maze(visited, exits, x, y);

	for (char e : exits) {
		std::cout << e << " ";
	}   std::cout << std::endl;

}

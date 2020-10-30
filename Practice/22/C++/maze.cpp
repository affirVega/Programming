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

bool is_wall_or_bad_point(int x, int y) {
	return x < 0 || x >= maze[0].length()
	|| y < 0 || y >= std::size(maze)
	|| maze[y][x] == '#';
}

void crawl_maze(visits_t& visited, exits_t& exits, int x, int y) {
	
	if (is_wall_or_bad_point(x, y)) {
		return;
	}

	if (std::find(visited.begin(), visited.end(), std::make_pair(x, y)) != visited.end()) {
		return;
	}

	visited.push_back(std::make_pair(x, y));

	if (maze[y][x] != ' '
		&& std::find(exits.begin(), exits.end(), maze[y][x]) == exits.end()) {
		exits.push_back(maze[y][x]);
	}
		
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

	if (is_wall_or_bad_point(x, y)) {
		std::cout << "Неверные координаты" << std::endl;
	} else {
		crawl_maze(visited, exits, x, y);

		if (exits.size() != 0) {
			for (char e : exits) {
				std::cout << e << " ";
			}
		} else {
			std::cout << "Выходов нет";
		}   std::cout << std::endl;
	}

}

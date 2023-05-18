#include <iostream>
#include <math.h>
#include <crtdbg.h>

#define START -2
#define END -1
#define EMPTY 0
#define WALL -3
#define PATH -9

//Axes:
//     Y^
//     X->

//prints the given matrix on the screen
void print_matrix(int** matrix, int height, int width)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (matrix[row][col] > 0 && matrix[row][col] < 10)
				std::cout << "0";
			std::cout << matrix[row][col] << " ";
		}
		std::cout << '\n';
	}
}

//fills the matrix with distances from the start point to the end point using breadth first search
void breadth_first_search(int** matrix, int height, int width, int crt_x, int crt_y)
{

}

void improvised_pathfinding(int** matrix, int height, int width, int crt_x, int crt_y)
{
	//if I'm here, the current node is valid

	//by a valid node I mean that this function has to be run for that node as it is currently not having the correct value asssessed to it

	//checking if the 4 neighbours are valid & assesing the value of the current node
	int min = width * height + 1;
	bool is_under_valid = false, is_above_valid = false, is_left_valid = false, is_right_valid = false;
	bool is_next_to_start = false;
	//std::cout << "'" << matrix[crt_y][crt_x] << "'";
	//under
	if (crt_y + 1 < height)
		if (matrix[crt_y + 1][crt_x] == START)
			is_next_to_start = true;
		else
			if (matrix[crt_y + 1][crt_x] != END)
			{
				is_under_valid = true;
				if (matrix[crt_y + 1][crt_x] < min && matrix[crt_y + 1][crt_x] != EMPTY)
					min = matrix[crt_y + 1][crt_x];
			}
	//above
	if (crt_y > 0)
		if (matrix[crt_y - 1][crt_x] == START)
			is_next_to_start = true;
		else
			if (matrix[crt_y - 1][crt_x] != END)
			{
				is_above_valid = true;
				if (matrix[crt_y - 1][crt_x] < min && matrix[crt_y - 1][crt_x] != EMPTY)
					min = matrix[crt_y - 1][crt_x];
			}
	//left
	if (crt_x > 0)
		if (matrix[crt_y][crt_x - 1] == START)
			is_next_to_start = true;
		else
			if (matrix[crt_y][crt_x - 1] != END)
			{
				is_left_valid = true;
				if (matrix[crt_y][crt_x - 1] < min && matrix[crt_y][crt_x - 1] != EMPTY)
					min = matrix[crt_y][crt_x - 1];
			}
	//right
	if (crt_x + 1 < width)
		if (matrix[crt_y][crt_x + 1] == START)
			is_next_to_start = true;
		else
			if (matrix[crt_y][crt_x + 1] != END)
			{
				is_right_valid = true;
				if (matrix[crt_y][crt_x + 1] < min && matrix[crt_y][crt_x + 1] != EMPTY)
					min = matrix[crt_y][crt_x + 1];
			}

	if (is_next_to_start)
		matrix[crt_y][crt_x] = 1;
	else
		if (matrix[crt_y][crt_x] != START && min != width * height + 1)
			matrix[crt_y][crt_x] = min + 1;

	//print_matrix(matrix, height, width);
	//std::cout << "\n\n";


	//checking if the correct values were assigned to the neigbours of the current node & if the neigbours are empty or not
	//under
	if (is_under_valid)
		if (matrix[crt_y + 1][crt_x] != EMPTY && abs(matrix[crt_y][crt_x] - matrix[crt_y + 1][crt_x]) == 1)
			is_under_valid = false;
	//above
	if (is_above_valid)
		if (matrix[crt_y - 1][crt_x] != EMPTY && abs(matrix[crt_y][crt_x] - matrix[crt_y - 1][crt_x]) == 1)
			is_above_valid = false;
	//left
	if (is_left_valid)
		if (matrix[crt_y][crt_x - 1] != EMPTY && abs(matrix[crt_y][crt_x] - matrix[crt_y][crt_x - 1]) == 1)
			is_left_valid = false;
	//right
	if (is_right_valid)
		if (matrix[crt_y][crt_x + 1] != EMPTY && abs(matrix[crt_y][crt_x] - matrix[crt_y][crt_x + 1]) == 1)
			is_right_valid = false;

	//running the function for the valid neighbours
	if (is_under_valid)
		improvised_pathfinding(matrix, height, width, crt_x, crt_y + 1);
	if (is_above_valid)
		improvised_pathfinding(matrix, height, width, crt_x, crt_y - 1);
	if (is_left_valid)
		improvised_pathfinding(matrix, height, width, crt_x - 1, crt_y);
	if (is_right_valid)
		improvised_pathfinding(matrix, height, width, crt_x + 1, crt_y);

}

//marks the shortest path with PATH
void mark_path(int** matrix, int height, int width, int crt_x, int crt_y)
{

}

int main()
{
	const int height = 10, width = 20;
	int** maze;
	
	//allocating memory for the maze
	maze = new int* [height];
	for (int i = 0; i < height; i++)
		maze[i] = new int[width]();

	//setting up maze
	int start_x = 2, start_y = 5, end_x = 14, end_y = 8;
	maze[start_y][start_x] = START;
	maze[end_y][end_x] = END;

	//breadth_first_search(maze, height, width, start_x, start_y);

	improvised_pathfinding(maze, height, width, start_x, start_y);

	print_matrix(maze, height, width);

	//freeing the memory for the maze
	for (int i = 0; i < height; i++)
		delete[] maze[i];
	delete[] maze;

	_CrtDumpMemoryLeaks();
	return 0;
}
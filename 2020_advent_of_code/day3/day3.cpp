#include<iostream>
#include<fstream>
#include<vector>

/*
  This method counts all the trees the toboggan would meet as it traverses its slope from the top left to the bottom.
  
  right - how many places to the right can the sled move
  down - how many places downward can the sled move
  hill = the representation of the hill to traverse

  returns the number of trees intersected when going down the hill with a slope of x units right and y units down.
*/
int count_trees(int right, int down, const std::vector<std::string>& hill)
{
	int modulus = hill[0].length();
	int trees = 0;
	int col = 0;
	int row = 0;

	while (row < hill.size() - 1)
	{
		col += right;
		col %= modulus; // handles wrap around
		row += down;

		if (hill[row].at(col) == '#')
		{
			trees++;
		}
	}

	return trees;
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> lines;

	while (std::getline(f, line, '\n')) 
	{
		lines.push_back(line);
	}

	f.close();

	int part_two_result = 1;

	if ( argc - 2 > 0 && (argc - 2) % 2 == 0)
	{
		for (int i = 2; i < argc; i += 2)
		{
			part_two_result *= count_trees(std::stoi(argv[i]), std::stoi(argv[i + 1]), lines);
		}
		std::cout << "Part 2" << std::endl;
		std::cout << "Result = " << part_two_result << std::endl;
	}
	else
	{
		std::cout << "Part 1" << std::endl;
		std::cout << "Trees = " << count_trees(1, 3, lines) << std::endl;
	}

	return 0;
	
}


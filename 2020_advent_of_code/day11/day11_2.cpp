#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<string>
#include<limits>

enum MapObject { floor, empty_seat, occupied_seat };

int count_occupied(const int& row, const int& col, const int& height, const int& width, const std::vector<MapObject>& map)
{
	int count = 0;
	int row_lower = row > 0 ? row - 1 : row;
	int row_upper = row < height - 1 ? row + 1 : row;

	int col_lower = col > 0 ? col - 1  : col;
	int col_upper = col < width - 1 ? col + 1 : col;

	for (int i = row_lower; i <= row_upper; i++)
	{
		for (int j = col_lower; j <= col_upper; j++)
		{
			if (!(i == row && j == col))
			{
				auto index = i * width + j;
				if (map[index] == MapObject::occupied_seat)
				{
					count++;
				}
			}
		}
	}
	return count;

}

bool process_cell(const std::vector<MapObject>& map, std::vector<MapObject> &swap, const int& height, const int& width, int index)
{
	auto obj = map[index];
	if (obj == MapObject::empty_seat || obj == MapObject::occupied_seat)
	{
		int row = index / width;
		int col = index % width;
		int count = count_occupied(row, col, height, width, map);
		if (obj == MapObject::empty_seat && count == 0)
		{
			swap.push_back(MapObject::occupied_seat);
			return true;
		}
		if (obj == MapObject::occupied_seat && count >= 4)
		{
			swap.push_back(MapObject::empty_seat);
			return true;
		}

	}
	swap.push_back(obj);
	return false;
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<MapObject> map;
	std::vector<MapObject> map2;
	std::vector<MapObject> swap;
	std::unordered_map<char, MapObject> char2enum = 
	{
		{'.', MapObject::floor}, 
		{'L', MapObject::empty_seat}, 
		{'#', MapObject::occupied_seat}
	};

	std::unordered_map<MapObject, char> enum2char = 
	{
		{         MapObject::floor, '.' }, 
		{    MapObject::empty_seat, 'L' }, 
		{ MapObject::occupied_seat, '#' }
	};
	int width = 0;
	int height = 0;


	while (std::getline(f, line)) 
	{
		if (line.size() > 0) 
		{
			width = line.size();
			height++;
			for (int i = 0; i < width; i++)
			{
				auto obj = char2enum[line[i]];
				map.push_back(obj);
				map2.push_back(obj);
			}
		}
	}



	f.close();
	bool changed = false;
	int iter = 0;
	do {
		iter++;
		changed = false;
		for (int i = 0; i < map.size(); i++)
		{
			changed |= process_cell(map, swap, height, width, i);
		}
		map = std::move(swap);
	} while (changed);
	int p1 = 0;

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i] == MapObject::occupied_seat) p1++;
	}

	int p2 = 0;


	std::cout << "Part 1:  " << p1 << std::endl << "Part 2:  " << p2  << std::endl;

	return 0;
	
}


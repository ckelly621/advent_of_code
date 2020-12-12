#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<string>
#include<limits>

enum MapObject { floor, empty_seat, occupied_seat };

int count_occupied(const std::vector<int>& neighbors, const std::vector<MapObject>& map)
{
	int count = 0;
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (map[neighbors[i]] == MapObject::occupied_seat) count++;
	}
	return count;
}

struct SeatMap
{
	int height;
	int width;
	std::vector<MapObject> map;
	std::vector<MapObject> swap;
};

bool changed_cell(SeatMap &seat_map, const int& index, const std::vector<int> neighbors, const int& thresh)
{
	auto obj = seat_map.map[index];
	if (obj == MapObject::empty_seat || obj == MapObject::occupied_seat)
	{
		int count = count_occupied(neighbors, seat_map.map);
		if (obj == MapObject::empty_seat && count == 0)
		{
			seat_map.swap.push_back(MapObject::occupied_seat);
			return true;
		}
		if (obj == MapObject::occupied_seat && count >= thresh)
		{
			seat_map.swap.push_back(MapObject::empty_seat);
			return true;
		}

	}
	seat_map.swap.push_back(obj);
	return false;
}

int solve_map(SeatMap m, 
		const std::unordered_map<int, std::vector<int>>& neighbors,	
		const std::unordered_map<char, MapObject>& char2enum,
	        const std::unordered_map<MapObject, char>& enum2char,
		const int& thresh)	
{
	bool changed = false;
	do {
		changed = false;
		for (int i = 0; i < m.map.size(); i++)
		{
			if (m.map[i] != MapObject::floor) changed |= changed_cell(m, i, neighbors.at(i), thresh);
			else 
			{
				m.swap.push_back(m.map[i]);
			}
		}
		m.map = std::move(m.swap);
	} while (changed);
	int count = 0;

	for (int i = 0; i < m.map.size(); i++)
	{
		if (m.map[i] == MapObject::occupied_seat) count++;
	}
	return count;
}

struct Movement
{
	int dx;
	int dy;
};

bool in_bounds(const int& i, const int& min, const int& max)
{
	return i >= min && i <= max;
}

class neighbor_finder
{
private:
	std::vector<Movement> moves = {	{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
	void find_neighbor_dir(const SeatMap& m, const int& index, const int& dist, const Movement& move, std::vector<int> &neighbors)
	{
		bool see_seat = false;
		int steps = 0;
		int row = index / m.width;
		int col = index % m.width;
		while (steps < dist && !see_seat && in_bounds(row, 0, m.height-1)  && in_bounds(col, 0, m.width-1))
		{
			steps++;
			row += move.dx;
			col += move.dy;
			if (in_bounds(row, 0, m.height-1)  && in_bounds(col, 0, m.width-1))
			{
				auto i = row * m.width + col;
				auto obj = m.map[i];
				if (obj != MapObject::floor)
				{
					see_seat = true;
					neighbors.push_back(i);
				}
			}
		}
	}
public:
	std::vector<int> find_neighbors(const SeatMap& m, const int& index, const int& dist)
	{
		std::vector<int> neighbors;
		if (m.map[index] != MapObject::floor)
		{
			for (int i = 0; i < moves.size(); i++)
			{
				auto move = moves[i];
				find_neighbor_dir(m, index, dist, move, neighbors);
			}
		}
		return neighbors;
	}

};

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<MapObject> map;
	std::vector<MapObject> map2;
	std::vector<MapObject> swap;
	std::vector<MapObject> swap2;
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

	std::unordered_map<int, std::vector<int>> m1_neighbors;
	std::unordered_map<int, std::vector<int>> m2_neighbors;

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

	neighbor_finder finder;

	SeatMap m1 = { height, width, map, swap };
	SeatMap m2 = { height, width, map2, swap2 };
	auto m2_dist = m2.height * m2.width;
	for (int i = 0; i < m1.map.size(); i++)
	{
		auto obj = m1.map[i];
		m1_neighbors[i] = finder.find_neighbors(m1, i, 1);
		auto n = finder.find_neighbors(m2, i, m2_dist);
		m2_neighbors[i] = n; 
	}


	int p1 = solve_map(m1, m1_neighbors, char2enum, enum2char, 4);
	int p2 = solve_map(m2, m2_neighbors, char2enum, enum2char, 5);


	std::cout << "Part 1:  " << p1 << std::endl << "Part 2:  " << p2  << std::endl;

	return 0;
	
}


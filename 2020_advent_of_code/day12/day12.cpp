#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<regex>
#include<cmath>

void handle_forward(int &x, int &y, const int& heading, const int& steps)
{
	if (heading == 0) x += steps;
	else if (heading == 90) y += steps;
	else if (heading == 180) x -= steps;
	else y -= steps;
}

void update_pos(int &x, int &y, int &heading, const char& action, const int& action_arg)
{
	switch (action)
	{
		case 'N':
			y += action_arg;
			break;
		case 'S':
			y -= action_arg;
			break;
		case 'E':
			x += action_arg;
			break;
		case 'W':
			x -= action_arg;
			break;
		case 'L':
			heading = (heading + action_arg) % 360;
			break;
		case 'R':
			heading = (heading - action_arg ) % 360;
			if (heading < 0) heading += 360;
			break;
		case 'F':
			handle_forward(x, y, heading, action_arg);
			break;
	}
}

void handle_rotate(int &x, int &y, const int& heading, const int& steps)
{
	if (heading == 0) x += steps;
	else if (heading == 90) y += steps;
	else if (heading == 180) x -= steps;
	else y -= steps;
}

void handle_rotate_p2(const int& x, const int& y, int &way_x, int &way_y, int turn)
{
	
	int diff_x = way_x - x;
	int diff_y = way_y - y;
	if (turn == 90) 
	{
		way_x = x - diff_y;
		way_y = y + diff_x;
	}
	else if (turn == 180)
	{
		way_x = x - diff_x;
		way_y = y - diff_y;
	}
	else if (turn == 270)
	{
		way_x = x + diff_y;
		way_y = y - diff_x;
	}
}

void update_pos_p2(int &x, int &y, int &way_x, int &way_y, const char& action, const int& action_arg)
{
	switch (action)
	{
		case 'N':
			way_y += action_arg;
			break;
		case 'S':
			way_y -= action_arg;
			break;
		case 'E':
			way_x += action_arg;
			break;
		case 'W':
			way_x -= action_arg;
			break;
		case 'L':	
			handle_rotate_p2(x, y, way_x, way_y, action_arg);
			break;
		case 'R':
			handle_rotate_p2(x, y, way_x, way_y, 360 - action_arg);
			break;
		case 'F':
			int diff_x = way_x - x;
			int diff_y = way_y - y;
			x += action_arg * diff_x;
			y += action_arg * diff_y;
			way_x = x + diff_x;
			way_y = y + diff_y;
			break;
	}
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::regex r("([NSEWLRF])([\\d]+)");
	std::smatch match;

	int x = 0;
	int y = 0;
	int heading = 0;

	int x2 = 0;
	int y2 = 0;
	int way_x = 10;
	int way_y = 1;

	while (std::getline(f, line)) 
	{
		if (line.size() > 0)
		{
			std::regex_match(line, match, r);
			char action = match.str(1).at(0);
			int argument = std::stoi(match.str(2));
			update_pos(x, y, heading, action, argument);
			update_pos_p2(x2, y2, way_x, way_y, action, argument);
		}
	}

	f.close();
	int p1 = std::abs(x) + std::abs(y);
	int p2 = std::abs(x2) + std::abs(y2);
;

	std::cout << "Part 1:  " << p1 << std::endl << "Part 2:  " << p2 << std::endl;

	return 0;
	
}


#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>


int find_id(const std::string& encoding)
{
	int lower_mask = 7; // 0000000111 in binary
	int upper_mask = 1023; // 1111111000 in binary
	int bit_shift = 3; // need to shift to the right
	int value = std::stoi(encoding, nullptr, 2);

	int row = (value & upper_mask) >> 3; 
	int col = (value & lower_mask);

	return row * 8 + col; 
}

std::string to_binary(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'B' || str[i] == 'R')
		{
			str[i] = '1';
		}
		else 
		{
			str[i] = '0';
		}

	}
	return str;
}



int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> lines;

	while (std::getline(f, line)) 
	{
		if (line.length() > 0) lines.push_back(to_binary(line));
	}

	f.close();

	int max = -1;

	std::vector<int> ids(lines.size(), 0);

	for (int i = 0; i < lines.size(); i++)
	{
		ids[i] = find_id(lines[i]);
		if (ids[i] > max) max = ids[i];
	}

	std::sort(ids.begin(), ids.end());

	int seat_id = 0;
	for (int i = 0; i < ids.size() - 1; i++)
	{
		if (std::abs(ids[i] - ids[i+1]) == 2) seat_id = (ids[i] + ids[i+1]) / 2;
	}

	std::cout << "Part 1:  " << max << std::endl;
	std::cout << "Part 2:  " << seat_id << std::endl;

	return 0;
	
}


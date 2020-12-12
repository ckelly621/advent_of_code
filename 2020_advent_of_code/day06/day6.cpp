#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> lines;

	int p1_total = 0;
	int p2_total = 0;

	while (std::getline(f, line)) 
	{
		lines.push_back(line);
	}

	f.close();
	
	std::unordered_map<char, int> answers;
	int group_size = 0;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i].length() > 0)
		{
			group_size++;
			for (int j = 0; j < lines[i].length(); j++)
			{
				answers[lines[i][j]] += 1;
			}
		}
		else 
		{
			// process the group
			p1_total += answers.size();
			for (auto& it: answers)
			{
				if (it.second == group_size) p2_total++;
			}

			// reset for processing next group
			answers.clear();
			group_size = 0;
		}

	}

	std::cout << "Part 1:  " << p1_total << std::endl << "Part 2:  " << p2_total << std::endl;

	return 0;
	
}


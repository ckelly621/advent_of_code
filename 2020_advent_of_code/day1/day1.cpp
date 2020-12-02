#include<fstream>
#include<vector>
#include<iostream>
#include<string>

int main(int argc, char** argv)
{
	std::ifstream my_file(argv[1]);
	std::vector<int> values;

	int value;
	while (my_file >> value)
	{
		values.push_back(value);
	}
	
	my_file.close();


	for (int i = 0; i < values.size() - 1; i++)
	{
		for (int j = i + 1; j < values.size(); j++)
		{
			if (values.at(i) + values.at(j) == 2020)
			{
				int result = values.at(i) * values.at(j);
				std::cout << "part 2:  " << result << std::endl;
				break;
			}
		}
	}

	for (int i = 0; i < values.size() - 2; i++)
	{
		for (int j = i + 1; j < values.size() - 1; j++)
		{
			for (int k = j + 1; k < values.size(); k++)
			{
				if (values.at(i) + values.at(j) + values.at(k) == 2020)
				{
					int result = values.at(i) * values.at(j) * values.at(k);
					std::cout << "part 2:  " << result << std::endl;
					break;
				}
			}
		}
	}

	return 0;
}


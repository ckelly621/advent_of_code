#include<fstream>
#include<iostream>
#include<string>
#include<regex>

int main(int argc, char** argv)
{
	std::ifstream my_file(argv[1]);

	std::string value;
	std::regex r("([\\d]+)-([\\d]+) ([a-z]{1,1}): ([a-z]+)");
	std::smatch match;

	int count = 0;
	int part2 = 0;

	while ( std::getline(my_file, value, '\n'))
	{
		std::regex_match(value, match, r);

		if (match.size() > 0)
		{
			int min, max;
			char letter;
			std::string password;

			min = std::stoi(match.str(1));
			max = std::stoi(match.str(2));
			letter = match.str(3).c_str()[0];
			password = match.str(4);

			int occurrences = 0;
			for (int i = 0; i < password.length(); i++)
			{
				if (password.at(i) == letter)
				{
					occurrences++;
				}
			}

			if (occurrences >= min && occurrences <= max)
			{
				count++;
			}

			// convert to 0-index indices for part two
			min--;
			max--;

			if (password.at(min) != password.at(max) && (password.at(min) == letter || password.at(max) == letter))
			{
				part2++;
			}
		}
	}

	my_file.close();

	std::cout << "good passwords:  " << count << std::endl;
	std::cout << "good passwords:  " << part2 << std::endl;

	return 0;
}


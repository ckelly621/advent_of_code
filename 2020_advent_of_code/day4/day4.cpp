#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<regex>

bool is_valid(const std::string& entry, const std::vector<std::regex>& regexes)
{
	std::smatch match;

	for (int i = 0; i < regexes.size(); i++)
	{
		std::regex_match(entry, match, regexes[i]);
		if (match.size() == 0) return false;
	}

	return true;
}




int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> lines;

	/*
         *
         * Regexes for applying rules
         *
         * 0 - byr must be in string
         * 1 - iyr must be in string
         * 2 - eyr must be in string
         * 3 - hgt must be in string
	 * 4 - hcl must be in string
         * 5 - ecl must be in string
         * 6 - pid must be in string
         *
         * Note:  cid is optional and not used for any validation
         *
         */
        std::vector<std::regex> p1{
                std::regex(".*\\sbyr:.*"),
                std::regex(".*\\siyr:.*"),
                std::regex(".*\\seyr:.*"),
                std::regex(".*\\shgt:.*"),
                std::regex(".*\\shcl:.*"),
                std::regex(".*\\secl:.*"),
                std::regex(".*\\spid:.*")
        };


	/*
	 *
	 * Regexes for applying rules
	 *
	 * 0 - byr must be in range [1920, 2002]
	 * 1 - iyr must be in range [2010, 2020]
	 * 2 - eyr must be in range [2020, 2030]
	 * 3 - hgt must contain a unit in set U {'in', 'cm'} and be in range [59, 76] for 'in' or [150, 193] for 'cm'
	 * 4 - hcl must be a 6-digit hexidecimal code (lowercase) with a preceding '#'
	 * 5 - ecl must be exactly one from the set C {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}
	 * 6 - pid must be a 9-digit number that includes any leading zeros
	 *
	 * Note:  cid is optional and not used for any validation
	 *
	 */
	std::vector<std::regex> p2{
		std::regex(".*\\sbyr:(19[2-9][\\d]|200[0-2])\\s.*"),
		std::regex(".*\\siyr:(201[\\d]|2020)\\s.*"),
		std::regex(".*\\seyr:(202[\\d]|2030)\\s.*"),
		std::regex(".*\\shgt:(?:(?:59|6[\\d]|7[0-6])in|1(?:[5-8][\\d]|9[0-3])cm)\\s.*"),
		std::regex(".*\\shcl:#[\\da-f]{6,6}\\s.*"),
		std::regex(".*\\secl:(?:(amb|blu|brn|gry|grn|hzl|oth))\\s.*"),
		std::regex(".*\\spid:[\\d]{9}?\\s.*")
	};

	int good_passports_p1 = 0;
	int good_passports_p2 = 0;

	while (std::getline(f, line, '\n')) 
	{
		lines.push_back(line);
	}

	f.close();
	std::stringstream s;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i].length() > 0)
		{
			s << ' ' << lines[i] << ' ';
		}

		else 
		{
			if (is_valid(s.str(), p1)) 
			{
				good_passports_p1++;
			}

			if (is_valid(s.str(), p2))
			{
				good_passports_p2++;
			}
			s.str("");
		}

	}

	std::cout << "Part 1:  " << good_passports_p1 << std::endl << "Part 2:  " << good_passports_p2 << std::endl;

	return 0;
	
}


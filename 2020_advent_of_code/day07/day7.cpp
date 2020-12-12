#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<regex>

struct bag
{
	std::string name;
	std::unordered_map<std::string, int> contents;
};

struct bag parse_line(const std::regex& bagr, const std::regex& contents, std::string line)
{
	std::string name;
	std::smatch name_match;
	std::regex_match(line, name_match, bagr);
	name = name_match.str(1);

	std::smatch contents_match;
	std::unordered_map<std::string, int> m_contents;

        while(std::regex_search(line, contents_match, contents))
	{
		int count = std::stoi(contents_match.str(2));
		auto str = contents_match.str(3);
		m_contents[str] = count;

		line = contents_match.suffix();
        }

	return {name, m_contents};
}

void find_bags_by_content(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& bags, 
		std::unordered_set<std::string> &contains,
		std::unordered_set<std::string> &seen,
		const std::string& key, 
		const std::string& content)
{
	auto check_seen = seen.find(key);
        if (check_seen == seen.end()) 
	{
		seen.insert(key);
	}
	else
	{
		return;
	}
	if (key == content) return;
	auto children = bags.at(key);
	auto find_iter = children.find(content);
	if (find_iter != children.end()) {
		contains.insert(key);
		return;
	}

	for (auto& f : children)
	{
		find_bags_by_content(bags, contains, seen, f.first, content); 
		auto check_contains = contains.find(f.first);
		if (check_contains != contains.end()) contains.insert(key);
	}
}

int count_bags_inside(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& bags,
		const std::string& key)
{
	auto children = bags.at(key);
	int contents = 0;
	for (auto& child : children)
	{
		contents += child.second * (count_bags_inside(bags, child.first) + 1);
	}

	return contents;
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> lines;
	std::regex bagr("([a-z ]+) bags contain.*");
	std::regex contents("(([\\d]) ([a-z ]+)) bag[s]{0,1}[,\\.]");
	std::unordered_map<std::string, std::unordered_map<std::string, int>> bags;
	std::vector<std::string> bags_v;

	std::unordered_set<std::string> contains_bag;
	std::unordered_set<std::string> seen;

	int p1_total = 0;
	int p2_total = 0;

	while (std::getline(f, line)) 
	{
		if (line.length() > 0) lines.push_back(line);
	}

	f.close();
	

	for (int i = 0; i < lines.size(); i++)
	{
		struct bag b = parse_line(bagr, contents, lines[i]);
		bags[b.name] = b.contents;
		bags_v.push_back(b.name);
	}

	for (auto& iter : bags_v)
	{
		find_bags_by_content(bags, contains_bag, seen, iter, "shiny gold");
	}

	p1_total = contains_bag.size();
	p2_total = count_bags_inside(bags, "shiny gold");
	std::cout << "Part 1:  " << p1_total << std::endl << "Part 2:  " << p2_total << std::endl;

	return 0;
	
}


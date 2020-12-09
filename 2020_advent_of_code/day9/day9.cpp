#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
#include<string>
#include<limits>

void init_valid_numbers(std::unordered_set<long> &valid_numbers, 
		const std::vector<long>& sequence,
		int start,
		int end)
{
	for (int i = start; i <= end; i++)
	{
		valid_numbers.insert(sequence[i]);
	}
}

bool is_sum(const std::unordered_set<long>& valid_numbers, const long& value)
{
	for (auto it = valid_numbers.begin(); it != valid_numbers.end(); ++it)
	{
		if (value != 2 * *it)
		{
			auto pair_check = valid_numbers.find(value - *it);
			if (pair_check != valid_numbers.end()) return true;
		}
	}

	return false;
}

std::vector<long> find_range_for_value(const std::vector<long> sequence, const long& value)
{
	std::vector<long> contiguous_range;
	long sum = 0;
	int curr = 0;
	while (curr < sequence.size() && sum != value)
	{
		long curr_value = sequence[curr];
		sum += curr_value;
		contiguous_range.push_back(curr_value);
		while (sum > value) 
		{
			sum -= contiguous_range[0];
			contiguous_range.erase(contiguous_range.begin());
		}
		curr++;
	}

	return contiguous_range;

}

long find_weakness(const std::vector<long>& range)
{
	long max = std::numeric_limits<long>::min();
	long min = std::numeric_limits<long>::max();

	for (int i = 0; i < range.size(); i++)
	{
		long value = range[i];
		if (value > max) max = value;
		if (value < min) min = value;
	}
	return min + max;
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	int preamble_length = std::stoi(argv[2]);
	std::string line;
	std::vector<long> sequence;
	std::unordered_set<long> valid_numbers;

	while (std::getline(f, line)) 
	{
		if (line.size() > 0) sequence.push_back(std::stol(line));
	}

	f.close();

	int window_start = 0;
	int window_end = preamble_length - 1;
	init_valid_numbers(valid_numbers, sequence, window_start, window_end);
	int curr = preamble_length;

	while(curr < sequence.size() && is_sum(valid_numbers, sequence[curr])) 
	{
		auto value_at_curr = sequence[curr];
		valid_numbers.insert(value_at_curr);
		window_end++;

		auto value_at_window_start = sequence[window_start];
		valid_numbers.erase(value_at_window_start);
		window_start++;

		curr++;
	}

	long p1_number = sequence[curr];

	auto range = find_range_for_value(sequence, p1_number);
	long p2_sum = find_weakness(range);
	
	std::cout << "Part 1:  " << p1_number << std::endl << "Part 2:  " << p2_sum << std::endl;

	return 0;
	
}


#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>
#include<algorithm>
#include<chrono>

bool less_than(int a, int b) { return a < b; }

class ArrangementsOnes
{
private:
	std::vector<long> combos = {1, 1, 2};

	void fill_combos(const int& index)
	{
		for (int i = combos.size() - 1; i < index; i++)
		{
			combos.push_back(combos[i-2] + combos[i-1] + combos[i]);
		}
	}
public:
	long get_combos(const int& ones)
	{
		if (ones >= combos.size()) fill_combos(ones);
		return combos[ones];
	}	
};

void handle_contiguous_ones(long &p2, int &ones, ArrangementsOnes &arr)
{
	if (ones > 0) p2 *= arr.get_combos(ones);
	ones = 0;
}

int main(int argc, char** argv)
{
	auto begin = std::chrono::high_resolution_clock::now();
	std::ifstream f(argv[1]);
	std::vector<int> adapters;
	std::string line;

	while (std::getline(f, line)) 
	{
		if (line.size() > 0) adapters.push_back(std::stoi(line));
	}

	f.close();
	long p2 = 1;

	int jolt_1 = 0;
	int jolt_3 = 0;
	int effective_jolt = 0;
	int contiguous_ones = 0;
	std::sort(adapters.begin(), adapters.end(), less_than);
	ArrangementsOnes a;

	for ( int i = 0; i < adapters.size(); i++ )
	{
		auto adapter = adapters[i];
		int delta_jolt = adapter - effective_jolt;
		effective_jolt = adapter;
		if (delta_jolt == 1)
		{
			jolt_1++;
			contiguous_ones++;
		}
		else if (delta_jolt == 3)
		{
			jolt_3++;
			handle_contiguous_ones(p2, contiguous_ones, a);
		}
		if (i + 1 == adapters.size())
		{
			jolt_3++;
			handle_contiguous_ones(p2, contiguous_ones, a);
		}
	}

	int p1 = jolt_1 * jolt_3;	
	auto end = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::cout << "Part 1:  " << p1 << std::endl << "Part 2:  " << p2 << std::endl;
	std::cout << "elapsed time:  " << microseconds.count() << " microseconds" << std::endl;

	return 0;
	
}


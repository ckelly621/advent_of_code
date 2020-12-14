#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>
#include<unordered_map>

long gcd(long a, long b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

long lcm(long a, long b)
{
	return (b * a) / gcd(b, a);
}

long find_earliest(const std::vector<int>& buses)
{
	long t_stamp = 0;
	long dt = buses[0];
	for (int i = 1; i < buses.size(); i++)
	{
		if (buses[i] != -1 )
		{
			int bus = buses[i];
		        do
		        {
				t_stamp += dt;
			} while ((t_stamp + i) % bus != 0);
			dt = lcm(dt, buses[i]);
		}
	}
	return t_stamp;

}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	int timestamp = std::stoi(argv[2]);
	int min_wait = std::numeric_limits<int>::max();
	std::string line;
	std::vector<int> buses;
	int bus_id = -1;

	while (std::getline(f, line, ',')) 
	{
		if (line.size() > 0) 
		{
			int bus = -1;
			if (line != "x") {
				bus = std::stoi(line);
				int wait_time = bus - (timestamp % bus);
				if (wait_time < min_wait)
				{
					min_wait = wait_time;
					bus_id = bus;
				}
			}
			buses.push_back(bus);
			
		}
	}
	f.close();

	int p1 = min_wait * bus_id;
	long p2 = find_earliest(buses);


	std::cout << "Part 1:  " << p1 << std::endl << "Part 2:  " << p2  << std::endl;

	return 0;
	
}


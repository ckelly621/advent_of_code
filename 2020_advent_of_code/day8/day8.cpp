#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<regex>

enum Operation { nop, jmp, acc };

struct Command {
	Operation op;
	int arg;
};

struct Command to_command(const std::string& str, 
		const std::unordered_map<std::string, Operation>& str2op, 
		std::regex r)
{
	std::smatch match;
	std::regex_match(str, match, r);
	return { str2op.at(match.str(1)), std::stoi(match.str(2)) };
}

void process_command(Command cmd, int &pc_counter, int &accumulator)
{
	switch (cmd.op)
	{
		case Operation::nop :
			pc_counter++; 
			break;
		case Operation::jmp :
		        pc_counter += cmd.arg;
			break;
		case Operation::acc :
		        pc_counter++;
		        accumulator += cmd.arg;
		        break;	
	}	
}

void run_program(const std::vector<Command>& program, int &pc_counter, int &accumulator, bool &cycled)
{
	std::unordered_set<int> previously_run;
	while ((pc_counter >= 0 && pc_counter < program.size()) && !cycled)
	{
		auto check_if_run = previously_run.find(pc_counter);
		if (check_if_run == previously_run.end())
		{
			previously_run.insert(pc_counter);
			process_command(program[pc_counter], pc_counter, accumulator);
		}
		else 
		{
			cycled = true;
		}
	}
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<Command> program;
	std::unordered_map<std::string, Operation> str2op;
	std::unordered_set<int> cycle_set;
	str2op["nop"] = Operation::nop;
	str2op["jmp"] = Operation::jmp;
	str2op["acc"] = Operation::acc;

	std::unordered_set<int> run_commands;

	std::regex r("([a-z]{3}) ([\\-\\+]?[\\d]+)");

	while (std::getline(f, line)) 
	{
		if (line.size() > 0) program.push_back(to_command(line, str2op, r));
	}

	f.close();

	{
		int pc_counter = 0;
		int accumulator = 0;
		bool cycled = false;
		run_program(program, pc_counter, accumulator, cycled);
		std::cout << "Part 1:  " << accumulator << std::endl;
	}

	int iter = 0;
	bool change_terminates = false;
	int pc_counter, accumulator;
	while (iter  < program.size() && !change_terminates)
	{
		pc_counter = 0;
		accumulator = 0;
		bool cycled = false;
		auto cmd = program[iter];
		if (cmd.op != Operation::acc)
		{
			auto orig = cmd.op;
			if (cmd.op == Operation::nop) {
				program[iter].op = Operation::jmp;
			}
			else
			{
				program[iter].op = Operation::nop;
			}
			run_program(program, pc_counter, accumulator, cycled);
			program[iter].op = orig;
			if (!cycled) change_terminates = true;
		}
		iter++;
	}
	std::cout << "Part 2:  " << accumulator << std::endl;
	return 0;
	
}


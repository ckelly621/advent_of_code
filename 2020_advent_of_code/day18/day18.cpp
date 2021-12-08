#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<stack>
#include<unordered_map>

long eval(const long& a, const long& b, const char& op)
{
	if (op == '+') return a + b;
	if (op == '*') return a * b;
}

long eval_postfix(const std::string& eq)
{
	std::stack<long> operands;
	for (int i = 0; i < eq.size(); i++)
	{
		auto c = eq[i];
		if (c == '+' || c == '*')
		{
			auto b = operands.top();
			operands.pop();
			auto a = operands.top();
			operands.pop();
			auto ev = eval(a, b, c);
			operands.push(ev);
		}
		else 
		{
			long v = static_cast<int>(c) - 48;
			operands.push(v);
		}
	}
	return operands.top();
}

std::string infix_to_postfix(const std::string& eq, const std::unordered_map<char, int> precedence)
{
	std::stringstream out;
	std::stack<char> operators;
	for (int i = 0; i < eq.size(); i++)
	{
		auto c = eq[i];
		if (c != ' ')
		{
			if (c >= 48 && c <= 57)
			{
				out << c;
			}
			else if (c == '+' || c == '*')
			{
				auto p = precedence.at(c);
				if (operators.empty() || operators.top() == '(' || p > precedence.at(operators.top()))
				{
					operators.push(c);
				}
				else 
				{
					while(!operators.empty() && operators.top() != '(' && p <= precedence.at(operators.top()))
					{
						out << operators.top();
						operators.pop();
					}
					operators.push(c);
				}
			}
			else if (c == '(') operators.push(c);
			else // ')'
			{
				while (operators.top() != '(')
				{
					out << operators.top();
					operators.pop();
				}
				operators.pop();
			}
		}
	}
	while (!operators.empty())
	{
		out << operators.top();
		operators.pop();
	}
	return out.str();
}

int main(int argc, char** argv)
{
	std::ifstream f(argv[1]);
	std::string line;
	std::vector<std::string> equation_strings;
	std::vector<int> evals;
	std::unordered_map<char, int> p1_precendence = {{'+', 0}, {'*', 0}};
	std::unordered_map<char, int> p2_precendence = {{'+', 1}, {'*', 0}};


	while (std::getline(f, line)) 
	{
		if (line.length() > 0) {
			equation_strings.push_back(line);
		}
	}
	f.close();

	long p1 = 0;
	long p2 = 0;
	for (int i = 0; i < equation_strings.size(); i++)
	{
		long ans_1 = eval_postfix(infix_to_postfix(equation_strings[i], p1_precendence));
		long ans_2 = eval_postfix(infix_to_postfix(equation_strings[i], p2_precendence));
		p1 += ans_1;
		p2 += ans_2;
	}



	std::cout << "Part 1:  " << p1 << std::endl;
	std::cout << "Part 2:  " << p2 << std::endl;

	return 0;
	
}


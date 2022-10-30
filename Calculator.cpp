#include "Calculator.hpp"

std::vector < Variable > variables;

double get_value(const std::string& n)
{
	for (const Variable& variable : variables)
	{
		if (variable.name == n)
		{
			return variable.value;
		}
	}
	return 0.0;
}

void set_value(const std::string& n, double v)
{
	for (Variable& variable : variables)
	{
		if (variable.name == n)
		{
			variable.value = v;
			return;
		}
	}
}



bool is_declared(const std::string& n)
{
	for (const Variable& variable : variables)
	{
		if (variable.name == n)
		{
			return true;
		}
	}
	return false;
}

double define_name(const std::string& n, double v)
{
	if (is_declared(n))
	{
		// error
	}
	variables.push_back(Variable(n, v));
	return v;
}

#include <cmath>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <string>
#include <ios>

struct Token // есть изменения
{
	Token(char c) :
		kind(c)
	{}

	Token(char c, double v) :
		kind(c), value(v)
	{}

	Token(char c, std::string n) : // для переменных
		kind(c), name(n)
	{}

	char kind;
	double value;
	std::string name; // для переменных
};

struct Token_Stream // все ок
{
	Token_Stream() :
		m_full(false), m_buffer(0)
	{}

	Token get(Token_Stream& token_stream);

	void putback(const Token& token);

	bool m_full;

	Token m_buffer;
};

struct Variable // новое
{
	Variable(std::string n, double v) :
		name(n), value(v)
	{}

	std::string name;
	double value;
};

void calculate(Token_Stream& token_stream, char quit, char print);
double expression(Token_Stream& token_stream);
double term(Token_Stream& token_stream);
double statement(Token_Stream& token_stream);
double primary(Token_Stream& token_stream);

// новое
double get_value(const std::string& n);
void set_value(const std::string& n, double v, std::vector < Variable > variables);
bool is_declared(const std::string& n);
double define_name(const std::string& n, double v);
double declaration(Token_Stream& token_stream);

int main()
{
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	Token_Stream token_stream;

	const char quit = 'q';
	const char print = ';';

	calculate(token_stream, quit, print);

	system("pause");

	return 0;
}

void calculate(Token_Stream& token_stream, char quit, char print)
{
	const std::string prompt = "> ";
	const std::string result = "= ";

	while (std::cin)
	{
		std::cout << prompt;

		Token token = token_stream.get(token_stream);

		while (token.kind == print)
		{
			token = token_stream.get(token_stream);
		}
		if (token.kind == quit)
		{
			return;
		}

		token_stream.putback(token);

		std::cout << "\n" << result << statement(token_stream) << '\n'; // expression
	}
}

void Token_Stream::putback(const Token& token)
{
	m_buffer = token;
	m_full = true;
}

const char number = '8';

const char set = 'S'; // новое
const char name = 'a'; // новое 
const std::string declkey = "let"; // новое

Token Token_Stream::get(Token_Stream& token_stream)
{
	if (m_full)
	{
		m_full = false;
		return m_buffer;
	}
	char c;
	std::cin >> c;
	switch (c)
	{
	case 'q': case ';': case '(': case ')': case '{':
	case '}': case '+': case '-': case '*': case '/':
	case '%': case '=': case '!': case 's': case 'p':
		return Token(c);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(c);
		double value;
		std::cin >> value;
		return Token(number, value);
	}
	default: // новое
		if (isalpha(c))
		{
			std::string s;
			s += c;
			while (std::cin.get(c) && (isalpha(c) || isdigit(c)))
			{
				s += c;
			}
			std::cin.putback(c);
			if (s == declkey)
			{
				return Token(set);
			}
			return Token(name, s);
		}
	}
	return Token(c);
}

double primary(Token_Stream& token_stream)
{
	Token t = token_stream.get(token_stream);
	switch (t.kind)
	{
	case name: // новое
		return get_value(t.name);
		break;
	case '(':
	{
		double d = expression(token_stream);
		t = token_stream.get(token_stream);
		return d;
		break;
	}
	case '{':
	{
		double d = expression(token_stream);
		t = token_stream.get(token_stream);
		return d;
	}
	case number:
		return t.value;
	case '-':
		return -primary(token_stream);
	case '+':
		return primary(token_stream);
	}
	return 0.0;
}

double expression(Token_Stream& token_stream)
{
	double left = term(token_stream);
	Token t = token_stream.get(token_stream);
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term(token_stream);
			t = token_stream.get(token_stream);
			break;
		case '-':
			left -= term(token_stream);
			t = token_stream.get(token_stream);
			break;
		default:
			token_stream.putback(t);
			return left;
			break;
		}
	}
}

double statement(Token_Stream& token_stream) // новое
{
	Token token = token_stream.get(token_stream);
	switch (token.kind)
	{
	case set:
		return declaration(token_stream);
	default:
		token_stream.putback(token);
		return expression(token_stream);
	}
}

double term(Token_Stream& token_stream)
{
	double left = primary(token_stream);
	Token t = token_stream.get(token_stream);
	while (true)
	{
		switch (t.kind)
		{
		case 'p':
		{
			double power = primary(token_stream);
			left = pow(left, power);
			t = token_stream.get(token_stream);
			break;
		}
		case '!':
		{
			for (int i = left - 1; i > 1; i--)
			{
				left *= i;
			}
			t = token_stream.get(token_stream);
			break;
		}
		case 's':
		{
			left = sqrt(left);
			t = token_stream.get(token_stream);
			break;
		}
		case '*':
			left *= primary(token_stream);
			t = token_stream.get(token_stream);
			break;
		case '/':
		{
			double d = primary(token_stream);
			left /= d;
			t = token_stream.get(token_stream);
			break;
		}
		case '%':
		{
			double d = primary(token_stream);
			left = fmod(left, d);
			t = token_stream.get(token_stream);
			break;
		}
		default:
			token_stream.putback(t);
			return left;
			break;
		}
	}
}

// новое

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

double declaration(Token_Stream& token_stream)
{
	Token token = token_stream.get(token_stream);
	std::string name = token.name;
	Token assume = token_stream.get(token_stream);
	double value = expression(token_stream);
	define_name(name, value);

	return value;
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

#include "Calculator.hpp"


int main()
{
	//std::ifstream fin("test.txt", std::ios::in);
	//std::ofstream fout("result.txt", std::ios::out);

	//Token_Stream < std::ifstream > token_stream{ fin };
	Token_Stream < std::istream > token_stream{ std::cin };

	const char quit = 'q';
	const char print = ';';

	//calculate(token_stream, quit, print, fout);
	calculate(token_stream, quit, print, std::cout);

	return 0;

}
#include "Calculator.hpp"
#include <sstream> 

std::string read_file(const std::string& file_name) 
{
    std::ifstream f(file_name.c_str());
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

bool test(int test_num)
{
	const char quit = 'q';
	const char print = ';';

	std::string test_filename    = "test_files/test";
	std::string res_filename     = "test_files/result";
	std::string ref_res_filename = "test_files/ref_result";	

 	test_filename    += std::to_string(test_num);
 	res_filename     += std::to_string(test_num);
 	ref_res_filename += std::to_string(test_num);

	test_filename    += ".txt";
 	res_filename     += ".txt";
 	ref_res_filename += ".txt";

	std::ifstream fin(test_filename.c_str(), std::ios::in);
	std::ofstream fout( res_filename.c_str(), std::ios::out);
	
	//std::cout << read_file(test_filename) << "\n";
	Token_Stream < std::ifstream > token_stream{ fin };

	calculate(token_stream, quit, print, fout);
	
	fout.close();
	fin.close();
        
	std::string res = read_file(res_filename);
        std::string ref_res = read_file(ref_res_filename);
	//std::cout <<"res " << res << "\n";
	//std::cout << "ref res " << ref_res << "\n";
        if (res == ref_res)
	{
		std::cout << "Test " << test_num << " passed\n";
		return true;
	}
	else
	{
		std::cout << "Test " << test_num << " failed\n";
		return false;
	}

}

int main()
{
	int num_of_passed = 0;
	int total_num = 12;
        for (int i = 0; i < total_num; i++)
	{
		bool flag = test(i);
		if(flag)
		{
			num_of_passed++;
		}
	}

	std::cout << "Total " << num_of_passed << " tests passed out of " << total_num  << "\n";
	
	return 0;
}

#include <iostream>
#include <fstream>

#include "utility.h"

int main()
{
	std::string file{Utility::roomPath};
	file += Utility::fileName ;
	std::ofstream fout(file,std::ios::out);
	if (!fout.is_open())
	{
	       	return 1;
	}
	for (size_t i = 0 ; i < Utility::maxFileSize ; ++i)
	{
		fout <<  std::rand()  << " ";
	}
	return 0;
}

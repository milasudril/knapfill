//@	{"targets":[{"name":"knapfill","type":"application"}]}

#include "dataset.hpp"
#include "problem.hpp"
#include <cstdio>
#include <string>

int main(int argc, char* argv[])
	{
	try
		{
		if(argc<3)
			{
			printf("Usage: knapfill {file with valid values} {desired sum} ...\n");
			return 0;
			}

		KnapFill::Problem problem;
		problem.values(KnapFill::DataSet(argv[1])); //Load problem data

		argv-=2; // Skip program name and dataset file

		while(argv!=0)
			{
			auto capacity = atoi(arg[0]);
			auto solution=problem.capacity(capacity).solution();
			printf("Solution for %d\n    Value Count", capacity);
			std::for_each(solution.begin(), solution.end(),[](auto item)
				{
				printf("    %d %d\n",item.value, item.count);
				});
			putchar('\n')
			--argv;
			}
		}
	catch(const std::string& message)
		{
		fprintf(stderr,"Error: %s\n", message.c_str());
		return -1;
		}
	return 0;
	}

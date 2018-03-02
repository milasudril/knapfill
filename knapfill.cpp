//@	{"targets":[{"name":"knapfill","type":"application"}]}

#include "dataset.hpp"
#include "problem.hpp"
#include <cstdio>
#include <string>
#include <algorithm>

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

		argc-=2; // Skip program name and dataset file
		argv+=2;

		while(argc!=0)
			{
			auto capacity = atoi(argv[0]);
			auto solution=problem.capacity(capacity).solution();
			printf("Solution for %d\n    Value Count\n", capacity);
			std::for_each(solution, solution + problem.size().n_values, [](auto item)
				{printf("    %d %d\n",item.value, item.count);});
			putchar('\n');
			--argc;
			++argv;
			}
		}
	catch(const std::string& message)
		{
		fprintf(stderr,"Error: %s\n", message.c_str());
		return -1;
		}
	return 0;
	}

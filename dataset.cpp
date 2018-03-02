//@	{"targets":[{"name":"dataset.o","type":"object"}]}

#include "dataset.hpp"

#include <cstdio>
#include <memory>

using namespace KnapFill;

#include <string>

#ifdef _GNU_SOURCE
#warning Overiding strerror_r with POSIX complient version
extern "C" int __xpg_strerror_r(int errcode,char* buffer,size_t length);
#define strerror_r __xpg_strerror_r
#else
#include <cstring>
#endif

namespace
	{
	struct FileDeleter
		{
		void operator()(FILE* fptr) noexcept
			{
			if(fptr)
				{fclose(fptr);}
			}
		};

	void loadData(FILE* stream, std::vector<int>& data)
		{
		try
			{
			std::string buffer;
			while(true)
				{
				auto ch_in=getc(stream);
				if(ch_in==EOF)
					{
					if(buffer.size()!=0)
						{data.push_back(std::stoi(buffer));}
					return;
					}

				if(ch_in>=0 && ch_in<=' ')
					{
					if(buffer.size()!=0)
						{
						data.push_back(std::stoi(buffer));
						buffer.clear();
						}
					}
				else
					{buffer += ch_in;}
				}
			}
		catch(const std::exception& err)
			{throw std::string(err.what());}
		}
	}

DataSet::DataSet(const char* filename)
	{
	std::unique_ptr<FILE,FileDeleter> src(fopen(filename,"rb"));
	if(!src)
		{
		char msgbuff[512];
		strerror_r(errno, msgbuff, sizeof(msgbuff));
		throw std::string("Failed to open file ") + filename + ": " + msgbuff;
		}
	loadData(src.get(), *this);
	}

//@	{
//@	"targets":[{"name":"dataset.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"dataset.o","rel":"implementation"}]
//@	}

#ifndef KNAPFILL_DATASET_HPP
#define KNAPFILL_DATASET_HPP

#include <vector>

namespace KnapFill
	{
	class DataSet:private std::vector<int>
		{
		public:
			explicit DataSet(const char* src);
			using std::vector<int>::begin;
			using std::vector<int>::end;
			using std::vector<int>::size;
		};
	};

#endif

//@	{"targets":[{"name":"problem.o","type":"object"}]}

#include "problem.hpp"

using namespace KnapFill;

namespace
	{
	int& getMatrixElement(int* data, int n_cols, int row,int col) noexcept
		{return data[n_cols*row + col];}

	struct Params
		{
		int initial_capacity;
		int* mem;
		const int* values;
		int* count;
		};

	int buildMatrix(int n_vals, int capacity, const Params& params)
		{
		if(n_vals == 0)
			{return 0;}
		if(capacity == 0)
			{return 0;}
		auto& n = getMatrixElement(params.mem, params.initial_capacity, n_vals - 1, capacity - 1);
		if(n != -1)
			{return n;}

		auto max_result = 0;
		auto k_max = 0;
		auto k = 0;
		while(k*params.values[n_vals - 1] <= capacity)
			{
			auto val = k*params.values[n_vals - 1] + buildMatrix(n_vals - 1, capacity - k*params.values[n_vals-1], params);
			if(val > max_result)
				{
				max_result = val;
				k_max = k;
				}
			++k;
			}
		n = max_result;
		getMatrixElement(params.count, params.initial_capacity, n_vals - 1, capacity - 1) = k_max;
		return max_result;
		}
	}

void Problem::update() const
	{
	auto n_vals = m_n_values;
	auto capacity = m_capacity;
	auto size = n_vals*capacity;
	std::unique_ptr<int[]> mem(new int[size]);
	std::unique_ptr<int[]> val_count(new int[size]);
	std::fill(mem.get(), mem.get() + size, -1);
	std::fill(val_count.get(), val_count.get() + size, -1);

	auto vals = m_values.get();
	buildMatrix(n_vals, capacity, Params{capacity, mem.get(), vals, val_count.get()});

	std::unique_ptr<Item[]> solution(new Item[n_vals]);
	auto ptr = solution.get();
	memset(ptr, 0, n_vals*sizeof(Item));
	auto col = capacity - 1;
	vals = vals + n_vals;
	while(n_vals!=0 && col>=0)
		{
		--n_vals;
		--vals;
		auto n = getMatrixElement(val_count.get(), capacity, n_vals, col);
		auto val = *vals;
		*ptr = {val, n};
		++ptr;
		col -= n*val;
		}
	m_solution = std::move(solution);
	}

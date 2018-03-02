//@	{
//@	"targets":[{"name":"problem.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"problem.o","rel":"implementation"}]
//@	}

#ifndef KNAPFILL_PROBLEM_HPP
#define KNAPFILL_PROBLEM_HPP

#include <memory>
#include <cstring>

namespace KnapFill
	{
	class Problem
		{
		public:
			struct Item
				{
				int value;
				int count;
				};

			struct Size
				{
				int n_values;
				int capacity;
				};

			const Item* solution() const
				{
				if(!m_solution)
					{update();}
				return m_solution.get();
				}

			Size size() const noexcept
				{return {m_n_values, m_capacity};}

			template<class Range>
			Problem& values(const Range& vals)
				{
				auto n_vals=std::end(vals) - std::begin(vals);
				std::unique_ptr<int[]> temp(new int[n_vals]);
				memcpy(temp.get(), &*std::begin(vals), n_vals * sizeof(int));
				m_values = std::move(temp);
				m_solution.reset();
				m_n_values = n_vals;
				return *this;
				}

			Problem& capacity(int capacity) noexcept
				{
				m_capacity = capacity;
				m_solution.reset();
				return *this;
				}


		private:
			void update() const;
			int m_n_values;
			int m_capacity;
			mutable std::unique_ptr<const int[]> m_values;
			mutable std::unique_ptr<Item[]> m_solution;
		};
	}

#endif

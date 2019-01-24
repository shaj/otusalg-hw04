
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>

#include "oa_sort.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



int main()
{
	{
		std::vector<int> v {9, 3, 4, 6, 5, 7, 8, 2, 0, 1};

		otusalg::insertion_sort(v);

		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

	{
		std::vector<int> v {9, 3, 4, 6, 5, 7, 8, 2, 0, 1};

		otusalg::shell_sort(v.begin(), v.end(), std::less<int>());

		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}


	return 0;
}

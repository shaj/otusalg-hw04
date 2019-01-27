
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>

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



void read_data(std::istream &is, std::vector<int> &v)
{
	std::string slen;
	std::getline(is, slen);
	v.clear();
	v.reserve(std::stoi(slen));
	for(std::string line; std::getline(is, line);)
	{
		v.emplace_back(std::stoi(line));
	}
}

int main(int argc, char const *argv[])
{

	if(argc > 1)
	{
		std::cout << "'" << argv[1] << "'\n";

		std::vector<int> v;
		std::ifstream fs;
		fs.open(argv[1], std::ios::in);
 
		if(fs.is_open())
		{
			read_data(fs, v);
			fs.close();
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << "data size: " << v.size() << "\n";
			std::cout << "insertion_sort: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::insertion_sort(v);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			std::cout << "shell_sort: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort(v.begin(), v.end(), std::less<int>());
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			std::cout << "shell_sort_c: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_c(v);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			std::cout << "std::sort: " << measure<std::chrono::microseconds>::execution([&]()
			{
				std::sort(v.begin(), v.end(), std::less<int>());
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;



			std::cout << "\nDifferent sequence of steps:\n";
			std::vector<int> d;

			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			for(int i=v.size()/2; i!=0; i /= 2) d.emplace_back(i);
			std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << "\n";

			std::cout << "shell_sort_ck steps d[1]=N/2; d[i]=d[i-1]/2: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_ck(v, d);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			d.clear();
			for(int i=1; ; i++)
			{
				int p = std::pow(2, i) - 1;
				if(p > v.size()) break;
				d.emplace_back(p);
			}
			std::reverse(d.begin(), d.end());
			std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << "\n";

			std::cout << "shell_sort_ck steps 2**i-1: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_ck(v, d);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;

			
			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			d.clear();
			for(int i=0; ; i++)
			{
				int p = std::pow(2, i);
				if((p > v.size())) break;
				d.emplace_back(p);
			}
			std::reverse(d.begin(), d.end());
			std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << "\n";

			std::cout << "shell_sort_ck steps 2**i: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_ck(v, d);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


			fs.open(argv[1]);
			read_data(fs, v);
			fs.close();
			d.clear();
			d.push_back(1750);
			d.push_back(701);
			d.push_back(301);
			d.push_back(132);
			d.push_back(57);
			d.push_back(23);
			d.push_back(10);
			d.push_back(4);
			d.push_back(1);
			std::copy(d.begin(), d.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << "\n";

			std::cout << "shell_sort_ck steps Marcin Ciura: " << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::shell_sort_ck(v, d);
			}) << " us\n";
			if(std::is_sorted(v.begin(), v.end())) std::cout << "vector sorted\n";
			else std::cout << "vector NOT sorted\n";
			std::cout << std::endl;


		}
		else
		{
			std::cout << "File '" << argv[1] << "' does not exist" << std::endl;
		}
	}

	return 0;
}


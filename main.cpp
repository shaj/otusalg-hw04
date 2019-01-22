
#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <limits>
#include <memory>

#include <cstdlib>
#include <cmath>


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


class eratos
{

	std::vector<unsigned int> r;

public:
	void operator()(unsigned int n)
	{
		std::cout << "\n\nEratosfen functor" << std::endl;
		
		// std::bitset<n> v;
		std::cout << "trace 1" << std::endl;
		std::vector<bool> v(n, false);
		std::cout << "trace 2" << std::endl;
		r.empty();
		std::cout << "trace 3" << std::endl;
		if(n > 100) r.reserve(n / 100);
		std::cout << "trace 4" << std::endl;

std::cout << "Find " << measure<std::chrono::microseconds>::execution([&]()
{
		for(unsigned int i=2; i < (n/2); i++)
		{
			unsigned int j = i * 2;
			while(j < n)
			{
				v[j] = true;
				j += i;
			}
		}
}) << " us\n";

		std::cout << "trace 5" << std::endl;

std::cout << "Emplace " << measure<std::chrono::microseconds>::execution([&]()
{
		for(unsigned int i=0; i < n; i++)
		{
			if(v[i] == false)
			{
				r.emplace_back(i);
			}
		}
}) << " us\n";

		std::cout << "trace 6" << std::endl;
	}

	const auto &result() const
	{
		return r;
	}

};



class fibo_sum
{

public:
	void operator()(int n)
	{
		mpz_t a, b, f;
		mpz_init(a);
		mpz_init(b);
		mpz_init(f);
		mpz_set_ui(a, 1);
		mpz_set_ui(b, 1);
		mpz_set_ui(f, 0);

		for(int i=0; i<(n-2); i++)
		{
			mpz_add(f, a, b);
			mpz_set(a, b);
			mpz_set(b, f);
		}
		std::cout << "Fibo for n = " << n << " is ";
		mpz_out_str(stdout, 10, f);
		std::cout << std::endl;
	}
};


class fibo_alg
{

static constexpr auto sqrtfive = std::sqrt(5.0L);
static constexpr auto fi = (1.0L + sqrtfive) / 2.0L;

public:
	void operator()(int n)
	{
		auto fres = std::pow(fi, n) / sqrtfive + 0.5L;
		mpz_t ret;
		mpz_init(ret);
		mpz_set_d(ret, fres);

		std::cout << "Fibo for n = " << n << " is ";
		mpz_out_str(stdout, 10, ret);
		std::cout << std::endl;
	}
};

class fibo_matrix
{

public:
    int operator()(int n)
    {
//        std::array<unsigned long long int, 4> v {1, 1, 1, 0};
        int v = 5;
        int res = 0;

        std::vector<int> buf(static_cast<std::size_t>(n/2+1));

        if(n < 2) throw std::runtime_error("Value error");
        if(n == 2) return v*v;

        int pow = 2;
        buf[0] = v*v;   // Индекс buf + 2 => степень сохраненного числа
        while(1)
        {
            pow *= 2;
            if(pow > n)
            {
                for(int i=pow/2; i<n; i++)
                    res = res * v;
                return res;
            }
            else if(pow == n)
            {
                return res*res;
            }
            else
            {
                res = res * res;
                buf[pow] = res;
            }

        }
    }
};


int main()
{
	unsigned long long int a = 1234567890;
	unsigned long long int b = 12;
	int cnt = 0;


	std::cout << "First: " << measure<>::execution([&]()
		{
			while(a != b)
			{
				if(a > b)
					a = a-b;
				else
					b = b-a;
				cnt++;
			}
		}) << " ms\n";

	std::cout << "Alg 1: " << a << "\n";
	std::cout << cnt << std::endl;

    a = 1234567890;
	b = 12;
	cnt = 0;

	std::cout << "Second: " << measure<>::execution([&]()
		{
			while((a != 0) && (b != 0))
			{
				if(a > b)
					a = a % b;
				else
					b = b % a;
				cnt++;
			}
		}) << " ms\n";

	std::cout << a << "  " << b << "\n";
	std::cout << "Alg 2: " << std::max(a, b) << "\n";
	std::cout << cnt << std::endl;

    {
        // Быстрое возведение в степень

    }


	{
		// Решето Эратосфена
		auto e = std::make_unique<eratos>();

		auto t = measure<std::chrono::microseconds>::execution(*e, 100000);
		std::cout << "\nexecution " << t << " us" << std::endl;
		std::cout << "Found " << e->result().size() << " numbers" << std::endl;
	}

	{
        // Числа Фибоначчи
		fibo_sum f;
		auto t = measure<std::chrono::microseconds>::execution(f, 900);
		std::cout << "\nexecution fibo_summ " << t << " us" << std::endl;
	}

	{
        // Числа Фибоначчи
		fibo_alg f;
		auto t = measure<std::chrono::microseconds>::execution(f, 900);
		std::cout << "\nexecution fibo_alg " << t << " us" << std::endl;
	}

	{
        // Числа Фибоначчи
		fibo_matrix f;
		auto t = measure<std::chrono::microseconds>::execution(f, 900);
		std::cout << "\nexecution fibo_matrix " << t << " us" << std::endl;
	}

	return 0;
}

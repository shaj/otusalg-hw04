
#pragma once

#include <vector>
#include <iterator>


namespace otusalg
{


template <typename T>
int insertion_sort(std::vector<T> &v)
{
	T x;
	int j;
	for(int i=1; i<v.size(); i++)
	{
		x = v[i];
		j = i - 1;
		while((j >= 0) && (v[j] > x))
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = x;
	}
	return 0;
}

template< typename RandomAccessIterator, typename Compare >
void shell_sort( RandomAccessIterator first, RandomAccessIterator last, Compare comp )
{
    for( typename std::iterator_traits< RandomAccessIterator >::difference_type d = ( last - first ) / 2; d != 0; d /= 2 )
        for( RandomAccessIterator i = first + d; i != last; ++i )
            for( RandomAccessIterator j = i; j - first >= d && comp( *j, *( j - d ) ); j -= d )
                std::swap( *j, *( j - d ) );
}


} // namespace otusalg
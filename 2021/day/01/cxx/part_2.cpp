#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <limits>
#include <vector>
#include <list>

#define WINDOW_SIZE 3

using window_t = std::list<int>;

int main ()
{
  std::cout << "Advent of code: day 01" << std::endl;

  auto list = std::list<int>{};
  for_each(std::istream_iterator<int>{std::cin}, std::istream_iterator<int>{}, [&list, window = window_t{}] (auto cur) mutable
     {
        window.push_back(cur);
        if (window.size() == 3)
        {
          list.push_back(std::accumulate(std::begin(window), std::end(window), 0));
          window.pop_front();
        }
     }
  );

  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto cur) mutable {
    return std::exchange(prev, cur) < cur;
  };
  auto n = count_if(list.begin(), list.end(), is_greater);

  std::cout << "Answer: " << n << std::endl;

  return 0;
}


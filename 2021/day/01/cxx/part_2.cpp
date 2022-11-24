#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <list>

#define WINDOW_SIZE 3

using window_t = std::list<int>;

int main ()
{
  std::cout << "Advent of code: day 01" << std::endl;

  auto is_greater = [prev = std::numeric_limits<int>::max()] (auto cur) mutable {
    return std::exchange(prev, cur) < cur;
  };

  auto list = std::list<int>{};

  for_each(std::istream_iterator<std::string>{std::cin}, std::istream_iterator<std::string>{}, [&list, window = window_t{}] (auto input) mutable
     {
        auto cur = std::atoi(input.c_str());

        window.push_back(cur);
        if (window.size() == 3)
        {
          auto count = 0;
          for (auto value : window)
          {
            count += value;
          }
          list.push_back(count);
          window.pop_front();
        }
     }
  );

  auto n = count_if(list.begin(), list.end(), is_greater);

  std::cout << "Answer: " << n << std::endl;

  return 0;
}


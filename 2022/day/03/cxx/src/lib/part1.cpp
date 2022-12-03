/**
 * Priorities
 * - Lowercase item types a through z have priorities 1 through 26.
 * - Uppercase item types A through Z have priorities 27 through 52.
*/
#include "part1.h"

#include <algorithm>
#include <iterator>
#include <cctype>

#define DEBUG 0

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto sum = 0;
  auto do_count = [&sum] (auto input) mutable {
    auto len = input.size() / 2;
    auto a = input.substr(0, len);  
    auto b = input.substr(len, input.size());

    auto it = std::find_first_of(std::begin(a), std::end(b), std::begin(b), std::end(b));
    auto prio = static_cast<int>(*it) - 'a' + 1 ;
    if (std::isupper(*it))
    {
      prio = static_cast<int>(*it) - 'A' + 27;
    }
    sum += prio;

#if DEBUG
    std::cout << prio << " (" << *it << ")" << std::endl;
#endif
  };

  std::for_each(std::istream_iterator<std::string>{in}, std::istream_iterator<std::string>{}, do_count);

  return sum;
}

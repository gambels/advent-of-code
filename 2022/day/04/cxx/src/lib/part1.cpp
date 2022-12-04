#include "part1.h"

#include <algorithm>

#define DEBUG 0

Part1::Part1()
{}

auto Part1::handle_input(std::istream& in) -> std::size_t
{
  auto n = 0;
  auto do_line = [&n] (auto& input) {

#if DEBUG
    std::cout << input._a.first << "-" << input._a.second << " " << input._b.first << "-" << input._b.second << std::endl;
#endif        

    auto is_all_of = [&input] (auto a, auto b) {
      if (b.first <= a.first && a.second <= b.second )
      {
        return true;
      }
      return false;
    };
    n += is_all_of(input._a, input._b) ? 1 : is_all_of(input._b, input._a) ? 1 : 0;
  };
  for_each(std::istream_iterator<Input>{in}, std::istream_iterator<Input>{}, do_line);
  
  return n;
}

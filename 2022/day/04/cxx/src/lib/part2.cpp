#include "part2.h"
#include "common.hpp"

#include <algorithm>

#define DEBUG 0

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> std::size_t
{
  auto n = 0;
  auto do_line = [&n] (auto& input) {

#if DEBUG
    std::cout << input._a.first << "-" << input._a.second << " " << input._b.first << "-" << input._b.second << std::endl;
#endif        
    n += Input::is_all_of(input._a, input._b) ? 1 : Input::is_all_of(input._b, input._a) ? 1 : 
         Input::is_part_of(input._a, input._b) ? 1 : Input::is_part_of(input._b, input._a) ? 1 : 0;
  };
  for_each(std::istream_iterator<Input>{in}, std::istream_iterator<Input>{}, do_line);
  
  return n;
}
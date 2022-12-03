#include "part2.h"

#include <algorithm>
#include <vector>
#include <array>
#include <list>

#define DEBUG 0

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> size_t
{
  auto groups = groups_t{};
  auto do_group = [&groups] (auto input) {
    groups.push_back(input._group);
#if DEBUG
  std::cout << std::string{input} << std::endl;
#endif
  };
  std::for_each(std::istream_iterator<Input>{in}, std::istream_iterator<Input>{}, do_group);

  auto sum = 0;
  auto do_count = [&sum] (auto& group) {
    auto a = group[0];
    auto b = group[1];
    auto c = group[2];

    auto is_part = [] (auto c) {

    };
    
    auto ab = std::string{};
    std::copy_if(std::begin(a), std::end(a), std::back_inserter(ab), [&b] (auto c) { auto n = b.find_first_of(c); return n != std::string::npos; });
    
    auto it = std::find_first_of(std::begin(c), std::end(c), std::begin(ab), std::end(ab));
    auto prio = static_cast<int>(*it) - 'a' + 1 ;
    if (std::isupper(*it))
    {
      prio = static_cast<int>(*it) - 'A' + 27;
    }
    sum += prio;

#if DEBUG
    std::cout << a << " " << b << " " << c << " : " << *it << std::endl;
#endif
  };
  std::for_each(std::begin(groups), std::end(groups), do_count);
  
  return sum;
}

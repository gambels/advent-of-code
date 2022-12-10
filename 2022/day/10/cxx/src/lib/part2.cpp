#include "part2.h"
#include "common.hpp"

using namespace aoc;

Part2::Part2()
{}

auto Part2::handle_input(std::istream& in) -> std::string
{
  auto image = std::stringstream{};
  auto do_render = [&image, crt_pixel = 0, crt_wide = 40] (auto pos) mutable
  {
    auto sprite = make_sprite(pos, crt_wide);
    image << sprite[crt_pixel];
    if (++crt_pixel == crt_wide)
    {
      crt_pixel = 0;
      image << std::endl;
    }
  };
  image << std::endl;
  std::ranges::for_each(make_register(in), do_render);
  
  return image.str();
}

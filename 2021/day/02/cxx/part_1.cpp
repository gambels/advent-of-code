#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <sstream>

struct Input
{
  enum class Direction
  {
    FORWARD,
    DOWN,
    UP
  };

  Input() {}

  auto key2direction() -> Direction
  {
    if (m_key == "forward")
    {
      return Direction::FORWARD;
    }
    else if (m_key == "down")
    {
      return Direction::DOWN;
    }
    else
    {
      return Direction::UP;
    }
  }

  std::string m_key;
  int m_value;
};

std::istream& operator>>(std::istream& in, Input& input)
{
  in >> input.m_key >> input.m_value;
  return in;
}

int main ()
{

  std::cout << "Advent of code: day 02" << std::endl;

  auto depth = 0;
  auto horizontal = 0;

  auto do_parse = [&] (auto input) {
    //std::cout << input.m_key << " " << input.m_value << std::endl;

    switch (input.key2direction())
    {
      case Input::Direction::FORWARD:
        horizontal += input.m_value;
        break;
      case Input::Direction::DOWN:
        depth += input.m_value;
        break;
      case Input::Direction::UP:
        depth -= input.m_value;
        break;
    }

  };
  for_each(std::istream_iterator<Input>{std::cin}, std::istream_iterator<Input>{}, do_parse);

  std::cout << "Answer: " << horizontal * depth << std::endl;

  return 0;
}

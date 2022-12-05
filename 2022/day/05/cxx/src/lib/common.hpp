#pragma once

#include <vector>
#include <map>
#include <istream>
#include <fstream>
#include <iostream>
#include <filesystem>

#define DEBUG 0

using stack_t = std::vector<char>;
using stacks_t = std::map<int, stack_t>;

inline
auto made_stacks(std::filesystem::path path) -> stacks_t
{
  auto file = std::ifstream(path);
  auto stacks = stacks_t{};  
  for (auto line = std::string{}; getline(file, line);)
  {
    auto id = int{0};
    auto stack = std::string{};
    std::stringstream{line} >> id >> stack;

    for_each(std::begin(stack), std::end(stack), [&stacks, id] (auto c) {stacks[id].push_back(c);});
  }
  return stacks;
}

inline
auto print_stacks(auto& stacks)
{
  auto do_print = [] (auto& stack) {
    auto& [id, cont] = stack;
    std::cout << "Stack: " << id << std::endl;
    for (auto& elem : cont)
    {
      std::cout << elem << " ";
    }
  };
  std::for_each(std::begin(stacks), std::end(stacks), do_print);
}

inline 
auto get_code(auto& stacks)
{
  auto code = std::string{};
  for (auto& elem : stacks)
  {
    auto& [id, cont] = elem;
    code += cont.back();
  }
  return code;
}
  
struct Input
{
  Input() {}

  int count = 0;
  int from = 0;
  int to = 0;
};

inline
std::istream& operator>>(std::istream& in, Input& input)
{
  // format: "move <n> from <id> to <id>""
  auto str = std::string{};
  in >> str >> input.count >> str >> input.from >> str >> input.to;
  return in;
}

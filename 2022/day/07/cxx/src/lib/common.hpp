#pragma once

#include <map>
#include <filesystem>
#include <istream>
#include <algorithm>
#include <ranges>

using path_t = std::filesystem::path;
using fs_t = std::map<std::filesystem::path, size_t>;

struct Input
{
  Input() {}

  std::string line;
};

inline
std::istream& operator>>(std::istream& in, Input& input)
{
  getline(in, input.line);
  return in;
}

inline
auto made_fs(std::istream& in)
{
  auto fs = fs_t{};
  auto cur_path = path_t{};
  
  auto do_line = [&, already_listed = false] (auto& input) mutable {
    if (input.line.find("$ cd ") != std::string::npos)
    {
      auto dir = input.line.substr(5);
      cur_path = (dir == "..") ? cur_path.parent_path() : cur_path / dir;
    }
    else if (input.line.find("$ ls") != std::string::npos)
    {
      already_listed = fs.find(cur_path) != fs.end() ? true : false;
    }
    else if (auto size = size_t{0}; std::stringstream{input.line} >> size && !already_listed)
    {
      fs[cur_path] += size;

      auto add_size_to_parent = [&fs] (auto path, auto size) {
        while (path.parent_path() !=  path)
        {
            path = path.parent_path();
            fs[path] += size;
        }
      };
      add_size_to_parent(cur_path, size);
    }
  };
  std::ranges::for_each(std::ranges::istream_view<Input>(in), do_line);

  return fs;
}
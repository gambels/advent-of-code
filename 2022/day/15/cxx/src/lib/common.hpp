#pragma once

#include <istream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <regex>
#include <list>
#include <vector>

namespace aoc
{
  struct Input
  {
    struct Sensor
    {
      int64_t x;
      int64_t y;
    };

    struct Beacon
    {
      int64_t x;
      int64_t y;
    };

    Input() {}

    auto distance() const
    {
      return std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y);
    }

    Sensor sensor;
    Beacon beacon;
  };
  using scan_t = std::vector<Input>;

  struct Interval
  {
    friend auto operator<=>(const Interval&, const Interval&) =default;

    auto is_adjacent(const Interval& rhs)
    {
      if ((max + 1 <= rhs.min) || (rhs.max + 1 <= min))
      {
        return false;
      }
      return true;
    }

    auto join(const Interval& rhs)
    {
      auto min = std::min(this->min, rhs.min);
      auto max = std::max(this->max, rhs.max);

      return Interval{.min = min, .max = max};
    }

    int64_t min;
    int64_t max;
  };
  using intervals_t = std::vector<Interval>;

  inline
  std::istream& operator>>(std::istream& in, Input& input)
  {
    auto line = std::string{};
    getline(in, line);

    auto do_line = [&input] (auto& match) {
      std::stringstream{match.str(1)} >> input.sensor.x;
      std::stringstream{match.str(2)} >> input.sensor.y;
      std::stringstream{match.str(3)} >> input.beacon.x;
      std::stringstream{match.str(4)} >> input.beacon.y;
    };
    auto regex = std::regex("Sensor at x=([0-9-]+), y=([0-9-]+): closest beacon is at x=([0-9-]+), y=([0-9-]+)");
    std::ranges::for_each(std::sregex_iterator{std::begin(line), std::end(line), regex}, std::sregex_iterator{}, do_line);

    return in;
  }

  inline
  auto make_scan(std::istream& in)
  {
    auto scan = std::vector<Input>{};
    auto do_input = [&] (auto& input) {
      scan.push_back(input);
    };
    std::ranges::for_each(std::ranges::istream_view<Input>(in), do_input);

    return scan;
  }

  inline 
  auto dissect(const scan_t& scan, auto row)
  {
    auto intervals = intervals_t{};
    auto do_dissect = [&] (const auto& input)
    {
      auto max_dist = input.distance();;
      if (max_dist < std::abs(input.sensor.y - row))
      {
        return;
      }
      auto dist = max_dist - std::abs(input.sensor.y - row);
      auto min = input.sensor.x - dist;
      auto max = input.sensor.x + dist;
      intervals.emplace_back(Interval{.min = min, .max = max});
    };
    std::ranges::for_each(scan, do_dissect);
    std::ranges::sort(intervals);

    auto merged = intervals_t{};
    auto prev = intervals.front();
    auto do_merge = [&] (const auto& interval) mutable
    {
      if (prev.is_adjacent(interval))
      {
        prev = prev.join(interval);
      }
      else
      {
        merged.push_back(prev);
        prev = interval;
      }
    };
    std::ranges::for_each(intervals, do_merge);
    merged.push_back(prev);

    return merged;
  }

} // namespace aoc

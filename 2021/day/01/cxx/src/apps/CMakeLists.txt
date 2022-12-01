add_executable(aoe-day${AOE_DAY}-part1 part1.cpp)
target_link_libraries(aoe-day${AOE_DAY}-part1 PRIVATE part1)

add_executable(aoe-day${AOE_DAY}-part2 part2.cpp)
target_link_libraries(aoe-day${AOE_DAY}-part2 PRIVATE part2)

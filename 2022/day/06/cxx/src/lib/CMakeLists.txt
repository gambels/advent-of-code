add_library(part1 STATIC part1.cpp part1.h)
target_include_directories(part1 PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_library(part2 STATIC part2.cpp part2.h)
target_include_directories(part2 PUBLIC "${PROJECT_SOURCE_DIR}/src")

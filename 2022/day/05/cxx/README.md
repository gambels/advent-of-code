# Advent of code - Day 5

## Convert Puzzle Input

```sh
$ cd test
$ ./convert_puzzle_input.sh puzzle_input.txt
$ cd -
```

## Build

```sh
$ cmake -S . -B build -DAOE_DAY=5 && cd build
$ cmake --build build
```

## Run

```sh
$ ./build/bin/aoe-day5-part1 ./test/puzzle_input.txt.stacks < ./test/puzzle_input.txt.work
$ ./build/bin/aoe-day5-part2 ./test/puzzle_input.txt.stacks < ./test/puzzle_input.txt.work
```


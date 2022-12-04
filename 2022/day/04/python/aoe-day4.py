#!/usr/bin/env python

import os
import sys

aoe_day = 4

def is_all_of(lhs, rhs):
    a1, a2 = lhs
    b1, b2 = rhs
    if int(b1) <= int(a1) and int(a2) <= int(b2):
        return True
    return False

def is_part_of(lhs, rhs):
    a1, a2 = lhs
    b1, b2 = rhs
    if int(b1) <= int(a2) and int(a1) <= int(b2):
        return True
    return False

def do_part1():
    n = int(0)
    for line in sys.stdin.readlines():
        lhs, rhs = line.rstrip().split(',')
        a1, a2 = lhs.split('-')
        b1, b2 = rhs.split('-')

        if is_all_of((a1, a2), (b1, b2)) or is_all_of((b1, b2), (a1, a2)):
            n += 1

    return n

def do_part2():
    n = int(0)
    for line in sys.stdin.readlines():
        lhs, rhs = line.rstrip().split(',')
        a1, a2 = lhs.split('-')
        b1, b2 = rhs.split('-')

        if is_part_of((a1, a2), (b1, b2)):
            n += 1

    return n

if __name__ == '__main__':
    name = os.path.basename(__file__)
    if "part1" in name:
        aoe_part = 1
        n = do_part1()
    if "part2" in name:
        aoe_part = 2
        n = do_part2()

    print(f"Adven of code: day {aoe_day} / part {aoe_part}")
    print(f"Answer: {n}")

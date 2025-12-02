# Advent of Code 2025 - Day 2: Gift Shop Database

## Problem Summary

A young Elf accidentally added invalid product IDs to the gift shop database. We need to identify and sum all invalid IDs within given ranges.

### Part 1
An ID is **invalid** if it's made of a sequence of digits repeated **exactly twice**.

**Examples:**
- `11` = "1" repeated twice ✓
- `6464` = "64" repeated twice ✓
- `123123` = "123" repeated twice ✓

### Part 2
An ID is **invalid** if it's made of a sequence of digits repeated **2 or more times**.

**Examples:**
- `111` = "1" repeated 3 times ✓
- `999` = "9" repeated 3 times ✓
- `123123123` = "123" repeated 3 times ✓
- `1212121212` = "12" repeated 5 times ✓
- `1111111` = "1" repeated 7 times ✓

## Solution Approach

### Part 1 Algorithm
1. Parse comma-separated ranges from input
2. For each number in each range:
   - Convert to string
   - Check if length is even
   - Compare first half with second half
   - If they match, it's invalid
3. Sum all invalid IDs

### Part 2 Algorithm
1. Parse comma-separated ranges from input
2. For each number in each range:
   - Try all possible pattern lengths (1 to length/2)
   - For each pattern length that divides evenly:
     - Check if the entire number is that pattern repeated
   - If any pattern repeats 2+ times, it's invalid
3. Sum all invalid IDs

## Files

- `part1/solution.c` - Part 1 solution (patterns repeated exactly twice)
- `part2/solution.c` - Part 2 solution (patterns repeated 2+ times)
- `input.txt` - Puzzle input (ranges of product IDs)

## Compilation & Execution
```bash
make

./solution-part-1 path/to/input
./solution-part-2 path/to/input
```

## Features

- **Dynamic memory allocation** - handles any input size
- **Debug mode** - set `DEBUG 1` to see detailed progress
- **Error handling** - validates ranges and input format
- **Performance warnings** - alerts for large ranges

## Key Insights

- Part 2 includes all invalid IDs from Part 1 plus additional patterns
- The difference (~25 billion) comes from 3-digit repeats, triple patterns, etc.
- Pattern detection uses modulo arithmetic to check repetitions efficiently

## Complexity

- **Time:** O(n × m × p) where:
  - n = number of ranges
  - m = size of each range
  - p = number of pattern lengths to check (log of number length)
- **Space:** O(1) - only stores current number as string

---

**Advent of Code 2025 - Day 2**  
[adventofcode.com](https://adventofcode.com/2025/day/2)*
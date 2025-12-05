# Advent of Code 2025 - Day 2: Escalator Power

Solution for Advent of Code 2025 Day 2 puzzle in C.

## Problem Summary

You need to power an escalator by selecting batteries from banks. Each battery has a joltage rating (digit 1-9).

- **Part 1**: Select exactly 2 batteries per bank to maximize the 2-digit joltage
- **Part 2**: Select exactly 12 batteries per bank to maximize the 12-digit joltage

The batteries must maintain their original order (no rearranging).

## Files

- `escalator.c` - Main solution (currently configured for Part 2)
- `input.txt` - Your puzzle input

## Compilation
```bash
gcc -o escalator escalator.c
```

## Usage
```bash
./escalator input.txt
```

## Switching Between Parts

To switch between Part 1 and Part 2, modify the `BATTERIES_TO_SELECT` constant at the top of `escalator.c`:
```c
#define BATTERIES_TO_SELECT 2   // For Part 1
#define BATTERIES_TO_SELECT 12  // For Part 2
```

Then recompile.

## Example Input
```
987654321111111
811111111111119
234234234234278
818181911112111
```

## Example Output

### Part 1 (2 batteries)
```
Bank 1: 987654321111111
  Result: 98
  ...
Total output joltage: 357
```

- `987654321111111` → `98`
- `811111111111119` → `89`
- `234234234234278` → `78`
- `818181911112111` → `92`
- **Total: 357**

### Part 2 (12 batteries)
```
Bank 1: 987654321111111 (length 15)
  Position 0: searching indices [0, 3], need 11 more after
    → Selected '9' at index 0
  Position 1: searching indices [1, 4], need 10 more after
    → Selected '8' at index 1
  ...
  Result: 987654321111
  Joltage: 987654321111
  Running total: 987654321111

==================
Total output joltage: 3121910778619
```

- `987654321111111` → `987654321111`
- `811111111111119` → `811111111119`
- `234234234234278` → `434234234278`
- `818181911112111` → `888911112111`
- **Total: 3121910778619**

## Algorithm

### Part 1
For each bank, try every possible pair of batteries in order and find the maximum 2-digit number.

### Part 2
Uses a greedy approach: for each output position, select the largest available digit that leaves enough digits for the remaining positions.

**Time Complexity:**
- Part 1: O(n²) per bank where n is the length
- Part 2: O(n × k) per bank where k is the number of batteries to select

## Notes

- Handles lines up to 1024 characters
- Uses `unsigned long long` for large joltage values in Part 2
- Debug output shows the selection process for each bank
- Skips lines with fewer digits than required
# Safe Dial Solver

A C program that solves the Advent of Code day one puzzle.

## Problem

The safe has a dial with positions 0-99. Starting at position 50, follow rotation instructions (L/R followed by distance) and count how many times the dial points at 0.

- **Part 1**: Count only when the dial *ends* on position 0 after a rotation
- **Part 2**: Count *every click* that passes through 0 during any rotation added to part 1

## Files

- `solution.c` - Main program
- `Makefile` - Build configuration
- `input.txt` - Example input from problem description

## Build

```bash
make
```

## Usage

```bash
./solution-part-2.exe input.txt
```

## Example

Given rotations starting from position 50:
```
L68  -> position 82 (passed through 0 once)
L30  -> position 52
R48  -> position 0  (passed through 0 once, ends on 0)
```

- Part 1 counts: 1 (only the final 0)
- Part 2 counts: 3 (both times we clicked through 0 and ended on 0)

## Clean

```bash
make clean
```

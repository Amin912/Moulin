# Moulin

Nine Men's Morris (*le jeu du moulin*) in the terminal, written in C. Two
players share the keyboard, or one plays against the computer.

## The board

Each point is named by its square (1 is the outer square, 3 the inner one)
followed by its position (1 to 8, clockwise from the top-left corner). To
place a piece on the top-left corner of the middle square, type `2` then `1`.

```
11 ------------- 12 ------------- 13
 |                |                |
 |    21 ------- 22 ------- 23     |
 |     |          |          |     |
 |     |    31 - 32 - 33     |     |
 |     |     |         |     |     |
18 -- 28 -- 38        34 -- 24 -- 14
 |     |     |         |     |     |
 |     |    37 - 36 - 35     |     |
 |     |          |          |     |
 |    27 ------- 26 ------- 25     |
 |                |                |
17 ------------- 16 ------------- 15
```

## Rules

- Each player has nine pieces. Players take turns placing them on empty points.
- Three pieces in a line along a side of a square, or across the squares at a
  side's midpoint, form a mill. Forming a mill lets you remove one of the
  opponent's pieces that is not itself in a mill.
- Once all pieces are placed, players move a piece to an adjacent empty point:
  `1` clockwise, `2` anticlockwise, `3` to the next square in, `4` to the
  previous square out.
- A player loses when they are down to two pieces or cannot move.
- There is no "flying" phase: with three pieces left, pieces still move
  to adjacent points only.

The computer opponent plays randomly on Easy. On Medium it completes its own
mills and blocks yours while placing pieces.

## Building

With CMake:

```sh
cmake -S . -B build
cmake --build build --config Release
```

Or directly with any C11 compiler:

```sh
cc -std=c11 main.c -o moulin
```

It runs in any terminal that understands ANSI colours, including Windows
Terminal and the Windows 10+ console.

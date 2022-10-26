# Simple_Shogi

## Mini shogi game program

* Shogi
* Usage of data store methods
 
-------------------------------------
# Mini Shogi game in C

This is assignment 2 of Data Structure.

> There are some instrucion that the user need to enter them manually 
> 
> Which will be display by code block above

## About board display
include:
* A 9x9 board, row(段) 1-9 from right to left, and column(筋) 1-9 from upward to downward
* 20 chess for both user: 步x9, 香x2, 桂x2, 銀x2, 金x2, 角x1, 飛x1, 玉x1
* Mochigoma bag for each player
```
# Example
--------- player y ---------
　　　　　　　　　　　　　　　　　　　　
============================
9  8  7  6  5  4  3  2  1  
香 桂 銀 金 玉 金 銀 桂 香 1
　 飛 　 　 　 　 　 角 　 2
步 步 步 步 步 步 步 步 步 3
　 　 　 　 　 　 　 　 　 4
　 　 　 　 　 　 　 　 　 5
　 　 　 　 　 　 　 　 　 6
步 步 步 步 步 步 步 步 步 7
　 角 　 　 　 　 　 飛 　 8
香 桂 銀 金 玉 金 銀 桂 香 9
============================
　　　　　　　　　　　　　　　　　　　　
--------- player x ---------
```

## Usage
1. Print the initial board(Blue for playerx, and red for player y)
2. Display the turn number and which player's turn
3. Start from player x, and take turns enter above data:
4. Enter the position of assigned chess in format:x y  //need to seperate wuth space
5. Enter the position for the assigned chess to go in format:x y
```
# Example
Turn 1
Player  x:
  Enter the initial position: 9 9   //need to seperate with space
  Enter the new position: 9 8
```
6. The program will show user whether the movement is available
7. If movement available, then program will execute.If not, it would ask user to enter again
```
# Example of Error message
  You can not move to here.
  Error: 步 can only move forward one step.
  Please try again.
```
8. If the movement include eating others chess, the chess will be place in eater's 'mochigoma bag'
```
#Example
--------- player y ---------
步 　　　　　　　　　　　　　　　　　　　
============================
9  8  7  6  5  4  3  2  1  
香 桂 銀 金 玉 金 銀 桂 香 1
　 飛 　 　 　 　 　 角 　 2
　 步 步 步 步 步 　 步 步 3
　 　 　 　 　 　 步 　 　 4
步 　 　 　 　 　 　 　 　 5
　 　 　 　 　 　 　 　 　 6
　 步 步 步 步 步 步 步 步 7
香 角 　 　 　 　 　 飛 　 8
　 桂 銀 金 玉 金 銀 桂 香 9
============================
　　　　　　　　　　　　　　　　　　　　
--------- player x ---------
```

9. Each turn will be writen into a csv file named "game_record.csv"

# Compile & Run

```
# Compile
gcc -o shogi main.c board.c chess.c stack.c -lev
```
```
# Run
./shogi
```
# Reference
[Shogi rule](https://shogi.hk/Gameplay-of-Japanese-Chess-Shogi/)

> 將棋走法玩法

[Color output in C](https://www.796t.com/article.php?id=190246)

> print color text in C

[Code reference of pgn](https://github.com/cutechess/sloppy/blob/master/src/pgn.c)

> A code of using pgn to save each games' chess noatation

[Libev tutorial](https://gohalo.me/post/linux-libev.html)

> Instruction of Libev and basic example code

[Libev tutorial](https://github.com/redis/hiredis)

> Instruction of Libev and basic example code

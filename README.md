## Practice of coding skills by making a Maze Generator and Solver

### About
the goal is to create an algorithm capable of generating random, fully solvable mazes and implementing an "autocomplete" feature where the computer finds the solution automatically using the A Search Algorithm*.

## This is practice of logic and memory management in C++

### Features
* **Random Maze Generation:** Uses Recursive Backtracking to ensure every part of the maze is reachable.
* **Customizable Size:** Users can define the dimensions of the maze or use a default 11x11 grid.
* **Dynamic Obstacles:** Includes varied terrain like water and stones with different traversal costs.
* **A* Pathfinding:** An optimized solver that calculates the most efficient path from start to finish.
* **Visual Simulation:** Console-based animation that shows the maze being solved in real-time.

### Prerequisites
* **C++ Compiler** (MinGW, GCC, or Clang).
* **Header Files:** Ensure `funciones.h` is present in your directory with the `Node` struct and `CompararNodes` class definitions.

## Setup & Execution 

1. **Clone the repo**
```bash
git clone [https://github.com/SadCloud03/Maze-Generator.git](https://github.com/SadCloud03/Maze-Generator.git)
cd Maze-Generator
```
2. **Copile the project**
```bash 
g++ main.cpp funciones.cpp -o maze_solver.exe
```

3. **Run the application**
```bash 
./maze_solver.exe
```


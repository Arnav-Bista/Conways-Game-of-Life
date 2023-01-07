# Conway's Game of Life

## Is it a game?

Conway's game of life isn't really a game. It is a cellular automation (simulation) invented by Cambridge Mathematician John Conway.

The simulation consists of a grid of cells. Each of these cells can either be dead or alive. These cells follow a small set of rules that determine if they are dead or alive in the next iteration.

(Neighbours signify cells that are alive)

Here are the rules of the game:

- For a cell that is alive:
  - Each cell with one or no neighbours die, as if by solitude.
  - Each cell with four or more neighbours die, as if by overpopulation
  - Each cell with two or three neighbours survive.
- For a cell that is dead:
  - Each cell with exactly three neighbours become populated.

Using these four rules, we can create interesting automations and witness how these cell evolve into something eye catching.

## Code and Application

I've developed this using `C++` and `SFML` for the GUI. I initially built the application in `Python` with `Pygame` but wanted to work with something lower level and closer to hardware for a simulation. Luckily, `Pygame` and `SFML` had a lot in common regarding how graphics are rendered and the event cycle.

If you wish, you can edit the `main.cpp` file and adjust the grid size, window size, top offset size, and so on.

### Build

To compile the application into binaries, execute the following commands:

```sh
g++ -c main.cpp
g++ main.o -o ConwaysGameOfLife -lsfml-graphics -lsfml-window -lsfml-system
```

You should then have an executable called `ConwaysGameOfLife`.

### Usage

The usage of this application is fairly simple.

The `<SPACE>` key pauses and unpauses the simulation.
Use `<MOUSE LEFT CLICK>` to change the state of the cells. Dragging is supported.

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


class Game {
private:
  std::vector<std::vector<bool>> A_board;
  std::vector<std::vector<bool>> B_board;
  std::vector<std::vector<bool>>* current;
  std::vector<std::vector<bool>>* next;
  std::vector<std::vector<bool>>* temp;
  int size;

public:
  Game(int size) {
    // + 2 to avoid checking for edge cases.
    this->size = size;
    A_board = std::vector<std::vector<bool>>(
        size + 2, 
        std::vector<bool>(size + 2, false)
      );
    B_board = std::vector<std::vector<bool>>(
        size + 2, 
        std::vector<bool>(size + 2, false)
      );

    current = &A_board;
    next = &B_board;
  }

  // This function has to get x and y within bounds (within + 2)
  int getNeighbours(int x, int y) {
    int neighbours = 0;
    for(int i = x - 1; i < x + 2; i++) {
      for(int j = y - 1; j < y + 2; j++){
        if(i == x && j == y) {
          continue;
        }
        if((*current)[i][j]) {
          neighbours += 1;
        }
      }
    }
    return neighbours;
  }
  void set(int x, int y, bool val) {
    (*current)[x][y] = val;
  }

  void flip(int x, int y) {
    (*current)[x][y] = !(*current)[x][y];
  }
  
  void update() {
    int num_neighbours;
    for(int i = 1; i <= size; i++) {
      for(int j = 1; j <= size; j++) {
        num_neighbours = getNeighbours(i, j);
        if(num_neighbours < 2) {
          (*next)[i][j] = false;
        }
        else if(num_neighbours > 3) {
          (*next)[i][j] = false;
        }
        else if(num_neighbours == 3) {
          (*next)[i][j] = true;
        }
        else {
          (*next)[i][j] = (*current)[i][j];
        }
      }
    }
    temp = current;
    current = next;
    next = temp;
  }

  void print() {
    std::string res;
    for(int i = 1; i <= size; i++) {
      for(int j = 1; j <= size; j++) {
        res = (*current)[i][j] ? "1" : "0";
        std::cout << res << " ";
      }
      std::cout << "\n";
    }
  }
  
  std::vector<std::vector<bool>>* getBoard() {
    return current;
  }

};

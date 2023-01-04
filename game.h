#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#ifndef GAME_H
#define GAME_H

class Game {
private:
  std::vector<bool> A_board;
  std::vector<bool> B_board;
  std::vector<bool>* current;
  std::vector<bool>* next;
  std::vector<bool>* temp;
  int size;

public:
  Game(int size) {
    // + 2 to avoid checking for edge cases.
    this->size = size + 2;
    A_board = std::vector<bool>(
        this->size * this->size,
        false
      );
    B_board = std::vector<bool>(
        this->size * this->size,
        false
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
        if((*current)[i + j * size]) {
          neighbours += 1;
        }
      }
    }
    return neighbours;
  }
  void set(int x, int y, bool val) {
    (*current)[x + y * size] = val;
  }

  void flip(int x, int y) {
    (*current)[x + y * size] = !(*current)[x + y * size];
  }
  
  void update() {
    int num_neighbours;
    for(int i = 1; i <= size; i++) {
      for(int j = 1; j <= size; j++) {
        num_neighbours = getNeighbours(i, j);
        if(num_neighbours < 2) {
          (*next)[i + j * size] = false;
        }
        else if(num_neighbours > 3) {
          (*next)[i + j * size] = false;
        }
        else if(num_neighbours == 3) {
          (*next)[i + j * size] = true;
        }
        else {
          (*next)[i + j * size] = (*current)[i + j * size];
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
        res = (*current)[i + j * size] ? "1" : "0";
        std::cout << res << " ";
      }
      std::cout << "\n";
    }
  }
  
  std::vector<bool>* getBoard() {
    return current;
  }

  bool getCell(int i, int j) {
    return (*current)[(i + size + 1) + j * size];
  }

  void setCell(int i, int j, bool value) {
    (*current)[i + size + 1 + j * size] = value;
  }

};

#endif 


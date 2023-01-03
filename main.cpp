#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "game.h"


const float SCREEN_X = 500.0;
const float SCREEN_Y = 500.0;
const float SCREEN_BPP = 32;
const float TOP_OFFSET = 50;
const int SIZE = 20;

void fillColor(std::vector<sf::RectangleShape>& drawTable) {
  for(int i = 0; i < SIZE*SIZE; i++) {
    drawTable[i].setFillColor(sf::Color(243, 243, 244));
  }
}

void setPosition(std::vector<sf::RectangleShape>& drawTable, float size_x, float size_y) {
  for(int i = 0; i < SIZE; i++) {
    for(int j  = 0; j < SIZE; j++) {
      drawTable[i * SIZE + j].setPosition(size_x * j, size_y * i + TOP_OFFSET);
      // drawTable[i * SIZE + j].setFillColor(sf::Color::Blue);
    }
  }
}

void changeColor(std::vector<sf::RectangleShape>& drawTable, int i, int j, sf::Color color) {
  drawTable[i + j * SIZE].setFillColor(color);
}

int main() {
  
  float size_x = SCREEN_X / SIZE;
  float size_y = (SCREEN_Y - TOP_OFFSET)/ SIZE;

  int hover_x = 0;
  int hover_y = 0;

  sf::RenderWindow window(sf::VideoMode(SCREEN_X,SCREEN_Y,SCREEN_BPP), "Conway's Game of Life");
  Game game(SIZE);
  sf::RectangleShape rectangle(sf::Vector2f(size_x,size_y));
  window.setVerticalSyncEnabled(true);

  std::vector<sf::RectangleShape> drawTable
    (
      SIZE * SIZE, 
      sf::RectangleShape(
        sf::Vector2f(
          size_x,
          size_y 
        )
      )
    );
  
  fillColor(drawTable);
  setPosition(drawTable, size_x, size_y);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    sf::Vector2i position = sf::Mouse::getPosition(window);
    std::cout << position.x << " " << position.y << "\n";
    window.clear(sf::Color(52, 52, 74));
  
    // Clear Hover
    changeColor(drawTable,hover_x,hover_y,sf::Color(243, 243, 244));
    
    // Handle Hover
    if(position.y > TOP_OFFSET && position.y < SCREEN_Y && position.x < SCREEN_X) {
      hover_x = position.x / size_x;
      hover_y = (position.y - TOP_OFFSET) / size_y;
      changeColor(drawTable,hover_x,hover_y, sf::Color(247, 179, 43));
    }
    // Draw Squares
    for(sf::RectangleShape rect : drawTable) {
      window.draw(rect);
    }
    window.display();
  }
}







#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <vector>

#include "game.h"

class Graphics {
private:
  float SCREEN_X;
  float SCREEN_Y;
  float SCREEN_BPP;
  float TOP_OFFSET;
  int SIZE;

  float size_x;
  float size_y;

  sf::Color HOVER;
  sf::Color ACTIVE;
  sf::Color INACTIVE;
  sf::Color BLEND;
  sf::Color BACKGROUND;

  std::vector<sf::RectangleShape> drawTable;
  std::vector<bool> affected;

  bool mouseClick;
  bool gameActive;
  bool state;

  std::vector<bool>* board;
  
  Game game;

  void handleMouseInteractions(sf::Vector2i position) {
    int x, y;
    if(position.y > TOP_OFFSET && position.y < SCREEN_Y && position.y > 0 && position.x > 0 && position.x < SCREEN_X) {
      x = position.x / size_x;
      y = (position.y - TOP_OFFSET) / size_y;
      drawTable[x + y * SIZE].setFillColor(HOVER);
      if(!mouseClick) {
        if(game.getCell(x,y)) {
         drawTable[x + y * SIZE].setFillColor(BLEND);
         }
        else {
            drawTable[x + y * SIZE].setFillColor(HOVER);
          }
      }
      else {
        // Mouse is held down
        if(!affected[x + y * SIZE]){
          if (state) {
            drawTable[x + y * SIZE].setFillColor(ACTIVE);
          }
          else {
            drawTable[x + y * SIZE].setFillColor(INACTIVE);
          }
          // drawTable[x + y * SIZE].setFillColor(state ? ACTIVE : INACTIVE);
          game.setCell(x, y, state);
          affected[x + y * SIZE] = true;
        }
      }
    }
  }

  void clearStates() {
    // Affected IF MOUSE IS RELEASED
    if (!mouseClick) {
      for(int i = 0; i < SIZE * SIZE; i++) {
        affected[i] = false;
      }
    }
    // Hover effects
    for(int i = 0; i < SIZE; i++) {
      for(int j = 0; j < SIZE; j++) {
        if (game.getCell(i,j)) {
          drawTable[i + j * SIZE].setFillColor(ACTIVE);
        }
        else {
          drawTable[i + j * SIZE].setFillColor(INACTIVE);
        }
      }
    }
  }

public:
  Graphics(
    float SCREEN_X,
    float SCREEN_Y,
    float SCREEN_BPP,
    float TOP_OFFSET,
    int SIZE
  ) : game(SIZE) {
    this->SCREEN_X = SCREEN_X;
    this->SCREEN_Y = SCREEN_Y;
    this->SCREEN_BPP = SCREEN_BPP;
    this->TOP_OFFSET = TOP_OFFSET;
    this->SIZE = SIZE;

    size_x = SCREEN_X / SIZE;
    size_y = (SCREEN_Y - TOP_OFFSET) / SIZE;

    HOVER = sf::Color(184,51,106);
    ACTIVE = sf::Color(247, 179, 43);
    BLEND = sf::Color(118,52,90);
    INACTIVE = sf::Color(243,243,244);
    BACKGROUND = sf::Color(29, 52, 97);

    affected = std::vector<bool>(SIZE*SIZE, false);
    drawTable = std::vector<sf::RectangleShape>(
        SIZE * SIZE,
        sf::RectangleShape(
          sf::Vector2f(
            size_x,
            size_y
          )
        )
      );
    
    for(int i = 0; i < SIZE; i++) {
      for(int j = 0; j < SIZE; j++) {
        drawTable[i + j * SIZE].setPosition(i * size_x, TOP_OFFSET + j * size_y);
      }
    }
    mouseClick = false;
    gameActive = false;
  }
  
  void setState(sf::Vector2i position) {
    int x, y;
    if(position.y > TOP_OFFSET && position.y < SCREEN_Y && position.y > 0 && position.x > 0 && position.x < SCREEN_X) {
      x = position.x / size_x;
      y = (position.y - TOP_OFFSET) / size_y;
      state = !game.getCell(x,y);
    }
    
  }

  void setBoard(std::vector<bool>* board) {
    this->board = board;
  }

  void run() {
    sf::RenderWindow window(
        sf::VideoMode(
          SCREEN_X,
          SCREEN_Y,
          SCREEN_BPP
        ),
        "Conway's Game of Life"
      );
    window.setFramerateLimit(144);

    sf::Font font;
    if(!font.loadFromFile("FiraCodeNF.ttf")) {
      std::cout << "ERROR LOADING FONTS. Can't find 'FiraCodeNF.ttf'\n";
      return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("SIMULATION PAUSED");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    while (window.isOpen()) {
      sf::Event event;
      sf::Vector2i position = sf::Mouse::getPosition(window);

      while (window.pollEvent(event)) {
        switch (event.type){
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::KeyPressed:
            switch (event.key.code) {
              case sf::Keyboard::Space:
                gameActive = !gameActive;
                text.setString(gameActive ? "SIMULATION RUNNING" : "SIMULATION PAUSED");
              default:
                break;
            }
          case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
              mouseClick = true;
              setState(position);
            }
            break;
          case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
              mouseClick = false;
            }
            break;
          default:
            break;
        }
      }
      window.clear(BACKGROUND);

      if (window.hasFocus()){
        handleMouseInteractions(position);
      }
      
      for(sf::RectangleShape rect : drawTable) {
        window.draw(rect);
      }

      window.draw(text);
      
      window.display();
      clearStates();
      if (gameActive) {
        game.update();
      }
    }
  }
};


















#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

#include "game.h"
#include "graphics.h"


const float SCREEN_X = 500.0;
const float SCREEN_Y = 500.0;
const float SCREEN_BPP = 32;
const float TOP_OFFSET = 50;
const int SIZE = 20;

const sf::Color HOVER(184,51,106);
const sf::Color ACTIVE(52,52,74);
const sf::Color BLEND(118,52,90);

int main() {
  Game game(SIZE);
  Graphics graphics(
      SCREEN_X,
      SCREEN_Y,
      SCREEN_BPP,
      TOP_OFFSET,
      SIZE
    );
  graphics.run();
}

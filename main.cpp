#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

#include "game.h"
#include "graphics.h"


const float SCREEN_X = 600.0;
const float SCREEN_Y = 700.0;
const float SCREEN_BPP = 32;
const float TOP_OFFSET = 50;
const int SIZE = 50;

int main() {
  Graphics graphics(
      SCREEN_X,
      SCREEN_Y,
      SCREEN_BPP,
      TOP_OFFSET,
      SIZE
    );
  graphics.run();
}

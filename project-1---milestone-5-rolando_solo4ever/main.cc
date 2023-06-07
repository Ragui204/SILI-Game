#include <iostream>
#include <vector>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game game;
  game.Init();
  game.UpdateScreen();
  game.Start();

  return 0;
}

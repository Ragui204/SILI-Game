#ifndef PLAYER_H
#define PLAYER_H

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  void Draw(graphics::Image& image) override;
  Player();
  Player(int x, int y);
  void Move(const graphics::Image& image) override;
};

class PlayerProjectile : public GameElement {
 public:
  void Draw(graphics::Image& image) override;
  PlayerProjectile();
  PlayerProjectile(int x, int y);
  void Move(const graphics::Image& image) override;
};

#endif

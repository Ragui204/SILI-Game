
#ifndef OPPONENT_H
#define OPPONENT_H

#include "game_element.h"


   // Projectile class
class OpponentProjectile : public GameElement {
  public:
   // Member functions
   void Draw(graphics::Image& image) override;
   void Move(const graphics::Image& image) override;
   // Constructors
   OpponentProjectile();
   OpponentProjectile(int x, int y);
};

class Opponent : public GameElement {
 private:
  int counter_;
 public:
  // Constructors
  Opponent();
  Opponent(int x, int y);
  // Member Functions
 void Draw(graphics::Image& image) override;
 void Move(const graphics::Image& image) override;
 std::unique_ptr<OpponentProjectile> LaunchProjectile(); // Addded a LaunchProjectile().
};

#endif

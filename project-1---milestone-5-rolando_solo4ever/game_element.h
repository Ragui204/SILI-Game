#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

//#include "cpputils/graphics/image.h"

class GameElement {
 private:
  int x_ = 0;
  int y_ = 0;
  int width_;
  int height_;
  bool is_active = true;

 public:
  // Constructors
  GameElement();
  GameElement(int x, int y, int width, int height);
  // Setters
  void SetX(int x);
  void SetY(int y);
  void SetIsActive(bool active);
  // Getters
  int GetX();
  int GetY();
  int GetWidth();
  int GetHeight();
  bool GetIsActive();
  // Member Fuctions
  virtual void Draw(graphics::Image& image) = 0;
  virtual void Move(const graphics::Image& image) = 0;
  bool IntersectsWith(GameElement* element); // Modified to reciev a Game element pointer.
  bool IsOutOfBounds(const graphics::Image& image);
};
#endif

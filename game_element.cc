#include "game_element.h"

#include "cpputils/graphics/image.h"

GameElement::GameElement() {
  this->x_ = 0;
  this->y_ = 0;
  this->width_ = 50;
  this->height_ = 50;
  this->is_active = true;
}
GameElement::GameElement(int x, int y, int width, int height) {
  this->x_ = x;
  this->y_ = y;
  this->width_ = width;
  this->height_ = height;
}
// Setters
void GameElement::SetX(int x) { x_ = x; }
void GameElement::SetY(int y) { y_ = y; }
void GameElement::SetIsActive(bool active) { is_active = active; }
// Getters
int GameElement::GetX() { return x_; }
int GameElement::GetY() { return y_; }
int GameElement::GetWidth() { return width_; }
int GameElement::GetHeight() { return height_; }
bool GameElement::GetIsActive() { return is_active; }
// Member Fuctions
bool GameElement::IntersectsWith(GameElement* element) {
  return !(GetX() > element->GetX() + element->GetWidth() ||
           element->GetX() > GetX() + GetWidth() ||
           GetY() > element->GetY() + element->GetHeight() ||
           element->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& image) {
  if (GetX() + GetWidth() > image.GetWidth() ||
      GetY() + GetHeight() > image.GetHeight() ||
      GetX() < 0 || GetY() < 0) {
    return true;
  } else {
    return false;
  }
}

/*void GameElement::Draw(graphics::Image& image) {
  image.DrawRectangle(GetX(), GetY(), 5, 5, 0, 0, 0);*/
//}

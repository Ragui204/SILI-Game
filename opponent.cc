#include "opponent.h"

#include "game_element.h"

// Constructors.
Opponent::Opponent() : Opponent(0, 0) {}
Opponent::Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
// Member Functions.
void Opponent::Draw(graphics::Image& image) {
  graphics::Image opponent;
  opponent.Load("opponent.bmp");

  int Max_Heigth = image.GetHeight();
  int Max_Width = image.GetWidth();

  if (GetX() >= 0 && GetY() >= 0 && GetX() <= (Max_Width - GetWidth()) &&

      GetY() <= (Max_Heigth - GetHeight())) {
    for (int x = 0; x < GetWidth(); x++) {
      for (int y = 0; y < GetHeight(); y++) {
        graphics::Color color = opponent.GetColor(x, y);
        image.SetColor(GetX() + x, GetY() + y, color);
      }
    }
  }
}
void Opponent::Move(const graphics::Image& image) {
  if (!IsOutOfBounds(image)) {
     SetY(GetY() + 3);
     SetX(GetX() + 3);
  } else {
     SetIsActive(false);
  }
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  std::unique_ptr<OpponentProjectile> unique_OpponentProjectile =
      std::make_unique<OpponentProjectile>(Opponent::GetX(), Opponent::GetY());
  if (counter_ == 10) {
    counter_ = 0;
    return unique_OpponentProjectile;
  } else {
    counter_++;
    return nullptr;
  }
}



OpponentProjectile::OpponentProjectile() : OpponentProjectile(0, 0) {}
OpponentProjectile::OpponentProjectile(int x, int y)
    : GameElement(x, y, 5, 5) {}

void OpponentProjectile::Draw(graphics::Image& image) {
  graphics::Image opponent_projectile;
  opponent_projectile.Load("o_projectile.bmp");

  int Max_Heigth = image.GetHeight();
  int Max_Width = image.GetWidth();

  if (GetX() >= 0 && GetY() >= 0 && GetX() <= (Max_Width - GetWidth()) &&

      GetY() <= (Max_Heigth - GetHeight())) {
    for (int x = 0; x < GetWidth(); x++) {
      for (int y = 0; y < GetHeight(); y++) {
        graphics::Color color = opponent_projectile.GetColor(x, y);
        image.SetColor(GetX() + x, GetY() + y, color);
      }
    }
  }
}
void OpponentProjectile::Move(const graphics::Image& image) {
  if (!IsOutOfBounds(image)) {
     SetY(GetY() + 3);
    // SetX(GetX() + 3);
  } else {
    SetIsActive(false);
  }
}

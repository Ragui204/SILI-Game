#include "player.h"
#include "game_element.h"
#include "opponent.h"

void Player::Move(const graphics::Image& image) {}

Player::Player() : Player(0, 0) {}
Player::Player(int x, int y) : GameElement(x, y, 50, 50) {}

void Player::Draw(graphics::Image& image) {
  graphics::Image player;
  player.Load("player.bmp");

  int Max_Heigth = image.GetHeight();
  int Max_Width = image.GetWidth();

  if (GetX() >= 0 && GetY() >= 0 && GetX() <= (Max_Width - GetWidth()) &&

      GetY() <= (Max_Heigth - GetHeight())) {
    for (int x = 0; x < GetWidth(); x++) {
      for (int y = 0; y < GetHeight(); y++) {
        graphics::Color color = player.GetColor(x, y);
        image.SetColor(GetX() + x, GetY() + y, color);
      }
    }
  }
}

void PlayerProjectile::Move(const graphics::Image& image) {
  if (!IsOutOfBounds(image)) {
     SetY(GetY() - 3);
  } else {
    SetIsActive(false);
  }
}

PlayerProjectile::PlayerProjectile() : PlayerProjectile(0, 0) {}
PlayerProjectile::PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

void PlayerProjectile::Draw(graphics::Image& image) {
  graphics::Image player_pojectile;
  player_pojectile.Load("p_projectile.bmp");

  int Max_Heigth = image.GetHeight();
  int Max_Width = image.GetWidth();

  if (GetX() >= 0 && GetY() >= 0 && GetX() <= (Max_Width - GetWidth()) &&

      GetY() <= (Max_Heigth - GetHeight())) {
    for (int x = 0; x < GetWidth(); x++) {
      for (int y = 0; y < GetHeight(); y++) {
        graphics::Color color = player_pojectile.GetColor(x, y);
        image.SetColor(GetX() + x, GetY() + y, color);
      }
    }
  }
}

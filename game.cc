
#include "game.h"

#include <vector>

#include "cpputils/graphics/image.h"

// Constructors
Game::Game() {
  background_.Initialize(800, 600);
  score_ = 0;
  lost_game_ = false;
}

Game::Game(int width, int height) { background_.Initialize(width, height); }
// Getters
graphics::Image& Game::GetGameScreen() { return background_; }
std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() { return opponents_; }
std::vector<std::unique_ptr<OpponentProjectile>>& Game::GetOpponentProjectiles() {
  return opponent_projectiles_;
}
std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return player_projectiles_;
}
Player& Game::GetPlayer() { return player; }
int Game::GetScore() { return score_; }
bool Game::HasLost() { return lost_game_; }
// Members Functions
void Game::CreateOpponents() {
  int x_pos = 400;
  int y_pos = 100;
  std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>(x_pos, y_pos);
  opponents_.push_back(std::move(opponent));
}

void Game::Init() {
  CreateOpponents();
  player.SetX(100);
  player.SetY(100);
  background_.AddMouseEventListener(*this);
  background_.AddAnimationEventListener(*this);
}
void Game::UpdateScreen() {
  background_.DrawRectangle(0, 0, background_.GetWidth(),
                            background_.GetHeight(), 255, 255, 255);

  background_.DrawText(1, 1, "Score: " + std::to_string(score_), 25, 0, 0, 0);

  player.Draw(background_);
  for (int i = 0; i < player_projectiles_.size(); i++) {
    player_projectiles_[i]->Draw(background_);
  }
  for (int i = 0; i < opponents_.size(); i++) {
    opponents_[i]->Draw(background_);
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    opponent_projectiles_[i]->Draw(background_);
  }
  if (HasLost()) {
   background_.DrawText(240, 250, "GAME OVER\n", 100, 196, 24, 24);
 }
 }
void Game::Start() { background_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Move(background_);
    }
  }

  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Move(background_);
    }
  }

  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Move(background_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->IntersectsWith(&player) &&
        opponents_[i]->GetIsActive() && player.GetIsActive()) {
      lost_game_ = true;
      player.SetIsActive(false);
      opponents_[i]->SetIsActive(false);
    }
    for (int j = 0; j < player_projectiles_.size(); j++) {
      if (player_projectiles_[j]->IntersectsWith(opponents_[i].get()) &&
          player_projectiles_[j]->GetIsActive() &&
          opponents_[i]->GetIsActive()) {
        player_projectiles_[j]->SetIsActive(false);
        opponents_[i]->SetIsActive(false);
      }
      if (player.GetIsActive() && player_projectiles_[j]->IntersectsWith(opponents_[i].get())) {
       score_ ++;
   }
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->IntersectsWith(&player) &&
        opponent_projectiles_[i]->GetIsActive() && player.GetIsActive()) {
      opponent_projectiles_[i]->SetIsActive(false);
      player.SetIsActive(false);
      lost_game_ = true;
    }
  }
}



void Game::OnAnimationStep() {
  if (opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  background_.Flush();

}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if ((event.GetMouseAction() == graphics::MouseAction::kMoved ||
       event.GetMouseAction() == graphics::MouseAction::kDragged) &&
      (event.GetX() > 0 && event.GetX() < background_.GetWidth()) &&
      (event.GetY() > 0 && event.GetY() < background_.GetHeight())) {
    player.SetX(event.GetX() - player.GetWidth() / 2);
    player.SetY(event.GetY() - player.GetWidth() / 2);
  }
  if (event.GetMouseAction() == graphics::MouseAction::kDragged ||
      event.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> PProjectilePtr =
        std::make_unique<PlayerProjectile>(event.GetX(), event.GetY());
    player_projectiles_.push_back(std::move(PProjectilePtr));
  }

  if (HasLost() && event.GetMouseAction() == graphics::MouseAction::kPressed ) {
        Game my_game;
        my_game.Init();
        my_game.UpdateScreen();
        my_game.Start();
    }
}

 void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents_.size(); i++) {
  std::unique_ptr<OpponentProjectile> uniqueOppPtr =
      opponents_[i]->LaunchProjectile();
  if (uniqueOppPtr != nullptr) {
   opponent_projectiles_.push_back(std::move(uniqueOppPtr));
  }
}
}

void Game::RemoveInactive() {
  for (int i = opponents_.size() - 1; i >= 0; i--) {
  if (opponents_[i]->GetIsActive() == false) {
    opponents_.erase(opponents_.end() - (opponents_.size() - i));
  }
}
for (int i = opponent_projectiles_.size() - 1; i >= 0; i--) {
  if (opponent_projectiles_[i]->GetIsActive() == false) {
    opponent_projectiles_.erase(opponent_projectiles_.end() -
                                (opponent_projectiles_.size() - i));
  }
}
for (int i = player_projectiles_.size() - 1; i >= 0; i--) {
  if (player_projectiles_[i]->GetIsActive() == false) {
    player_projectiles_.erase(player_projectiles_.end() -
                              (player_projectiles_.size() - i));
  }
}
}

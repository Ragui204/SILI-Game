#ifndef GAME_H
#define GAME_H

#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
        public graphics::MouseEventListener {
 private:
  graphics::Image background_;
  std::vector<std::unique_ptr<Opponent>> opponents_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectiles_; // Pointers now.
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectiles_;
  Player player;
  int score_;
  bool lost_game_ = false;

 public:
  // Constructors
  Game();
  Game(int width, int height);
  // Getters
  graphics::Image& GetGameScreen();
  std::vector<std::unique_ptr<Opponent>>& GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles();
  Player& GetPlayer();
  int GetScore();
  bool HasLost();
  // Members Functions
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& event);
  void LaunchProjectiles();
  void RemoveInactive();
};

#endif

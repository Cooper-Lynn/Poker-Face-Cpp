//
// Created by coope on 19/11/2024.
//

#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include <AIModel.hpp>

#include "Player.hpp"
#include <vector>
#include <memory>
#include <random>
#include <array>
#include <utility>

class AIPlayer final : public Player {
private:
  double positionState;
  double handState;
  double potRatio;
  int predictedWorth;
  int evaluatedWorth;
  std::mt19937 rng;
  AIModel aiModel;

public:
  explicit AIPlayer(std::string name) ;
  ~AIPlayer() override;

  [[nodiscard]] std::string getName() const override;
  [[nodiscard]] int getChips() const override;
  void changeChips(int newChips) override;
  void incWins() override;
  [[nodiscard]] int getWins() const override;
  [[nodiscard]] std::vector<std::string> getHand() const override;
  void addCard(std::string);
  void clearHand();
  void setCurrentBet(int bet);
  void setHighestBet(int bet);
  void clearCurrentBet();
  void clearHighestBet();
  int getCurrentBet();
  int getHighestBet();
  double findHandState();
  double findPosition(std::vector<std::unique_ptr<Player>> &players);
  double findPotRatio(double pot);


};

#endif // AIPLAYER_HPP

//
// Created by coope on 19/11/2024.
//

#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "Player.hpp"
#include <vector>
#include <array>
#include <utility>

class AIPlayer final : public Player {
public:
  explicit AIPlayer(std::string name); // Constructor

  [[nodiscard]] std::string getName() const override;
  [[nodiscard]] int getChips() const override;
  void changeChips(int newChips) override;
  void incWins() override;
  [[nodiscard]] int getWins() const override;
  [[nodiscard]] std::vector<std::array<std::pair<std::string, std::string>, 2>> getHand() const override;
};

#endif // AIPLAYER_HPP

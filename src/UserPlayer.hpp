#ifndef USERPLAYER_HPP
#define USERPLAYER_HPP

#include <vector>
#include <array>
#include <utility>
#include "Player.hpp"

class UserPlayer final : public Player {
public:
    explicit UserPlayer(std::string name);

    [[nodiscard]] std::string getName() const override;
    int getChips() const override;
    void changeChips(int newChips) override;
    void incWins() override;
    [[nodiscard]] int getWins() const override;
    [[nodiscard]] std::vector<std::array<std::pair<std::string, std::string>, 2>> getHand() const override;
};

#endif //USERPLAYER_HPP
#ifndef USERPLAYER_HPP
#define USERPLAYER_HPP

#include <vector>
#include <array>
#include <utility>
#include "Player.hpp"

class UserPlayer final : public Player {
public:
    explicit UserPlayer(std::string& name);
    ~UserPlayer() override;

    [[nodiscard]] std::string getName() const override;
    int getChips() const override;
    void changeChips(int newChips) override;
    void incWins() override;
    [[nodiscard]] int getWins() const override;
    std::vector<std::string> getHand() const;
    void addCard(std::string card);
    void clearHand();
    void setCurrentBet(int bet);
    void setHighestBet(int bet);
    void clearCurrentBet();
    void clearHighestBet() override;
    int getCurrentBet() override;
    int getHighestBet() override;


};

#endif //USERPLAYER_HPP
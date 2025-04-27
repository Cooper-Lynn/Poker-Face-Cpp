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

    void setHighestPlayedBet(int bet);

    void clearCurrentBet();

    void clearHighestBet();

    void setPot(int pot);

    int getCurrentBet() override;

    int getHighestBet() override;

    int getHighestPlayedBet();

    void setCurrentPosition(int position);

    void updateCommunityHand(std::vector<std::string> &communityHand);

    double getHandStrength();

    std::vector<std::string> getValuedHand();

    std::vector<std::string> getCommunityHand();

    std::pair<double, std::vector<std::string> > tieBreaker(double matching);

    int getAction(std::vector<std::unique_ptr<Player> > &players);

    void setTag(bool folded);

    bool getTag();

    std::unique_ptr<Player> clone();

    void resetPlayer();
};

#endif //USERPLAYER_HPP
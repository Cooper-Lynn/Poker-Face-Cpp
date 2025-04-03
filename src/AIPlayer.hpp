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
    double RatioBetReserve;
    double RatioHighPot;
    double RatioHighReserve;
    int relativePosition;
    double validPot;
    double validChips;
    std::mt19937 rng;
    AIModel aiModel;

public:
    explicit AIPlayer(std::string name);

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

    void setHighestPlayedBet(int bet);

    void clearCurrentBet();

    void clearHighestBet();

    void setPot(int pot);

    int getCurrentBet();

    int getHighestBet();

    int getHighestPlayedBet();

    double findHandState();

    double findPositionState(std::vector<std::unique_ptr<Player> > &players);

    double findPotRatio();

    void setCurrentPosition(int position);

    void updateCommunityHand(std::vector<std::string> &communityHand);

    std::vector<std::string> getCommunityHand();

    std::vector<std::string> getValuedHand();

    double getHandStrength();

    std::pair<double, std::vector<std::string> > tieBreaker(double matching);

    int getAction(std::vector<std::unique_ptr<Player> > &players);

    void setTag(bool folded);

    bool getTag();

    std::unique_ptr<Player> clone();
};

#endif // AIPLAYER_HPP

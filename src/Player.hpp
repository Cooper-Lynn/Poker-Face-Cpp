//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <memory>

#include "HandReader.hpp"

class Player {
protected:
    std::string name;
    int chips = 100;
    int wins = 0;
    std::vector<std::string> playerHand;
    std::vector<std::string> communityHand;
    std::pair<double, std::vector<std::string> > evaluatedHand;
    std::vector<std::string> valuedHand;
    double handStrength;
    bool tag = false;
    int currentBet = 0;
    int highestBet = 0;
    int highestPlayedBet = 0;
    int dealerPosition;
    int currentPosition;
    int currentPot;
    HandReader handReader;

public:
    explicit Player(std::string name): name(std::move(name)), chips(100), wins(0),
                                       handReader(playerHand, communityHand) {
    };

    virtual ~Player() = default;

    virtual std::string getName() const =0;

    virtual int getChips() const =0;

    virtual void changeChips(int chipChange) = 0;

    virtual void incWins() = 0;

    virtual int getWins() const = 0;

    virtual std::vector<std::string> getHand() const =0;

    virtual void addCard(std::string) =0;

    virtual void clearHand() = 0;

    virtual void setCurrentBet(int bet) = 0;

    virtual void setHighestBet(int bet) = 0;

    virtual void setHighestPlayedBet(int bet) = 0;

    virtual void clearCurrentBet() = 0;

    virtual void clearHighestBet() =0;

    virtual void setPot(int pot) = 0;

    virtual int getCurrentBet() =0;

    virtual int getHighestBet() = 0;

    virtual int getHighestPlayedBet() = 0;

    virtual void setCurrentPosition(int position) = 0;

    virtual void updateCommunityHand(std::vector<std::string> &communityHand) = 0;

    virtual std::vector<std::string> getCommunityHand() = 0;

    virtual double getHandStrength() = 0;

    virtual std::vector<std::string> getValuedHand() = 0;

    virtual std::pair<double, std::vector<std::string> > tieBreaker(double matching) = 0;

    virtual int getAction(std::vector<std::unique_ptr<Player> > &players) = 0;

    virtual void setTag(bool folded) = 0;

    virtual bool getTag() = 0;

    virtual std::unique_ptr<Player> clone() = 0;
};


#endif //PLAYER_HPP

//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <utility>
#include <vector>
#include <array>

class Player {
    protected:
        std::string name;
        int chips = 100;
        int wins = 0;
        std::vector<std::string> playerHand;
        std::vector<std::string> communityHand;
        std:: string tag;
        int currentBet = 0;
        int highestBet = 0;
        int currentPosition;
    public:
        explicit Player(std::string name): name(std::move(name)), chips(100), wins(0){};

        virtual ~Player() =default;
        virtual std::string getName() const=0;
        virtual int getChips() const =0;
        virtual void changeChips(int chipChange) = 0;
        virtual void incWins() = 0;
        virtual int getWins() const = 0;
        virtual std::vector<std::string>getHand() const =0;
        virtual void addCard(std::string) =0;
        virtual void clearHand() = 0;
        virtual void setCurrentBet(int bet) = 0;
        virtual void clearCurrentBet()= 0;
        virtual void clearHighestBet()=0;
        virtual int getCurrentBet()=0;
        virtual int getHighestBet()= 0;
        virtual void setCurrentPosition(int position) = 0;
        virtual void updateCommunityHand(std::vector<std::string>& communityHand) = 0;

};



#endif //PLAYER_HPP

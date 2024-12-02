//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>
#include <array>

class Player {
    protected:
        std::string name;
        int chips = 100;
        int wins = 0;
        std::vector<std::string> playerHand;
    public:
        explicit Player(std::string name): name(name), chips(100), wins(0){};

        virtual ~Player() =default;
        virtual std::string getName() const=0;
        virtual int getChips() const =0;
        virtual void changeChips(int chipChange) = 0;
        virtual void incWins() = 0;
        virtual int getWins() const = 0;
        virtual std::vector<std::string>getHand() const =0;
        virtual void addCard(std::string) =0;

};



#endif //PLAYER_HPP

//
// Created by coope on 19/11/2024.
//

#ifndef USERPLAYER_HPP
#define USERPLAYER_HPP

#include <vector>

#include "Player.hpp"

class UserPlayer final :public Player{
private:
    std::string name;
    int chips;
    int wins;
    std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>> playerHand;
public:
    UserPlayer(std::string name);

    std::string getName();
    int getChips() ;
    void changeChips(int newChips);
    void incWins() ;
    int getWins();
    std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>>getHand();
};

#endif //USERPLAYER_HPP

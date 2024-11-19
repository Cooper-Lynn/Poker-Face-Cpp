//
// Created by coope on 19/11/2024.
//

#ifndef USERPLAYER_HPP
#define USERPLAYER_HPP

#include "Player.hpp"

class UserPlayer:public Player{
private:
    std::string name;
    int chips;
public:
    UserPlayer(std::string name, int chips);
    std::string getName () const ;
    int getChips() const;
    void changeChips(int newChips);
    void incWins() ;
    int getWins() const;
};

#endif //USERPLAYER_HPP

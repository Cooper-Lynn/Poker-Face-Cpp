//
// Created by coope on 12/11/2024.
//

#include "UserPlayer.hpp"

UserPlayer::UserPlayer(std::string userName): Player(userName, chips) {
    this->name = userName;
};

std::string UserPlayer:: getName() {return name;};
int UserPlayer::getChips() const {return chips;};
int UserPlayer::getWins() const  {return wins;};
void UserPlayer::incWins() {wins++;};

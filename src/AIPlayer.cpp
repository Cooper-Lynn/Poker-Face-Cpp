//
// Created by coope on 12/11/2024.
//
#include "AIPlayer.hpp"
AIPlayer::AIPlayer(std::string userName,): Player(userName, chips) {
    this<-name = userName;
};

std::string AIPlayer::getName() {return name;};
int AIPlayer::getChips() {return chips;};
int AIPlayer::getWins()  {return wins;};
void AIPlayer::incWins() {wins++;};
;
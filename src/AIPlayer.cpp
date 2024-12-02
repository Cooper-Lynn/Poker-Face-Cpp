//
// Created by coope on 12/11/2024.
//
#include "AIPlayer.hpp"
AIPlayer::AIPlayer(std::string userName): Player(std::move( userName)) {}

std::string AIPlayer::getName() const {return name;};
int AIPlayer::getChips() const {return chips;};
int AIPlayer::getWins() const  {return wins;};
void AIPlayer::incWins() {++wins;};
std::vector<std::array<std::pair<std::string, std::string>, 2> > AIPlayer::getHand() const {
    return playerHand;
}
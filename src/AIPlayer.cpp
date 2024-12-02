//
// Created by coope on 12/11/2024.
//
#include "AIPlayer.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <array>

AIPlayer::AIPlayer(std::string userName): Player(std::move( userName)) {}
AIPlayer::~AIPlayer() = default;


std::string AIPlayer::getName() const {return name;};
int AIPlayer::getChips() const {return chips;};
int AIPlayer::getWins() const  {return wins;};
void AIPlayer::changeChips(int newChips) {chips = newChips;}
void AIPlayer::incWins() {++wins;};
std::vector<std::array<std::pair<std::string, std::string>, 2> > AIPlayer::getHand() const {
    return playerHand;
}
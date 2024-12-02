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
std::vector<std::string> AIPlayer::getHand() const {
    return playerHand;
}
void AIPlayer::addCard(std::string card)  {
    playerHand.push_back(card);
}


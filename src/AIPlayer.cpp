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

void AIPlayer::clearHand() {
    playerHand.clear();
}

void AIPlayer::setCurrentBet(int bet) {
    currentBet += bet;
}

void AIPlayer::setHighestBet(int bet) {
    highestBet = bet;
}

void AIPlayer::clearCurrentBet() {
    currentBet = 0;
}

void AIPlayer::clearHighestBet() {
    highestBet=0;
}

int AIPlayer::getHighestBet() {
    return highestBet;
}

int AIPlayer::getCurrentBet() {
    return currentBet;
}

void Player::setCurrentPosition(int position) {
    currentPosition = position;
}


double AIPlayer::findPosition(std::vector<std::unique_ptr<Player>> &players) {
    positionState = currentPosition/players.size();
    return positionState;
}

double AIPlayer::findHandState() {

}

void Player::updateCommunityHand(std::vector<std::string>& communityHand) {
    this->communityHand = communityHand;
}











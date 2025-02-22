//
// Created by coope on 12/11/2024.
//
#include "AIPlayer.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <array>

AIPlayer::AIPlayer(std::string userName): Player(std::move(userName)), aiModel(0.01, 0.95, 0.1) {
}

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
    ;
}

double AIPlayer::findHandState() {
    handReader.updateHands(playerHand, communityHand);
    evaluatedHand  = handReader.valueHand();
    evaluatedWorth = evaluatedHand.first;
    predictedWorth = handReader.predictWorth();


    if (predictedWorth > evaluatedWorth) {
        return predictedWorth/10;
    }
    return evaluatedWorth/10;




}

double AIPlayer::findPotRatio(double pot) {
    getChips();

}


void Player::updateCommunityHand(std::vector<std::string>& communityHand) {
    this->communityHand = communityHand;
}

std::vector<std::string> Player::getCommunityHand() {
    return communityHand;
}

void Player::setHighestBet(int bet) {
    highestBet = bet;
}

void Player::setHighestPlayedBet(int bet) {
    highestPlayedBet = bet;
}


int Player::getHighestPlayedBet() {
    return highestPlayedBet;
}

void Player::setPot(int pot) {
    currentPot = pot;
}











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


double AIPlayer::findPositionState(std::vector<std::unique_ptr<Player>> &players) {
    relativePosition = (currentPosition - dealerPosition + players.size() ) % players.size();

    return static_cast<double>(relativePosition) / players.size();
}

double AIPlayer::findHandState() {
    handReader.updateHands(playerHand, communityHand);
    evaluatedHand  = handReader.valueHand();
    evaluatedWorth = evaluatedHand.first;
    predictedWorth = handReader.predictWorth();


    if (predictedWorth > evaluatedWorth) {
        return static_cast<double>(predictedWorth)/10;
    }
    return static_cast<double>(evaluatedWorth)/10;

}

double AIPlayer::findPotRatio() {
    RatioBetReserve = 0;
    RatioHighPot = 0;
    RatioHighReserve = 0;

    //used as validation to prevent division by 0
    validChips = std::max(getChips(), 1);
    validPot = std::max(currentPot, 1);

    RatioBetReserve = 1-(static_cast<double>(currentBet)/validChips);
    RatioHighPot = 1-(static_cast<double>(highestPlayedBet)/validPot);
    RatioHighReserve = 1-(static_cast<double>(highestPlayedBet)/validChips);

    return (0.5*RatioBetReserve)+(0.3*RatioHighPot)+(0.2*RatioHighReserve);

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











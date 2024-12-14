//
// Created by coope on 12/11/2024.
//

#include "UserPlayer.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <array>



// Constructor: Pass userName to the base class constructor
UserPlayer::UserPlayer(std::string& userName) : Player(std::move(userName)) {}
UserPlayer::~UserPlayer() = default;


// Accessor methods
std::string UserPlayer::getName() const {
    return name; // name is inherited from the base class
}

int UserPlayer::getChips() const {
    return chips; // chips is inherited from the base class
}

int UserPlayer::getWins() const {
    return wins; // wins is inherited from the base class
}

// Mutator methods
void UserPlayer::incWins() {
    ++wins; // Increment wins
}

void UserPlayer::changeChips(int chipChange) {
    chips += chipChange; // Modify chip count
}

// Return the player's hand
std::vector<std::string> UserPlayer::getHand() const {
    return playerHand;
}

void UserPlayer::addCard(std::string card) {

    playerHand.push_back(card);

}

void UserPlayer::clearHand() {
    playerHand.clear();
}

void UserPlayer::setCurrentBet(int bet) {
    currentBet = bet;
}


void UserPlayer::clearCurrentBet() {
    currentBet = 0;
}



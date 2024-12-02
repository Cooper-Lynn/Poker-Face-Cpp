//
// Created by coope on 12/11/2024.
//

#include "UserPlayer.hpp"

// Constructor: Pass userName to the base class constructor
UserPlayer::UserPlayer(std::string userName) : Player(std::move(userName)) {}

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
std::vector<std::array<std::pair<std::string, std::string>, 2>> UserPlayer::getHand() const {
    return playerHand;
}
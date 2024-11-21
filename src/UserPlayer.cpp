//
// Created by coope on 12/11/2024.
//

#include "UserPlayer.hpp"

UserPlayer::UserPlayer(std::string userName): Player(userName) {
    this->name = userName;
};

std::string UserPlayer:: getName() {return name;};
int UserPlayer::getChips() {return chips;};
int UserPlayer::getWins() {return wins;};
void UserPlayer::incWins() {wins++;};
void UserPlayer::changeChips(int chipChange) {
    this->chips += chipChange;
}
std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>> UserPlayer::getHand() {
    return playerHand;
}
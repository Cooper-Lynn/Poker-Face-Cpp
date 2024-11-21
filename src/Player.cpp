//
// Created by cooper on 12/11/2024.
//

#include "Player.hpp"

Player::Player(std::string name){};

std::string Player::getName() {return name;} ;
int Player::getChips() {return chips;};
int Player::getWins()  {return wins;};
void Player::changeChips(int chipChange) {
    this->chips += chipChange;
}
std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>> Player::getHand() {
    return playerHand;
}


void Player::incWins() {wins++;};


//
// Created by cooper on 12/11/2024.
//

#include "Player.hpp"

Player::Player(std::string name,int chips):name(name),chips(chips),wins (0) {};

std::string Player::getName() {return name;};
int Player::getChips() const {return chips;};
int Player::getWins()  {return wins;};
void Player::incWins() {wins++;};


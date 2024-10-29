#include "Headers/Cards.hpp"

Cards::Cards(char suit, char num) {
	this->suit = suit;
	this->num = num;
}

char Cards::getSuit() {
	return this->suit;
}

char Cards::getNum() {
	return this->num;
}

char Cards::getCard() {
	return this->suit, this->num;
}
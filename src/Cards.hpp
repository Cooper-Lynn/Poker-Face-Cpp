#pragma once
#ifndef _CARDS_HPP_
#define _CARDS_HPP_


class Cards {
private:
	char suit;
	char num;
public:
	Cards(char suit, char num);
	char getSuit();
	char getNum();
	char getCard();
};
#endif // _CARDS_HPP_
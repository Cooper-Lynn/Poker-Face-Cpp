#pragma once
#ifndef _CARDS_HPP_
#define _CARDS_HPP_


class Cards {
private:
	char suit;
	char num;
public:
	Cards(char suit, char num);
	getSuit();
	getNum();
};
#endif // !CARDS.HPP
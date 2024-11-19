//
// Created by coope on 19/11/2024.
//

#ifndef USERPLAYER_HPP
#define USERPLAYER_HPP
#include "Player.hpp"

class UserPlayer:public Player{
	private:
		std::string name;
        int chips;
	public:
        Userplayer(std::string name, int chips);
        std::string getName() override;
        int getChips() override;
        void setChips(int chips);
  }
;

#endif //USERPLAYER_HPP

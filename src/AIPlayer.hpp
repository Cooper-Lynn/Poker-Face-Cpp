//
// Created by coope on 19/11/2024.
//

#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP
#include "Player.hpp"

class AIPlayer:public Player{
  private:
    std::string name;
    int chips;
  public:
    AIPlayer(std::string name, int chips);
    std::string getName () const ;
    int getChips() const;
    void changeChips(int newChips);
    void incWins() ;
    int getWins() const;
};



#endif //AIPLAYER_HPP

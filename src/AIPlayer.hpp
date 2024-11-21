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
    int wins;
    std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>> playerHand;
  public:
    AIPlayer(std::string name);
    std::string getName ();
    int getChips() ;
    void changeChips(int newChips);
    void incWins() ;
    int getWins() ;
  std::pmr::vector<std::array<std::pair<std::string, std::string>, 2>> getHand();
};



#endif //AIPLAYER_HPP

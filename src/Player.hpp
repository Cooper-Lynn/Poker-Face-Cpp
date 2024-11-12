//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP



class Player {
    private:
      std::string name;
      int chips;
      int wins;
    public:
      std::string getName();
      int getChips();
      int changeChips();
      int incWins();
      int getWins();

};



#endif //PLAYER_HPP

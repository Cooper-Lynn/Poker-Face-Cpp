//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP



class Player {
    private:
        std::string name;
        int chips = 100;
        int wins = 0;
        std::vector<std::array<std::pair<std::string, std::string>,2>> playerHand;
    public:
        Player(std::string name, int chips);
        virtual ~Player() = default;
        virtual std::string getName();
        virtual int getChips() ;
        virtual void changeChips();
        virtual void incWins();
        virtual int getWins();
        virtual std::vector<std::array<std::pair<std::string, std::string>,2>> getHand();

};



#endif //PLAYER_HPP

//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP



class Player {
    protected:
        std::string name;
        int chips = 100;
        int wins = 0;
        std::vector<std::array<std::pair<std::string, std::string>, 2>> playerHand;
    public:
        explicit Player(std::string name);

        virtual ~Player() =0;
        virtual std::string getName() const=0;
        virtual int getChips() const =0;
        virtual void changeChips(int chipChange) = 0;
        virtual void incWins() = 0;
        virtual int getWins() const = 0;
        virtual std::vector<std::array<std::pair<std::string, std::string>, 2>>getHand() const =0;
};



#endif //PLAYER_HPP

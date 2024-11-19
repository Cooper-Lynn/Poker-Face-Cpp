//
// Created by coope on 12/11/2024.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP



class Player {
    private:
        std::string name;
        int chips = 0;
        int wins = 0;
    public:
        Player(std::string name, int chips);
        virtual ~Player() = default;
        virtual std::string getName();
        virtual int getChips() const;
        virtual void changeChips();
        virtual void incWins();
        virtual int getWins() const
    ;

};



#endif //PLAYER_HPP

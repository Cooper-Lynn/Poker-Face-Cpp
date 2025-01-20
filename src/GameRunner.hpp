//
// Created by coope on 20/01/2025.
//

#ifndef GAMERUNNER_HPP
#define GAMERUNNER_HPP

class GameRunner {
private:

    int dealerPosition;
    int highestBet;
    std::vector<std::string> communityCards;
    std::vector<std::string> allCards;
    std::vector<std::unique_ptr<Player>> players;

public:
    GameRunner(int dealerPosition, int highestBet);
    default ~GameRunner();


};

#endif //GAMERUNNER_HPP

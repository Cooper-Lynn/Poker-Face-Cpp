//
// Created by coope on 20/01/2025.
//

#ifndef GAMERUNNER_HPP
#define GAMERUNNER_HPP
#include <memory>
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

class GameRunner {
private:

    int dealerPosition;
    int highestBet;
    int chipPot;
    std::vector<std::string> communityCards;
    std::vector<std::string> allCards;
    std::vector<std::unique_ptr<Player>> players;

public:
    GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player>> &players, std::vector<std::string> &allCards);
    ~GameRunner();
    void sortBlinds();
    void round1();
    void round2();
    void round3();
    void round4();
    int getDealerPosition();
    int getHighestBet();
    std::vector<std::string> getCommunityCards();
    std::vector<std::string> getAllCards();
    int getWinnerPos();
    std::string checkOrCall();
    std::vector<std::string> handDetail(std::vector<std::string>& hand);
    std::pair<std::string, std::string> cardDetail(std::string& card);
    std::vector<std::string> giveHands(std::vector<std::string> &deck, int numOfPlayers);
    std::string dealCard(std::vector<std::string> &deck);
    std::vector<std::string> createDeck(std::vector<std::string> &suits, std::vector<std::string> &ranks);


};

#endif //GAMERUNNER_HPP

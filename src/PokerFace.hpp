//
// Created by coope on 19/03/2025.
//

#ifndef POKERFACE_HPP
#define POKERFACE_HPP

#include <iostream>
#include <MainGui.hpp>
#include <MainGui.hpp>
#include <vector>
#include <string>
#include <QObject>
#include <memory>
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include "GameRunner.hpp"
#include "MainGui.hpp"

class PokerFace{


private:
    std::vector<std::string> suits = {"s", "h", "d", "c"};
    std::vector<std::string> ranks = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    };



public:
    PokerFace();
    void gameStarted(std::vector<std::string> userInputSetup);
    std::vector<std::string> createDeck(std::vector<std::string>& suits, std::vector<std::string>& ranks);
    std::string dealCard(std::vector<std::string>& deck);
    std::vector<std::string> giveHands(std::vector<std::string>& deck, int numOfPlayers);
    std::pair<std::string, std::string> cardDetail(std::string& card);
    std::vector<std::string> handDetail(std::vector<std::string>& hand);
    std::string checkOrCall(int maxBet);
    void passGameRunner(GameRunner &gameRunner);


};
#endif // POKERFACE_HPP //POKERFACE_HPP

//
// Created by coope on 20/01/2025.
//

#ifndef GAMERUNNER_HPP
#define GAMERUNNER_HPP
#include <memory>
#include <random>
#include "Player.hpp"
#include <QObject>

#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

class GameRunner : public QObject {
    Q_OBJECT
private:
    bool roundFinished;
    int dealerPosition;
    int highestBet;
    int chipPot;
    int chipInput;
    int playerRoundChoice;
    int roundCounter=1;
    int tieInboundCounter;
    int officialTieRank;
    int temporaryTieRank;
    double highestStrength;
    double tempStrength;
    double tieStrength;
    double tieBreaker;
    bool tieBroken;
    bool officialTie;



    std::string officialTieRankString;
    std::string tempLeaderName;
    std::string cresult;

    std::vector<std::string> communityCards;
    std::vector<std::unique_ptr<Player> > players;
    std::vector<std::string> currentDeck;
    std::vector<std::string> handsToGive;
    std::vector<std::string> handToShow;
    std::vector<std::string> hand;
    std::vector<std::string> playerTies;
    std::vector<std::string> suits = {"s", "h", "d", "c"};
    std::vector<std::string> ranks = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    };



public:
    GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player> > &players,
               std::vector<std::string> &currentDeck);

    ~GameRunner();

    bool bettingCycle();

    void sortBlinds();

    void round1();

    void midRounds();

    void finalRound();

    std::vector<std::unique_ptr<Player> > getPlayers();

    void setUserInput(int action, int chips);

    int getDealerPosition();

    int getHighestBet();

    int getChipPot();

    std::vector<std::string> getCommunityCards();

    std::vector<std::string> getCurrentDeck();

    int getWinnerPos();

    std::string checkOrCall(int bet);

    std::vector<std::string> handDetail(std::vector<std::string> &hand);

    void giveHandsToPlayers();

    void setCurrentDeck(std::vector<std::string> &newDeck);

    std::pair<std::string, std::string> cardDetail(std::string &card);

    std::vector<std::string> giveHands(std::vector<std::string> &deck, int numOfPlayers);

    std::string dealCard(std::vector<std::string> &deck);

    std::vector<std::string> createDeck();

    std::unique_ptr<Player> findPlayer(std::string name);

    void setUserInput();

    signals:
    void userInputRequired();
    void userInputProcessed();
    void updateGUIHidden();
    void updateGUIUnhidden();
    void updateActionMessage(std::string actionMessage);



};

#endif //GAMERUNNER_HPP

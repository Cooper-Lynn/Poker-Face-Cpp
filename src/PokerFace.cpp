// Poker Face.cpp
#include <iostream>
#include <QtPlugin>
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include "GameRunner.hpp"
#include "MainGui.hpp"
#include "PokerFace.hpp"
#include <vector>
#include <array>
#include <random>
#include <utility>
#include <memory>
#include <QObject>


PokerFace::PokerFace() {
    ;
}


/*
 *Function to create a deck of cards to be used in the game
 *@param suits is the suits in the deck, ranks is the ranks in the deck
 *@return the complete deck
 */
std::vector<std::string> PokerFace::createDeck(std::vector<std::string> &suits, std::vector<std::string> &ranks) {
    std::vector<std::string> deck;
    for (const auto &suit: suits) {
        for (const auto &rank: ranks) {
            deck.push_back(suit + rank);
        }
    }
    return deck;
}

/*
 *Function to pick a random card from the deck
 *@param, reference to the deck
 *@
 */

std::string PokerFace::dealCard(std::vector<std::string> &deck) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, deck.size() - 1);
    int randomIndex = distrib(gen);
    std::string card = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex);
    return card;
}

std::vector<std::string>
PokerFace::giveHands(std::vector<std::string> &deck, int numOfPlayers) {
    std::vector<std::string> handsToGive;
    for (int i = 0; i < numOfPlayers * 2; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, deck.size() - 1);
        int randomIndex = distrib(gen);
        handsToGive.push_back(deck[randomIndex]);
        deck.erase(deck.begin() + randomIndex);
    }
    return handsToGive;
}

std::pair<std::string, std::string> PokerFace::cardDetail(std::string &card) {
    std::string first;
    std::string second;
    if (card.at(0) == 's') {
        first = "Spades";
    } else if (card.at(0) == 'd') {
        first = "Diamonds";
    } else if (card.at(0) == 'h') {
        first = "Hearts";
    } else if (card.at(0) == 'c') {
        first = "Clubs";
    }

    std::string number = card.substr(1);
    if (number == "1" || number == "14") {
        second = "Ace";
    } else if (number == "11") {
        second = "Jack";
    } else if (number == "12") {
        second = "Queen";
    } else if (number == "13") {
        second = "King";
    } else {
        second = number;
    }

    return {first, second};
}

std::vector<std::string> PokerFace::handDetail(std::vector<std::string> &hand) {
    std::vector<std::string> handToShow;
    for (auto &card: hand) {
        auto [Suite, Rank] = cardDetail(card);
        std::string cardToAddToHand = Rank + " of " + Suite + "\n";
        handToShow.push_back(cardToAddToHand);
    }
    return handToShow;
}

std::string PokerFace::checkOrCall(int maxBet) {
    if (!maxBet) return "Check";
    return "Call";
}

void PokerFace::gameStarted(std::vector<std::string> userInputSetup, MainGui *gui) {
    std::vector<std::string> suits = {"s", "h", "d", "c"}; // spades, hearts, diamonds, clubs
    std::vector<std::string> ranks = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    }; // Ace to King
    // Create the deck
    std::vector<std::string> deck = createDeck(suits, ranks);
    std::vector<std::string> riverCards;
    std::vector<std::string> aiNames = {"Bert", "Ruben", "Chanel", "Dimitri", "Gary", "Steve", "Tegan", "Kian", "Sam", "Bea", "Olivia"};
    std::vector<std::string> handToShow;
    std::vector<std::string> hand;
    std::vector<std::unique_ptr< Player> > players;
    std::vector<std::string> handsToGive;
    std::string playerName;


    int dealerPosition = 0;
    int maxBet = 0;
    int playerRoundChoice;
    int chipInput;
    int chipPot = 0;
    int round;
    int numPlayer;

    mainGui = gui;


    playerName = userInputSetup[0];


    numPlayer = std::stoi(userInputSetup[1]);

    std::cout << "Within PokerFace.cpp" << std::endl;
    std::cout << "Player Name: " << playerName << std::endl;
    std::cout << "Number of Players: " << numPlayer << std::endl;

    players.push_back(std::make_unique<UserPlayer>(playerName));
    for (auto i = 0; i < numPlayer; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, aiNames.size() - 1);
        int randomIndex = distrib(gen);
        players.push_back(std::make_unique<AIPlayer>(aiNames[randomIndex]));
        aiNames.erase(aiNames.begin() + randomIndex);
    }


    /*
     *This Section lists out all the players in the game
     */

    for (auto &player: players) {
        std::cout << "Player: ";
        std::cout << player->getName() << "\n";
    }
    dealerPosition = 1;
    while (true) {
        std::unique_ptr<GameRunner> gameRunner = std::make_unique<GameRunner>(dealerPosition, players, deck);
        gameRunner->giveHandsToPlayers();
        passGameRunner(gameRunner);
        gameRunner->round1();
        gameRunner->midRounds();
        gameRunner->midRounds();
        gameRunner->finalRound();
        players.clear();
        players = std::move( gameRunner->getPlayers());
        dealerPosition ++;
        dealerPosition = dealerPosition++ % players.size();
        deck = createDeck(suits, ranks);

        for (auto &player: players) {
            if (player->getChips() < 500 ) {
                player->resetPlayer();
                player->changeChips(-player->getChips());
                player->changeChips(500);
            }
            else {
                player->resetPlayer();
            }

        }

        gameRunner.reset();
    }
}


void PokerFace::passGameRunner(std::unique_ptr<GameRunner> &gameRunner) {

    mainGui->setGameRunnerPointer(gameRunner.get());
}


int main(int argc, char *argv[]) {
    std::cout<<"at least getting here";
    PokerFace poker_face;

    //Uncomment for training
    //AIModel model(0.12, 0.94, 0.9);
    //model.quickTrain(100000);


    MainGui gui(argc, argv, poker_face);
    return 0;
}

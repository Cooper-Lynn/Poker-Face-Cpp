//
// Created by coope on 20/01/2025.
//
#include "GameRunner.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <qeventloop.h>
#include <QMessageBox>

#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

GameRunner::GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player> > &players,
                       std::vector<std::string> &currentDeck) {
    this->dealerPosition = dealerPosition;
    this->players = std::move(players);
    this->currentDeck = std::move(currentDeck);
    highestBet = 0;
    chipPot = 0;

}

GameRunner::~GameRunner() {
};

void GameRunner::sortBlinds() {
    int numPlayers = players.size();

    if (numPlayers < 2) return;

    chipPot += 15;
    if (numPlayers == 2) {
        players[dealerPosition]->changeChips(-5);
        players[(dealerPosition + 1) % numPlayers]->changeChips(-10);
    } else {
        int smallBlindPos = (dealerPosition + 1) % numPlayers;
        int bigBlindPos = (dealerPosition + 2) % numPlayers;

        players[smallBlindPos]->changeChips(-5);
        players[bigBlindPos]->changeChips(-10);
    }


    dealerPosition = (dealerPosition + 1) % numPlayers;
}

std::vector<std::string> GameRunner::handDetail(std::vector<std::string> &hand) {
    std::vector<std::string> handToShow;
    for (auto &card: hand) {
        auto [Suite, Rank] = cardDetail(card);
        std::string cardToAddToHand = Rank + " of " + Suite + "\n";
        handToShow.push_back(cardToAddToHand);
    }
    return handToShow;
}

void GameRunner::giveHandsToPlayers() {
    handsToGive = giveHands(currentDeck, players.size());
    for (auto &player: players) {
        for (int i = 0; i < 2; ++i) {
            if (!handsToGive.empty()) {
                // Add the first card to the player's hand
                player->addCard(handsToGive.front());
                // Remove the card from the deck
                handsToGive.erase(handsToGive.begin());
            } else {
                std::cerr << "Error: Not enough cards to distribute." << std::endl;
                break;
            }
        }
    }
}

std::pair<std::string, std::string> GameRunner::cardDetail(std::string &card) {
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

std::vector<std::string> GameRunner::giveHands(std::vector<std::string> &deck, int numOfPlayers) {
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

std::string GameRunner::dealCard(std::vector<std::string> &deck) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, deck.size() - 1);
    int randomIndex = distrib(gen);
    std::string card = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex);
    return card;
}

std::vector<std::string> GameRunner::createDeck() {
    std::vector<std::string> deck;
    for (const auto &suit: suits) {
        for (const auto &rank: ranks) {
            deck.push_back(suit + rank);
        }
    }
    return deck;
}

void GameRunner::setCurrentDeck(std::vector<std::string> &newDeck) {
    currentDeck = newDeck;
}


std::string GameRunner::checkOrCall() {
    if (!highestBet) return "Check";
    return "Call";
}

int GameRunner::getDealerPosition() {
    return dealerPosition;
}

int GameRunner::getHighestBet() {
    return highestBet;
}

std::vector<std::string> GameRunner::getCurrentDeck() {
    return currentDeck;
}

std::vector<std::string> GameRunner::getCommunityCards() {
    return communityCards;
}

bool GameRunner::bettingCycle() {
    for (int count = 0, i = (dealerPosition + 1) % players.size(); count < players.size();
         count++, i = (i + 1) % players.size()) {
        std::cout<<players.size()<<std::endl;
        if (dynamic_cast<UserPlayer *>(players[i].get()) && players[i]->getChips() != 0 && players[i]->getTag() ==
            false) {
            std::cout<<"USER INPUT";
            emit userInputRequired();
            //QEventLoop loop;



            //loop.exec();
        } else if (players[i]->getTag() == false) {
            std::cout << "Error: before player action." << std::endl;
            int action = players[i]->getAction(players);
            std::cout<<"ACTION: "<<action<<std::endl;
            switch (action) {
                case 0:
                    chipInput = highestBet - players[i]->getCurrentBet();
                    if (chipInput >= players[i]->getChips()) {

                        break;
                    }
                    chipPot += chipInput;
                    players[i]->changeChips(chipInput);
                    players[i]->setCurrentBet(chipInput);
                    break;
                case 1:
                    if (rand() % 100 < 10) {
                        chipInput = players[i]->getChips() * 0.05;
                    } else {
                        auto mult = players[i]->getHandStrength();
                        chipInput = players[i]->getChips() * mult;
                    }
                    break;
                case 2:
                    players[i]->setTag(true);
                    chipInput = 0;
                    break;
                default:
                    players[i]->setTag(true);

                    chipInput = 0;
                    break;
            }
            chipPot += chipInput;
            players[i]->changeChips(-chipInput);
            if (chipInput > highestBet) {
                highestBet = chipInput;
            }

            std::cout << chipPot<<" poopbutt but without butt\n";
        }
    }

    for (auto &player: players) {
        player->setPot(chipPot);
        player->setHighestPlayedBet(highestBet);
        roundFinished = true;
        if (player->getHighestBet() != highestBet) {
            //roundFinished = false;
        }
    }

    return roundFinished;
}


void GameRunner::round1() {
    hand = players[0]->getHand();
    handToShow = handDetail(hand);
    for (auto &cards: handToShow) {
        std::cout << cards << std::endl;
    }
    this->sortBlinds();

    for (int i = 0; i < players.size(); i++) {
        players[i]->setCurrentPosition((i - dealerPosition + players.size()) % players.size());
    }

        while (!roundFinished) {
            roundFinished = false;
            bettingCycle();
        }

    for (int i = 0; i < 3; i++) {
        std::string tempCard = dealCard(currentDeck);
        communityCards.push_back(tempCard);
    }
    std::cout << "End of Round 1\n";
    std::cout << chipPot;
    handToShow = handDetail(communityCards);

    for (auto &card: handToShow) {
        std::cout << card;
    }
}

void GameRunner::midRounds() {
    roundFinished = false;

    while (!roundFinished) {
        bettingCycle();
    }

    std::cout << "End of Round 2\n";
    std::cout << chipPot;
    handToShow = handDetail(communityCards);
    std::cout << "\nCommunity Cards: " << std::endl;

    for (auto &card: handToShow) {
        std::cout << card;
    }
}

void GameRunner::finalRound() {
    roundFinished = false;

    while (!roundFinished) {
        bettingCycle();
    }


    highestStrength = 0;

    for (auto &player: players) {
        std::vector<std::string> theHand = player->getHand();
        handToShow = handDetail(theHand);
        std::cout << "Player Name: " << player->getName() << std::endl;
        std::cout << "Hand: ";
        for (auto &card: handToShow) {
            std::cout << card;
        }
    }

    tempLeaderName = "";
    tieStrength = 0;

    for (auto &player: players) {
        tempStrength = player->getHandStrength();
        if (tempStrength > highestStrength && tempStrength > tieStrength) {
            tempLeaderName = player->getName();
            tieStrength = 0;
            playerTies.clear();
        }
        if (tempStrength == highestStrength) {
            playerTies.push_back(std::move(player));
            tieStrength = tempStrength;
        }
    }

    tieBreaker = 0;
    tieBroken = false;
    while (!tieBroken) {
        if (playerTies.size() != 0) {
            for (auto &player: playerTies) {
                auto result = player->tieBreaker(tieStrength);
                if (result.first > tieBreaker) {
                    tieBreaker = result.first;
                    tempLeaderName = player->getName();
                    tieStrength = 0;
                    tieBroken = true;
                }
                if (result.first == tieBreaker && tieBreaker != 0) {
                    tieStrength = result.first;
                    tieBroken = false;
                } else {
                    auto tieBrokePlayer = std::find_if(playerTies.begin(), playerTies.end(),
                                                       [&player](std::unique_ptr<Player> &playerToRemove) {
                                                           return playerToRemove->getName() == player->getName(); //
                                                       });

                    if (tieBrokePlayer != playerTies.end()) {
                        playerTies.erase(tieBrokePlayer);
                    }
                }
            }
        }
    }

    handToShow = handDetail(communityCards);
    std::cout << "\nCommunity Cards: " << std::endl;

    for (auto &card: handToShow) {
        std::cout << card;
    }
}

std::vector<std::unique_ptr<Player> > GameRunner::getPlayers() {
    std::vector<std::unique_ptr<Player> > tempPlayers;
    tempPlayers.reserve(players.size());
    for (const auto &p: players) {
        tempPlayers.push_back(p->clone());
    }
    return std::move(tempPlayers);
}

void GameRunner::setUserInput(int action, int chips) {
    for (int count = 0, i = (dealerPosition + 1) % players.size(); count < players.size();
         count++, i = (i + 1) % players.size()) {
        if (dynamic_cast<UserPlayer *>(players[i].get()) && players[i]->getChips() != 0 && players[i]->getTag() ==
            false) {
            switch (action) {
                case 0:
                    chips = highestBet - players[i]->getCurrentBet();
                    if (chips >= players[i]->getChips()) {
                        std::cout << "Incorrect amount of chips available";
                        break;
                    }
                    chipPot += chips;
                    players[i]->changeChips(chips);
                    players[i]->setCurrentBet(chips);
                    break;
                case 1:
                    if (chips >= players[i]->getChips()) {
                        std::cout << "Incorrect amount of chips available";
                        break;
                    }
                    chipPot += chips;
                    players[i]->changeChips(-chips);
                    players[i]->setCurrentBet(chips);
                    if (chips > players[i]->getHighestBet()) {
                        players[i]->setHighestBet(chips);
                    }
                    break;
                case 2:
                    players[i]->setTag(true);
                    break;
                default:
                    break;
            }
        }
    }
    //emit userInputProcessed();
}

void GameRunner::setGameBaseView() {
    //GameBaseView *gameBaseView) {
    //this->gameBaseView= gameBaseView;
}

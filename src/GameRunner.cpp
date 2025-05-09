//
// Created by coope on 20/01/2025.
//
#include "GameRunner.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <qcoreapplication.h>
#include <qeventloop.h>
#include <QObject>
#include <thread>

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
        players[smallBlindPos]->setCurrentBet(5);
        players[smallBlindPos]->setHighestBet(5);

        players[bigBlindPos]->changeChips(-10);
        players[bigBlindPos]->setCurrentBet(10);
        players[bigBlindPos]->setHighestBet(10);
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


std::string GameRunner::checkOrCall(int currentbet) {
    std::cout << currentbet<<std::endl;
    std::cout << highestBet<<std::endl;
    if (highestBet == currentbet) return "Check";
    return "Call";
}

int GameRunner::getDealerPosition() {
    return dealerPosition;
}

int GameRunner::getChipPot() {
    return chipPot;
}


int GameRunner::getHighestBet() {
    return highestBet;
}

std::vector<std::string> GameRunner::getCurrentDeck() {
    std::vector<std::string> deck;
    deck = currentDeck;
    return deck;
}

std::vector<std::string> GameRunner::getCommunityCards() {
    std::vector<std::string> community;
    community = communityCards;
    return community;
}

bool GameRunner::bettingCycle() {
    for (int count = 0, i = (dealerPosition + 2) % players.size(); count < players.size();
        count++, i = (i + 1) % players.size()) {
        emit updateGUIHidden();
        QCoreApplication::processEvents();
        QElapsedTimer timer;
        timer.start();

        while (timer.elapsed() < 2000) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        if (dynamic_cast<UserPlayer *>(players[i].get()) && players[i]->getChips() != 0 && players[i]->getTag() ==
            false) {
            emit userInputRequired();
            QEventLoop loop;
            auto conn = connect(this, &GameRunner::userInputProcessed, &loop, &QEventLoop::quit, Qt::UniqueConnection);
            loop.exec();
        }

        else if (players[i]->getTag() == false) {
            int action = players[i]->getAction(players);
            std::cout << "ACTION: " << action << std::endl;
            std::cout << "PLAYER NAME:" <<players[i]->getName() << std::endl;
            switch (action) {

                case 1:

                    std::cout<<players[i]->getName()<<" "<<players[i]->getChips();
                    if (rand() % 100 < 10) {
                        chipInput = (highestBet-players[i]->getCurrentBet())+players[i]->getChips() * 0.05;
                    } else {
                        auto mult = players[i]->getHandStrength()/25;
                        chipInput = (highestBet-players[i]->getCurrentBet())+players[i]->getChips() * mult;
                    }

                    if (chipInput >= players[i]->getChips()) {
                        chipInput = players[i]->getChips();
                    }

                    break;


                case 0:
                    cresult = checkOrCall(players[i]->getChips());
                    if (cresult == "Call") {
                        chipInput = highestBet - players[i]->getCurrentBet();
                        if (chipInput >= players[i]->getChips()) {
                            chipInput = players[i]->getChips();
                            break;
                        }
                        break;
                    }
                    else {
                        chipInput = 0;
                        break;
                    }


                case 2:
                    players[i]->setTag(true);
                    chipInput = 0;
                    break;

                default:
                    players[i]->setTag(true);
                    chipInput = 0;
                    break;
            }

            std::cout<<"Highest Bet "<< highestBet<<std::endl;
            std::cout<<players[i]->getName()<<" "<<players[i]->getChips() << std::endl;
            std::cout<<"Chip Input "<< chipInput<<std::endl;
            chipPot += chipInput;
            players[i]->changeChips(-chipInput);
            players[i]->setCurrentBet(chipInput);
            if (players[i]->getCurrentBet() > highestBet) {
                highestBet += players[i]->getCurrentBet()-highestBet;
            }
            std::string actionMessage;
            if(action == 0) {
                actionMessage+=players[i]->getName()+" has "+ cresult+"ed";
            }
            else if(action == 1) {
                actionMessage+=players[i]->getName()+" has raised b: "+std::to_string(chipInput);
            }
            else {
                actionMessage+=players[i]->getName()+" has folded";
            }
            emit updateActionMessage(actionMessage);
            std::cout << chipPot << "\n";
        }
    }

    for (auto &player: players) {
        player->setPot(chipPot);
        player->setHighestPlayedBet(highestBet);
        roundFinished = true;
        std::cout<<player->getName()<<" "<<player->getChips() << "\n";
        std::cout<<player->getHighestBet()<<" "<<player->getHighestPlayedBet() << "\n";

    }

    for (auto &player: players) {
        std::cout<<player->getName()<<" "<<player->getCurrentBet() << "\n";
        if (player->getCurrentBet() != highestBet && player->getTag() == false) {
            roundFinished = false;
        }
        if (player->getChips() == 0 && player->getTag() == false) {
            roundFinished = true;
        }
    }

    return roundFinished;
}


void GameRunner::round1() {
    std::cout << "round1" << std::endl;
    roundCounter++;
    hand = players[0]->getHand();
    handToShow = handDetail(hand);
    std::cout<<"Hand to show:";
    for (auto &cards: handToShow) {
        std::cout << cards << std::endl;
    }
    this->sortBlinds();

    for (int i = 0; i < players.size(); i++) {
        players[i]->setCurrentPosition((i - dealerPosition + players.size()) % players.size());
    }

    emit updateGUIHidden();

    QCoreApplication::processEvents();
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < 2000) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    highestBet = 10; //Big blind
    roundFinished = false;

    while (!roundFinished) {
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
    std::cout<<"Round: "<<roundCounter<<" Community Cards size:"<<communityCards.size()<<"\n";

    roundFinished = false;


    for (auto& player: players) {
        player->updateCommunityHand(communityCards);
        auto tempBet = player->getCurrentBet();
        player->setHighestPlayedBet(highestBet);
        player->setHighestBet(highestBet);
    }

    while (!roundFinished) {
        bettingCycle();
    }

    std::string tempCard = dealCard(currentDeck);
    communityCards.push_back(tempCard);

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


    for (auto& player: players) {
        player->updateCommunityHand(communityCards);
        player->setHighestPlayedBet(highestBet);
        player->setHighestBet(highestBet);
    }

    while (!roundFinished) {
        bettingCycle();
    }



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
    highestStrength = 0;

    for (auto &player: players) {
        if (player->getTag() == true) {
            continue;
        }
        tempStrength = player->getHandStrength();
        std::cout << "Player Name: " << player->getName() << std::endl;
        std::cout << "Temp Strength: " << tempStrength << std::endl;
        if (tempStrength > highestStrength && tempStrength > tieStrength) {
            std::cout << player->getName() << " has progressed\n";
            tempLeaderName = player->getName();
            highestStrength = tempStrength;
            tieStrength = 0;
            playerTies.clear();
        }
        if (tempStrength == highestStrength) {
            std::cout << player->getName() << " has a tie\n";
            playerTies.push_back(player->getName());
            tieStrength = tempStrength;
        }
    }
    tieBreaker = 10;
    officialTieRank = 0;
    tieBroken = false;
    if (playerTies.empty()) {
        tieBroken = true;
    }
    std::cout<<"pties "<<playerTies.size()<<std::endl;
    while (!tieBroken && playerTies.size() > 1) {
        if (playerTies.size() != 0) {
            std::cout << "TieNotBroken\n";
            for (auto &playerName: playerTies) {
                for (auto &player : players) {
                    if (player->getName() == playerName) {
                        std::cout<<player->getName()<<"\n";
                        auto result = player->tieBreaker(tieStrength);
                        std::cout<<result.first<<"\n";
                        if (result.first < tieBreaker) {
                            tieBreaker = result.first;
                            tempLeaderName = player->getName();
                            tieStrength = 0;
                            tieBroken = true;
                        }
                        if (result.first == tieBreaker && tieBreaker != 10) {
                            tieStrength = result.first;
                            tieBroken = false;

                        }
                        if (result.first == 1) {
                            tieInboundCounter++;
                            officialTieRankString = result.second[0];
                            officialTieRankString = officialTieRankString.substr(1);
                            if (officialTieRankString == "1") {
                                officialTieRankString = "14";
                            }
                            temporaryTieRank = std::stoi(officialTieRankString);

                            if (temporaryTieRank > officialTieRank) {
                                tempLeaderName = player->getName();
                            }

                        }
                        else {
                            auto tieBrokePlayer = std::find_if(playerTies.begin(), playerTies.end(),
                                                                                [&player](std::string &playerToRemoveName) {
                                                                                    return playerToRemoveName == player->getName(); //
                                                                                    });

                            if (tieBrokePlayer != playerTies.end()) {
                                playerTies.erase(tieBrokePlayer);
                            }
                        }
                    }
                }
            }
        }
        if (tieInboundCounter == playerTies.size()) {
            tieBroken = true;
            officialTie = true;
        }
    }

    std::cout<<"Winner Name: "<<tempLeaderName<<std::endl;
    std::cout<<"Winner Strength: "<<tieStrength<<std::endl;

    std::string actionMessage = "Winner: "+tempLeaderName+" has won: "+std::to_string(chipPot);

    emit updateActionMessage(actionMessage);

    for (auto &player : players) {
            if (player->getName() == tempLeaderName) {
                player->changeChips(chipPot);
            }
    }

    emit updateGUIUnhidden();

    QCoreApplication::processEvents();
    QElapsedTimer timer;
    timer.start();

    while (timer.elapsed() < 5000) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
            std::cout<<"Action: "<<action<<std::endl;
            switch (action) {
                case 1:
                    if (chips >= players[i]->getChips()) {
                        std::cout << "Incorrect amount of chips available, call/check instead";
                        action = 0;
                        break;
                    }


                    if (chips< players[i]->getCurrentBet()-highestBet ) {
                        std::cout<<"chip lower then the difference";
                        chips = highestBet - players[i]->getCurrentBet();
                    }

                    std::cout<<"Chips to take: "<<chips<<std::endl;
                    players[i]->changeChips(-chips);
                    players[i]->setCurrentBet(chips);
                    chipPot += chips;
                    std::cout<<"difference between curr and hig: "<<players[i]->getCurrentBet()-highestBet<<std::endl;
                    if (players[i]->getCurrentBet()-highestBet > 0) {
                        highestBet += players[i]->getCurrentBet()-highestBet;
                    }
                    if (players[i]->getCurrentBet()-highestBet != players[i]->getCurrentBet() - players[i]->getHighestBet()) {
                        players[i]->setHighestBet(highestBet);
                    }
                break;

                case 0:
                    chips = highestBet - players[i]->getCurrentBet();
                    if (chips >= players[i]->getChips()) {
                        std::cout << "Incorrect amount of chips available, so betting remaining";
                        chips = players[i]->getChips();
                        break;
                    }
                    else {
                        std::cout<< "chips to bet: " << chips << std::endl;
                        std::cout<< "highest bet: " << highestBet << std::endl;
                        std::cout<< "Player chips before: " << players[i]->getChips() << std::endl;
                    }
                    chipPot += chips;
                    players[i]->changeChips(-chips);
                    players[i]->setCurrentBet(chips);
                    break;

                case 2:
                    players[i]->setTag(true);
                    break;
                default:
                    break;

            }
            std::cout<<"After user action chips bet: " << chips << std::endl;
            std::cout<<"After user action current bet: "<< players[i]->getCurrentBet() << std::endl;
            std::cout<<"After user action highest bet: "<< players[i]->getHighestBet() << std::endl;
            std::cout<<"After user action the gamerunner highest bet: "<< highestBet << std::endl;
            }
    }
    emit userInputProcessed();
}

std::unique_ptr<Player> GameRunner::findPlayer(std::string name) {
    for(auto &p: players) {
        if (p->getName() == name) {
            return std::unique_ptr<Player>(p.get());
        }
    }
    return nullptr;
}
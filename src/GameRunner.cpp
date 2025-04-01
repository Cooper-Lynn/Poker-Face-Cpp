//
// Created by coope on 20/01/2025.
//
#include "GameRunner.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

GameRunner::GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player>> &players, std::vector<std::string> &currentDeck){
  this->dealerPosition = dealerPosition;
  this->players = std::move(players);
  this->currentDeck = std::move(currentDeck);
    highestBet=0;
    chipPot=0;
  }

GameRunner::~GameRunner(){};

void GameRunner::sortBlinds() {
    int numPlayers = players.size();

    if (numPlayers < 2) return;

    chipPot += 15;
    if (numPlayers == 2) {
        players[dealerPosition]->changeChips(-5);
        players[(dealerPosition + 1) % numPlayers]->changeChips(-10);
    }
    else {
        int smallBlindPos = (dealerPosition + 1) % numPlayers;
        int bigBlindPos = (dealerPosition + 2) % numPlayers;

        players[smallBlindPos]->changeChips(-5);
        players[bigBlindPos]->changeChips(-10);
    }


    dealerPosition = (dealerPosition + 1) % numPlayers;
}

std::vector<std::string> GameRunner::handDetail(std::vector<std::string> &hand){
  std::vector<std::string> handToShow;
    for (auto& card : hand) {
        auto[Suite, Rank] = cardDetail(card);
        std::string cardToAddToHand = Rank + " of " + Suite+"\n";
        handToShow.push_back(cardToAddToHand);
    }
    return handToShow;
  }

void GameRunner::giveHandsToPlayers() {
    handsToGive = giveHands(currentDeck, players.size());
    for (auto& player : players) {
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

std::pair<std::string, std::string> GameRunner::cardDetail(std::string &card){
  std::string first;
    std::string second;
    if(card.at(0) == 's') {

        first = "Spades";
    }
    else if(card.at(0) == 'd') {

        first = "Diamonds";
    }
    else if(card.at(0) == 'h') {

        first = "Hearts";
    }
    else if(card.at(0) == 'c') {

        first = "Clubs";
    }

    std::string number =card.substr(1);
    if (number == "1" || number =="14") {
        second = "Ace";
    }
    else if (number=="11") {
        second = "Jack";
    }
    else if(number=="12") {
        second = "Queen";
    }
    else if(number=="13") {
        second = "King";
    }
    else {
        second = number;
    }

    return {first, second};
}

std::vector<std::string> GameRunner::giveHands(std::vector<std::string> &deck, int numOfPlayers) {
    std::vector<std::string> handsToGive;
    for (int i=0; i<numOfPlayers*2; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, deck.size()-1);
        int randomIndex = distrib(gen);
        handsToGive.push_back(deck[randomIndex]);
        deck.erase(deck.begin() + randomIndex);
    }
    return handsToGive;
}

std::string GameRunner::dealCard(std::vector<std::string> &deck) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, deck.size()-1);
    int randomIndex = distrib(gen);
    std::string card = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex);
    return card;
}

std::vector<std::string> GameRunner::createDeck() {
    std::vector<std::string> deck;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) {
            deck.push_back(suit+rank);
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
    for(int count = 0, i = (dealerPosition+1) % players.size(); count < players.size(); count++, i = (i + 1) % players.size()) {

        if(dynamic_cast<UserPlayer*>(players[i].get()) && players[i]->getChips()!=0) {
            std::cout<<"Remaining Chips: "<<players[i]->getChips();
            std::cout<<"\nCurrent Pot: "<<chipPot<<std::endl;
            std::cout<<"Player Options in Game Runner:"
                "\n1. "<<checkOrCall()<<
                "\n2. Raise"
                "\n3. Fold"
                "\n4. Quit Game"
                "\nEnter your choice: ";

            std::cin>>playerRoundChoice;
            switch(playerRoundChoice) {
                case 1:
                    chipInput = highestBet-players[i]->getCurrentBet();
                    if (chipInput >= players[i]->getChips()) {
                        std::cout<<"Incorrect amount of chips available";
                        break;
                    }
                    chipPot+=chipInput;
                    players[i]->changeChips(chipInput);
                    players[i]->setCurrentBet(chipInput);
                    break;

                case 2 :
                    std::cout<<"\nEnter how much you want to raise by (Remaining: "<<players[i]->getChips()<<"): ";
                    std::cin>>chipInput;
                    if (chipInput >= players[i]->getChips()) {
                        std::cout<<"Incorrect amount of chips available";
                        break;
                    }
                    chipPot+=chipInput;
                    players[i]->changeChips(-chipInput);
                    players[i]->setCurrentBet(chipInput);
                    if (chipInput>players[i]->getHighestBet()) {
                        players[i]->setHighestBet(chipInput);
                    }
                    break;

                case 3 :
                    std::cout<<"You have folded";
                    break;

                default:
                    break;
            }
        }

        else {
            int action = players[i]->getAction(players);
            chipPot+=30;
            players[i]->changeChips(-30);
            if (30>highestBet) {
                highestBet=chipInput;
            }
            std::cout<<chipPot;
        }


    }


    for(auto &player : players) {
        player->setPot(chipPot);
        player->setHighestPlayedBet(highestBet);
        roundFinished = true;
        if(player->getHighestBet()!=highestBet) {
            roundFinished = false;
        }
    }

    return roundFinished;
}


void GameRunner::round1() {

    hand = players[0]->getHand();
    handToShow = handDetail(hand);
    for (auto& cards : handToShow) {
        std::cout<<cards<<std::endl;
    }
    this->sortBlinds();

    for (int i=0 ; i<players.size(); i++){
        players[i]->setCurrentPosition((i - dealerPosition + players.size()) % players.size());
    }

    /*
    while (!roundFinished) {
        roundFinished = false;
        bettingCycle();
    }
    */

    for (int i=0; i < 3; i++) {
        std::string tempCard = dealCard(currentDeck);
        communityCards.push_back(tempCard);
    }
    std::cout<<"End of Round 1\n";
    std::cout<<chipPot;
    handToShow = handDetail(communityCards);
    std::cout<<"\nCommunity Cards: "<<std::endl;
    for (auto &card : handToShow) {
        std::cout<<card;
    }
}

void GameRunner::midRounds() {
    roundFinished = false;

    while(!roundFinished) {
        bettingCycle();
    }

    std::cout<<"End of Round 2\n";
    std::cout<<chipPot;
    handToShow = handDetail(communityCards);
    std::cout<<"\nCommunity Cards: "<<std::endl;

    for (auto &card : handToShow) {
        std::cout<<card;
    }
}

void GameRunner::finalRound() {
    roundFinished = false;

    while(!roundFinished) {
        bettingCycle();
    }



    highestStrength = 0;

    for(auto &player : players) {
        std::vector<std::string> theHand = player->getHand();
        handToShow = handDetail(theHand);
        std::cout<<"Player Name: "<<player->getName()<<std::endl;
        std::cout<<"Hand: ";
        for (auto &card : handToShow) {
            std::cout<<card;
        }
    }

    tempLeaderName = "";
    tieStrength = 0;

    for (auto &player : players) {
        tempStrength = player->getHandStrength();
        if (tempStrength>highestStrength && tempStrength > tieStrength) {
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
        if (playerTies.size()!=0) {
            for (auto &player : playerTies) {
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
                }
                else {
                    auto tieBrokePlayer = std::find_if(playerTies.begin(), playerTies.end(),
                    [&player](std::unique_ptr<Player>& playerToRemove) {
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
    std::cout<<"\nCommunity Cards: "<<std::endl;

    for (auto &card : handToShow) {
        std::cout<<card;
    }
}

std::vector<std::unique_ptr<Player>> GameRunner::getPlayers() {
    return std::move(players);
}






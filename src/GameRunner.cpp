//
// Created by coope on 20/01/2025.
//
#include "GameRunner.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <random>
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

GameRunner::GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player>> &players, std::vector<std::string> &currentDeck){
  this->dealerPosition = dealerPosition;
  this->players = std::move(players);
  this->currentDeck = std::move(currentDeck);
  }

GameRunner::~GameRunner(){};

void GameRunner::sortBlinds(){
  if(players.size()==2) {
            chipPot +=15;
            players[1]->changeChips(-10);
            players[0]->changeChips(-5);
        }
        else {
            if (dealerPosition+1<players.size()) {
                players[dealerPosition+1]->changeChips(-5);
                chipPot+=15;
            }
            else {
                players[0]->changeChips(-5);
                players[1]->changeChips(-10);
                chipPot+=15;
            }
            if (dealerPosition+2<players.size()) {
                players[dealerPosition+2]->changeChips(-10);
            }
            else {
                players[0]->changeChips(-10);
            }
            dealerPosition+=1;
        }
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
    if (number == "1") {
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

std::vector<std::string> GameRunner::createDeck(std::vector<std::string> &suits, std::vector<std::string> &ranks) {
    std::vector<std::string> deck;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) {
            deck.push_back(suit+rank);
        }
    }
    return deck;
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

void GameRunner::round1() {
    handsToGive = giveHands(currentDeck, dealerPosition);
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


    handToShow = handDetail(hand);
    for (auto& cards : handToShow) {
        std::cout<<cards<<std::endl;
    }

    for (int i=0; i < 3; i++) {
        std::string tempCard = dealCard(currentDeck);
        communityCards.push_back(tempCard);
    }
    while (!roundFinished) {
        for(int i = (dealerPosition+3)%players.size(); i < players.size()+3; i++) {
            if(players[(dealerPosition+i)%players.size()] == players[0]) {
                std::cout<<"Player Options:"
                            "\n1. "<<checkOrCall()<<
                            "\n2. Raise"
                            "\n3. Fold"
                            "\n4. Quit Game"
                            "\nEnter your choice: ";
                std::cin>>playerRoundChoice;
                if (playerRoundChoice == 1) {

                }
                else if (playerRoundChoice == 2) {
                    std::cout<<"\nEnter how much you want to raise by (Remaining: "<<players[0]->getChips()<<"): ";
                    std::cin>>chipInput;
                    chipPot+=chipInput;
                    players[0]->changeChips(-chipInput);
                    if (chipInput<highestBet) highestBet=chipInput;
                }
                else if (playerRoundChoice==3) {
                    std::cout<<"You have folded";
                }
                else if (playerRoundChoice==4) {
                    break;
                }
                else {
                    players[(dealerPosition + i)%players.size()]->changeChips(-10);
                    chipPot+=10;
                }

            }

        }
    }
    std::cout<<chipPot;
    handToShow = handDetail(communityCards);
    std::cout<<"Community Cards: "<<std::endl<<std::endl;
    for (auto &card : handToShow) {
        std::cout<<card;
    }

}

void GameRunner::round2() {
    std::string tempCard = dealCard(currentDeck);
    communityCards.push_back(tempCard);
}





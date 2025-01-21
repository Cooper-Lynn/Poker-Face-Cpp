//
// Created by coope on 20/01/2025.
//
#include "GameRunner.hpp"
#include <vector>
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"

GameRunner::GameRunner(int dealerPosition, std::vector<std::unique_ptr<Player>> &players, std::vector<std::string> &allCards){
  this->dealerPosition = dealerPosition;
  this->players = std::move(players);
  this->allCards = std::move(allCards);
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



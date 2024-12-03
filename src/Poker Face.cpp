// Poker Face.cpp
#include <iostream>
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include <vector>
#include <array>
#include <random>
#include <utility>
#include <memory>

std::vector<std::string>
    giveHands(std::vector<std::string> &deck, int numOfPlayers) {
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


int main() {
    std::vector<std::string> suits = {"s", "h", "d", "c"}; // spades, hearts, diamonds, clubs
    std::vector<std::string> ranks = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"}; // Ace to King

    // Create the deck
    std::vector<std::string>deck;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) {
            deck.push_back(suit+rank);
        }
    }


    int option = 0;
    while (!option) {
        std::cout<<"Menu\n";
        std::cout<<"1. Single player\n";
        std::cout<<"2. Multiplayer\n";
        std::cout<<"3. Quit\n";
        std::cout<<"\nEnter your choice: ";
        std::cin>>option;
    }

    if (option==1) {
        std::vector<std::string> aiNames = {"Bert", "Ruben", "Chanel", "Dimitri", "Gary", };
        std::string playerName;
        std::cout<<"\nEnter your username: \n";
        std::cin>>playerName;
        int numPlayer;
        std::cout<<"\nHow many players would you want to oppose? (Min 1): ";
        std::cin>>numPlayer;

        while(numPlayer<1) {
            std::cout<<"\nHow many players would you want to oppose? (Min 1): ";
            std::cin>>numPlayer;
        }
        std::vector<std::unique_ptr<Player>> players;
        players.push_back(std::make_unique<UserPlayer>(playerName));
        for (auto i = 0; i < numPlayer; i++) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, aiNames.size() - 1);
            int randomIndex = distrib(gen);
            players.push_back(std::make_unique<AIPlayer>(aiNames[randomIndex]));
            aiNames.erase(aiNames.begin() + randomIndex);



        }
        for (auto &player : players) {
            std::cout<<"Player: ";
            std::cout<< player->getName()<<"\n";
        }


        std::vector<std::string >handsToGive =giveHands(deck, players.size());


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

        for (const auto& card: handsToGive) {
            std::cout<<card;
        }
        std::vector<std::string> hand = players[0]->getHand();
        for (const auto& card: hand) {
            std::cout<< card;
        }

        int starter = 0;




    }





        /**
         *
         * MULTIPLAYER SECTION
         *
         */

        if (option==2) {
            std::string playerName;
            std::cout<<"\nEnter your username: \n";
            std::cin>>playerName;
            UserPlayer player1 (playerName);
            std::cout<<player1.getName();
        }
        else
            {
            option=0;
            return 0;
        }
}



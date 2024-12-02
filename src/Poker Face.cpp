// Poker Face.cpp
#include <iostream>
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include <vector>
#include <array>
#include <random>
#include <utility>
#include <memory>


int main() {
    std::vector<std::string> suits = {"s", "h", "d", "c"}; // spades, hearts, diamonds, clubs
    std::vector<std::string> ranks = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"}; // Ace to King

    // Create the deck
    std::vector<std::array<std::string, 2>> deck;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) {
            deck.push_back({suit, rank});
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
        UserPlayer player1 (playerName);
        std::cout<<player1.getName();
        int numPlayer;
        std::cout<<"\nHow many players would you want to oppose?: ";
        std::cin>>numPlayer;
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
        if (option==2) {
            std::string playerName;
            std::cout<<"\nEnter your username: \n";
            std::cin>>playerName;
            UserPlayer player1 (playerName);
            std::cout<<player1.getName();
        }
        if (option==3) {
            return 0;
        }
    }
}


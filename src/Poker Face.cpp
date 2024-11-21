// Poker Face.cpp
#include <iostream>
#include "Cards.cpp"
#include "UserPlayer.cpp"
#include "Player.cpp"
#include "AIPlayer.cpp"
#include <vector>
#include <array>
#include <random>


int main() {
    std::vector<std::string> suits = {"s", "h", "d", "c"}; // spades, hearts, diamonds, clubs
    std::vector<std::string> ranks = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"}; // Ace to King
    std::pmr::vector<std::string> aiNames = {"Bert", "Ruben", "Chanel", "Dimitri", "Gary", };

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
        std::cout<<"3. Quit";
        std::cout<<"Enter your choice: ";
        std::cin>>option;
    }

    if (option==1) {
        std::string playerName;
        std::cout<<"\nEnter your username: \n";
        std::cin>>playerName;
        UserPlayer player1 (playerName);
        std::cout<<player1.getName();
        int numPlayer;
        std::cout<<"\nHow many players would you want to oppose?: ";
        std::cin>>numPlayer;
        std::vector<Player> players;
        for (auto i = 0; i < numPlayer; i++) {
            players.emplace_back(i());

        }
        if (option==2) {
            std::string playerName;
            std::cout<<"\nEnter your username: \n";
            std::cin>>playerName;
            UserPlayer player1 (playerName, 100);
            std::cout<<player1.getName();
        }
        if (option==3) {
            return 0;
        }
    }
}


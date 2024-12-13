// Poker Face.cpp
#include <iostream>
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include <vector>
#include <array>
#include <random>
#include <utility>
#include <memory>


/*
 *Function to create a deck of cards to be used in the game
 *@param suits is the suits in the deck, ranks is the ranks in the deck
 *@return the complete deck
 */
std::vector<std::string> createDeck(std::vector<std::string> &suits, std::vector<std::string> &ranks) {
    std::vector<std::string> deck;
    for (const auto &suit : suits) {
        for (const auto &rank : ranks) {
            deck.push_back(suit+rank);
        }
    }
    return deck;
}

/*
 *Function to pick a random card from the deck
 *@param, reference to the deck
 *@
 */

std::string dealCard(std::vector<std::string> &deck) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, deck.size()-1);
    int randomIndex = distrib(gen);
    std::string card = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex);
    return card;
}

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

std::pair<std::string, std::string> cardDetail(std::string& card) {
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

std::vector<std::string> handDetail(std::vector<std::string>& hand) {
    std::vector<std::string> handToShow;
    for (auto& card : hand) {
        auto[Suite, Rank] = cardDetail(card);
        std::string cardToAddToHand = Rank + " of " + Suite+"\n";
        handToShow.push_back(cardToAddToHand);
    }
    return handToShow;
}

int main() {

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
        std::vector<std::string> suits = {"s", "h", "d", "c"}; // spades, hearts, diamonds, clubs
        std::vector<std::string> ranks = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"}; // Ace to King
        // Create the deck
        std::vector<std::string>deck = createDeck(suits, ranks);
        std::vector<std::string> riverCards;
        std::vector<std::string> aiNames = {"Bert", "Ruben", "Chanel", "Dimitri", "Gary","Steve"};

        int dealerPosition = 0;
        int chipInput;
        int chipPot =0;

        std::string playerName;
        std::cout<<"\nEnter your username: \n";
        std::cin>>playerName;
        int numPlayer;
        std::cout<<"\nHow many players would you want to oppose? (Min 1, Max 6): ";
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


            /*
             *This Section lists out all the players in the game
             */
        }
        for (auto &player : players) {
            std::cout<<"Player: ";
            std::cout<< player->getName()<<"\n";
        }


        std::vector<std::string >handsToGive =giveHands(deck, players.size());

        /*
         *This Section gives all players their cards
         */
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

        std::vector<std::string> hand = players[0]->getHand();
        /*
        std::string Suite;
        std::string Rank;
        for ( auto& card : hand) {
            auto[Suite, Rank] = cardDetail(card);
            std::cout<<Rank<<" of "<<Suite<<std::endl;
        }
        */
        std::vector<std::string> handToShow = handDetail(hand);
        for (auto& cards : handToShow) {
            std::cout<<cards<<std::endl;
        }
        //int starter = 0;


        /*
         *This section works out the blinds for the game, whether there is only 2 players or more
         *and takes into account if the blind position would go other the size of the array
         */

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

        for (int i=0; i < 3; i++) {
            std::string tempCard = dealCard(deck);
            riverCards.push_back(tempCard);
        }
        for (auto &card : riverCards) {
            std::cout<<card<<std::endl;
        }


        for(int i = 1; i <= players.size(); i++) {
            if(players[(dealerPosition+i)%players.size()]==players[0]) {

                /*FROM HERE INITIAL BETTING*/
                std::cout<<""
                std::cin>>chipInput;

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


        }
        else
        {
            option=0;
            return 0;
        }
}




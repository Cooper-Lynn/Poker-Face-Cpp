// Poker Face.cpp
#include <iostream>
#include "Cards.cpp"
#include "UserPlayer.cpp"
#include "Player.cpp"
#include "AIPlayer.cpp"


int main()
{

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
        UserPlayer player1 (playerName, 100);
        std::cout<<UserPlayer::getName();
    }
}


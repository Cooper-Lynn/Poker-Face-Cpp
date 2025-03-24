#include "gamebaseview.h"
#include "ui_gamebaseview.h"
#include "userinputgameinitialiser.h"
#include "MainGui.hpp"
#include "AIPlayer.hpp"
#include "UserPlayer.hpp"
#include <QButtonGroup>
#include <QImage>
#include <iostream>
#include <filesystem>

GameBaseView::GameBaseView(QWidget *parent, MainGui *mainGui)
    : QWidget(parent)
    , ui(new Ui::GameBaseView)
    , mainGui(mainGui)
{
    ui->setupUi(this);
}

GameBaseView::~GameBaseView()
{
    delete ui;
}

std::vector<std::string> GameBaseView::allowUserSetup() {
    std::vector<std::string> userInputs;
    userInitialiser = std::make_unique<userInputGameInitialiser>(this, this);
    userInitialiser->show();


    return userInputs;
}

void GameBaseView::passUserInput(std::vector<std::string> &userInput) {
    mainGui->passUserInputToPoker(userInput);
    userInitialiser->hide();
}

void GameBaseView::setGameRunner(GameRunner& gameRunner){
    this->gameRunner = &gameRunner;
    startGameRunner();
}

void GameBaseView::updateHiddenView() {
    updateCardBackPositions();
    updatePlayerGui();
}

void GameBaseView::updateShownView() {
    updateCardShownPositions();
    updatePlayerGui();
}


void GameBaseView::startGameRunner() {
    players = std::move(gameRunner->getPlayers());
    currentDeck = std::move(gameRunner->getCurrentDeck());
    updateHiddenView();
}

void GameBaseView::updateCardBackPositions() {
    std::cout<<"Updating card back positions\n";
    std::filesystem::path filePath = __FILE__; // Path of the current source file
    std::filesystem::path rootPath = filePath.parent_path().parent_path(); // Move up directories

    std::cout << "Project Root: " << rootPath << std::endl;

    int i=0;
    for (auto& player : players) {

        if(dynamic_cast<AIPlayer*>(player.get())) {
            std::cout<<"AIPlayer "<<player->getName()<<"\n";
            QImage card1("BackOfCard90p.png");
            QImage card2("BackOfCard90p.png");
            auto pixelPair = aiPlayerCardPositions[i];
            qPaint.drawImage(pixelPair.first, pixelPair.second, card1);
            qPaint.drawImage(pixelPair.first+5, pixelPair.second+5, card2);

        }
        i++;
    }
}

void GameBaseView::updateCardShownPositions() {
    for(auto& player : players) {
        if(dynamic_cast<AIPlayer*>(player.get())){
            std::vector<std::string> currentHand = player->getHand();

        }
    }
}

void GameBaseView::updatePlayerGui() {

}



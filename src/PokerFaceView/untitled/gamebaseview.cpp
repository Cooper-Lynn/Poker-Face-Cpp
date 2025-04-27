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
#include <QFile>
#include <QTextStream>

#include "usergameinputdialogue.h"

GameBaseView::GameBaseView(QWidget *parent, MainGui *mainGui)
    : QWidget(parent)
      , ui(new Ui::GameBaseView)
      , mainGui(mainGui) {
    ui->setupUi(this);
}

GameBaseView::~GameBaseView() {
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

void GameBaseView::setGameRunner(GameRunner &gameRunner) {
    this->gameRunner = &gameRunner;
    startGameRunner();
}

void GameBaseView::updateHiddenView() {
    for (auto card: cardLabels) {
        delete card;
    }
    for (auto card: cardCommunityLabels) {
        delete card;
    }
    cardLabels.clear();
    cardCommunityLabels.clear();
    players = std::move(gameRunner->getPlayers());
    currentDeck = std::move(gameRunner->getCurrentDeck());
    updateCardBackPositions();
    updateCommunityCards();
    updateAIGui();
    updatePlayerGui();
    this->update();
}

void GameBaseView::updateShownView() {
    for (auto card: cardLabels) {
        delete card;
    }
    for (auto card: cardCommunityLabels) {
        delete card;
    }
    cardLabels.clear();
    cardCommunityLabels.clear();
    players = std::move(gameRunner->getPlayers());
    currentDeck = std::move(gameRunner->getCurrentDeck());
    updateCardShownPositions();
    updateCommunityCards();
    updatePlayerGui();
    updateAIGui();
    this->update();
}

void GameBaseView::updateCommunityCards() {
    communityCards = std::move(gameRunner->getCommunityCards());
    for (auto *label: cardCommunityLabels) {
        label->deleteLater();
    }
    for (int i = 0; i < communityCards.size(); i++) {
        auto *communityCardLabel = new QLabel(this);

        QPixmap communityCard(QString("src/PokerFaceView/untitled/playingCards/%1.png").arg(communityCards[i].data()));

        communityCardLabel->setPixmap(communityCard);
        communityCardLabel->setGeometry(communityCardsPositions[i].first, communityCardsPositions[i].second, communityCard.width(), communityCard.height());
        communityCardLabel->show();
        cardCommunityLabels.push_back(communityCardLabel);
    }
}


void GameBaseView::startGameRunner() {
    players = std::move(gameRunner->getPlayers());
    currentDeck = std::move(gameRunner->getCurrentDeck());
    updateHiddenView();
}

void GameBaseView::updateCardBackPositions() {
    std::cout << "Updating card back positions\n";
    std::filesystem::path filePath = __FILE__; // Path of the current source file
    std::filesystem::path rootPath = filePath.parent_path().parent_path(); // Move up directories

    std::cout << "Project Root: " << rootPath << std::endl;

    int i = 0;
    for (auto &player: players) {
        if (dynamic_cast<AIPlayer *>(player.get())) {
            QLabel *cardLabel = new QLabel(this);
            QLabel *cardLabel2 = new QLabel(this);
            QPixmap cardPixmap("src/PokerFaceView/untitled/playingCards/BackOfCard90p.png");
            QPixmap cardPixmap2("src/PokerFaceView/untitled/playingCards/BackOfCard90p.png");
            cardLabel->setPixmap(cardPixmap);
            cardLabel2->setPixmap(cardPixmap2);
            auto pixelPair = aiPlayerCardPositions[i];
            cardLabel->setGeometry(pixelPair.first, pixelPair.second, cardPixmap.width(), cardPixmap.height());
            cardLabel2->setGeometry(pixelPair.first + 5, pixelPair.second + 5, cardPixmap.width(), cardPixmap.height());
            cardLabel->show();
            cardLabel2->show();
            cardLabels.push_back(cardLabel);
            cardLabels.push_back(cardLabel2);
            std::cout << "AIPlayer " << player->getName() << "\n";
            i++;
        }
    }
}

void GameBaseView::updateCardShownPositions() {
    int i = 0;
    for (auto &player: players) {
        if (dynamic_cast<AIPlayer *>(player.get())) {
            std::vector<std::string> currentHand = player->getHand();
            auto card1 = currentHand[0];
            auto card2 = currentHand[1];
            QLabel *cardLabel = new QLabel(this);
            QLabel *cardLabel2 = new QLabel(this);
            QPixmap cardPixmap((("src/PokerFaceView/untitled/playingCards/"+card1+".png").data()));
            QPixmap cardPixmap2((("src/PokerFaceView/untitled/playingCards/"+card1+".png").data()));
            cardLabel->setPixmap(cardPixmap);
            cardLabel2->setPixmap(cardPixmap2);
            auto pixelPair = aiPlayerCardPositions[i];
            cardLabel->setGeometry(pixelPair.first, pixelPair.second, cardPixmap.width(), cardPixmap.height());
            cardLabel2->setGeometry(pixelPair.first + 5, pixelPair.second + 5, cardPixmap.width(), cardPixmap.height());
            cardLabel->show();
            cardLabel2->show();
            cardLabels.push_back(cardLabel);
            cardLabels.push_back(cardLabel2);
            std::cout << "AIPlayer " << player->getName() << "\n";
            i++;
        }
    }
}

void GameBaseView::updatePlayerGui() {
    for (auto &player: players) {
        if (dynamic_cast<UserPlayer *>(player.get())) {
            QLabel *playerNameLabel = new QLabel(this);
            playerNameLabel->setGeometry(631, 480, 150, 30);
            playerNameLabel->setText(player->getName().data());
            playerNameLabel->show();

            userHand = player->getHand();
        }

        QLabel *playerCardLabel = new QLabel(this);
        QLabel *playerCardLabel2 = new QLabel(this);


        QPixmap cardPixmap((("src/PokerFaceView/untitled/playingCards/" + userHand[0] + ".png").data()));
        QPixmap cardPixmap2((("src/PokerFaceView/untitled/playingCards/" + userHand[1] + ".png").data()));

        playerCardLabel->setPixmap(cardPixmap);
        playerCardLabel2->setPixmap(cardPixmap2);
        playerCardLabel->setGeometry(530, 543, cardPixmap.width(), cardPixmap.height());
        playerCardLabel2->setGeometry(660, 543, cardPixmap.width(), cardPixmap.height());
        playerCardLabel->show();
        playerCardLabel2->show();
        cardLabels.push_back(playerCardLabel);
        cardLabels.push_back(playerCardLabel2);
    }
}

void GameBaseView::updateAIGui() {
    int i = 0;
    for (auto &player: players) {
        if (dynamic_cast<AIPlayer *>(player.get())) {
            QLabel *nameLabel = new QLabel(this);
            auto pixelPair = aiPlayerNamePositions[i];
            nameLabel->setText(player->getName().data());
            nameLabel->setGeometry(pixelPair.first, pixelPair.second, 150, 30);
            nameLabel->show();
            i++;
        }
    }
}

void GameBaseView::userInput() {
    std::cout<<"gamebaseview"<<std::endl;
    userInputDialogue = std::make_unique<UserGameInputDialogue>(this, this);
    int maxChips = 0;
    int currentbet = 0;
    updateHiddenView();
    for (auto &player: players) {
        if (dynamic_cast<UserPlayer *>(player.get())) {
            maxChips = player->getChips();
            currentbet = player->getCurrentBet();
            qDebug() << "maxChips: " << maxChips << "\n";
        }
    }
    std::string result = gameRunner->checkOrCall(currentbet);
    userInputDialogue->updateMaxChips(maxChips);
    userInputDialogue->updateCheckOrCall(result);
    userInputDialogue->update();
    userInputDialogue->show();


}

void GameBaseView::passUserChoice(int action, int chips ){
    mainGui->getUserGameInput(action, chips);
}

void GameBaseView::closeEvent(QCloseEvent *event) {
    exit(0);
}



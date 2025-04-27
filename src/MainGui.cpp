//
// Created by coope on 19/03/2025.
//

#include "MainGui.hpp"
#include <PokerFaceView/untitled/gameview.h>
#include <QApplication>
#include <PokerFaceView/untitled/mainwindow.h>
#include <memory>
#include <QPushButton>


MainGui::MainGui(int argc, char *argv[], PokerFace &main) : pokerFace(main) {
    this->a = new QApplication(argc, argv);
    this->mainWindow = std::make_unique<MainWindow>();
    QObject::connect(this->mainWindow.get(), &MainWindow::startGameSignal,
                     this, &MainGui::onStartGameRequest);



    startGUI();
};

MainGui::~MainGui() = default;

int MainGui::startGUI() {
    mainWindow->setWindowTitle("Start Menu");
    mainWindow->show();
    return a->exec();
}

void MainGui::onStartGameRequest() {
    mainWindow->hide();
    startGameView();
}


void MainGui::startConfirmed() {
    ;
}

void MainGui::startGameView() {
    std::vector<std::string> userInputSetup;

    gameView = std::make_unique<GameBaseView>(nullptr, this);
    gameView->setWindowTitle("Poker Face");

    gameView->showNormal();
    gameView->activateWindow();
    gameView->setWindowFlags(Qt::Window);

    gameView->resize(1280, 720);
    gameView->raise();
    gameView->show();
    gameView->move(100, 100);

    gameView->activateWindow();
    userInputSetup = gameView->allowUserSetup();
}

void MainGui::passUserInputToPoker(std::vector<std::string> &userInput) {
    qDebug() << "Within MainGui";
    pokerFace.gameStarted(userInput, this);
}

void MainGui::setGameRunnerPointer(GameRunner *gameRunner) {
    std::cout << "Setting GameRunnerPointer" << std::endl;
    this->gameRunner = gameRunner;
    auto conn = QObject::connect(gameRunner, &GameRunner::userInputRequired,
            this, &MainGui::showUserGameInputDialogue);
    qDebug() << "Connection established:" << (conn ? "yes" : "no");

    auto conn2 = QObject::connect(gameRunner, &GameRunner::updateGUIHidden,
            this, &MainGui::updateHiddenGameBaseView);
    gameView->setGameRunner(*this->gameRunner);

    auto conn3 = QObject::connect(gameRunner, &GameRunner::updateGUIUnhidden,
        this, &MainGui::updateUnhiddenGameBaseView);


}

void MainGui::showUserGameInputDialogue() {
    gameView->userInput();
}

void MainGui::getUserGameInput(int action, int chips) {
    gameRunner->setUserInput(action, chips);
}

void MainGui::updateHiddenGameBaseView() {
    gameView->updateHiddenView();
}

void MainGui::updateUnhiddenGameBaseView() {
    qDebug() << "Within MainGui, updating unhidden";
    gameView->updateShownView();

}

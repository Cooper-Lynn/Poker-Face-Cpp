//
// Created by coope on 19/03/2025.
//

#include "MainGui.hpp"
#include <PokerFaceView/untitled/gameview.h>
#include <QApplication>
#include <PokerFaceView/untitled/mainwindow.h>
#include <QPushButton>


MainGui::MainGui(int argc, char *argv[], PokerFace& main) : pokerFace(main) {
    this->a = new QApplication(argc, argv);
    this->mainWindow = new MainWindow();;
    startGUI();


};

MainGui::~MainGui() = default;

int MainGui::startGUI() {
    mainWindow->setWindowTitle("Main GUI");
    mainWindow->show();
    return a->exec();
}

int MainGui::onStartGameRequest() {

    mainWindow->destroyed();
    this->gameView = new GameView();
    gameView->show();
    pokerFace.gameStarted();

    return a->exec();
}

int MainGui::startConfirmed() {
    return a->exec();

}




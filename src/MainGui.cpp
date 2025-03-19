//
// Created by coope on 19/03/2025.
//

#include "MainGui.hpp"
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


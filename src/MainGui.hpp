//
// Created by coope on 19/03/2025.
//
#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QApplication>
#include <PokerFaceView/untitled/gameview.h>
#include <PokerFaceView/untitled/mainwindow.h>
#include "PokerFace.hpp"



class MainGui {
private:
    QApplication *a;
    MainWindow *mainWindow;
    PokerFace& pokerFace;
    GameView* gameView;

private slots:
    int onStartGameRequest();
    int startConfirmed();

public:
    MainGui(int argc, char *argv[], PokerFace& main);
    ~MainGui();
    int startGUI();

};



#endif //MAINGUI_HPP

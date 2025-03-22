//
// Created by coope on 19/03/2025.
//
#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QApplication>
#include <PokerFaceView/untitled/GameBaseView.h>
#include <PokerFaceView/untitled/mainwindow.h>
#include "PokerFace.hpp"



class MainGui : public QObject {

    Q_OBJECT

private:
    QApplication *a;
    std::unique_ptr<MainWindow> mainWindow;
    PokerFace& pokerFace;
    std::unique_ptr<GameBaseView> gameView;

private slots:
    void onStartGameRequest();
    void startConfirmed();

public:
    MainGui(int argc, char *argv[], PokerFace& main);
    ~MainGui();
    int startGUI();
    void startGameView();
    void passUserInputToPoker(std::vector<std::string> &userInput);

};



#endif //MAINGUI_HPP

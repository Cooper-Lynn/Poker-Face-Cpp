#include "gamebaseview.h"
#include "ui_gamebaseview.h"
#include "userinputgameinitialiser.h"
#include "MainGui.hpp"
#include <QButtonGroup>

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
}

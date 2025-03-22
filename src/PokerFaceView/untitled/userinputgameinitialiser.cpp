#include "userinputgameinitialiser.h"

#include <iostream>

#include "ui_userinputgameinitialiser.h"
#include "gamebaseview.h"
#include "ui_gamebaseview.h"
#include <QButtonGroup>
#include <QMessageBox>


userInputGameInitialiser::userInputGameInitialiser(QWidget *parent, GameBaseView* gameView)
    : QDialog(parent), gameView(gameView)
    , ui(new Ui::userInputGameInitialiser)
{
    ui->setupUi(this);

    QButtonGroup *buttonGroup = new QButtonGroup(this);


    buttonGroup->addButton(ui->ageConfirm);
    buttonGroup->addButton(ui->ageDeny);


    buttonGroup->setExclusive(true);


}

userInputGameInitialiser::~userInputGameInitialiser()
{
    delete ui;
}



void userInputGameInitialiser::on_confirmPush_clicked()
{
    std::cout<<"clicking confirm";
    if (ui->ageConfirm->isChecked()) {

        QString name = ui->userNameInput->text();
        QString aiNum = ui->AINumberInput->text();

        std::string userName = name.toStdString();
        std::string AI = aiNum.toStdString();

        userInput.push_back(userName);
        userInput.push_back(AI);

        try {
            int num = aiNum.toInt();
        }
        catch (...) {
            QMessageBox::information(this, "Error", "Please enter a number for AI between 1 and 6");
        }
        int num = aiNum.toInt();

        if(num <1 || num>6) {
            QMessageBox::information(this, "Error", "Please enter a number for AI between 1 and 6");
        }
        if(userName.size() <=0 || userName.size()>18) {
            QMessageBox::information(this, "Error", "Name is invalid, must be less then 18 characters");
        }
        else {
            if (gameView) {
                gameView->passUserInput(userInput);
            } else {
                QMessageBox::critical(this, "Error", "GameView is not initialized.");
            }
        }



    } else {
        QMessageBox::information(this, "Error", "You must be 18 or older to play this game");
    }
}


void userInputGameInitialiser::on_quitPush_clicked()
{
    exit(0);
}

std::vector<std::string> userInputGameInitialiser::getUserInput() {
    qDebug() <<userInput[0];
    qDebug() <<userInput[1];
    return userInput;
}


void userInputGameInitialiser::findLineEdits() {
    userLineEdit = this->findChild<QLineEdit*>("userNameInput");
    aiNumLineEdit = this->findChild<QLineEdit*>("AINumberInput");
    if (!userLineEdit) {
        qDebug() << "Error: userLineEdit not found!";
    }
    if (!aiNumLineEdit) {
        qDebug() << "Error: aiNumLineEdit not found!";
    }
}




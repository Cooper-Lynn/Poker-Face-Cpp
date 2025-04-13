#include "usergameinputdialogue.h"

#include <QApplication>
#include <QMessageBox>

#include "ui_usergameinputdialogue.h"

UserGameInputDialogue::UserGameInputDialogue(QWidget *parent, GameBaseView* gameView)
    : QDialog(parent), gameView(gameView)
      , ui(new Ui::UserGameInputDialogue) {
    ui->setupUi(this);
}

UserGameInputDialogue::~UserGameInputDialogue() {
    delete ui;
}

void UserGameInputDialogue::on_callCheckRButton_clicked()
{
    action = 0;
    chips = 0;
}


void UserGameInputDialogue::on_raiseRButton_clicked()
{
    QString chipsString = ui->raiseByLabel->text();
    action = 1;
    try {
        chips = chipsString.toInt();
    }
    catch (...) {
        QMessageBox::information(this, "Error", "Invalid Chips");
    }

}


void UserGameInputDialogue::on_foldRButton_clicked()
{
    action = 2;
    chips = 0;
}


void UserGameInputDialogue::on_buttonBox_accepted()
{
    if (gameView && (action == 1 || action == 2 || action == 0)) {
        gameView->passUserChoice(action, chips);
    }
    else {
        QMessageBox::information(this, "Error", "You need to choose an action");
        this->show();
    }
}

void UserGameInputDialogue::updateMaxChips(int chips) {
    maxChips = chips;
    cashLabel = this->findChild<QLabel*>("cashLabel");
    cashLabel->setText("Cash: "+QString::number(chips));
}

std::pair<int, int> UserGameInputDialogue::getUserInput() {
    return std::make_pair(action, chips);
}


void UserGameInputDialogue::closeEvent(QCloseEvent *event) {
    qDebug() <<"Closing down";
    exit(0);
}
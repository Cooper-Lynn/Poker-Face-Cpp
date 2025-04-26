#include "usergameinputdialogue.h"

#include <QApplication>
#include <QMessageBox>

#include "ui_usergameinputdialogue.h"

UserGameInputDialogue::UserGameInputDialogue(QWidget *parent, GameBaseView* gameView)
    : QDialog(parent), gameView(gameView)
      , ui(new Ui::UserGameInputDialogue) {
    ui->setupUi(this);

    raiseLabel = this->findChild<QLabel*>("raiseByLabel");
    raiseEdit = this->findChild<QLineEdit*>("raiseEdit");
}

UserGameInputDialogue::~UserGameInputDialogue() {
    delete ui;
}

void UserGameInputDialogue::on_callCheckRButton_clicked()
{
    raiseLabel->hide();
    raiseEdit->hide();
    action = 0;
    chips = 0;

}


void UserGameInputDialogue::on_raiseRButton_clicked()
{
    raiseLabel->show();
    raiseEdit->show();
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
    raiseLabel->hide();
    raiseEdit->hide();
    action = 2;
    chips = 0;
}


void UserGameInputDialogue::on_buttonBox_accepted()
{
    qDebug() << maxChips;
    if (gameView){
        action = -1;
        if (ui->foldRButton -> isChecked()) {
            action = 2;
            chips = 0;
            std::cout<<action<<"\n";
            gameView->passUserChoice(action, chips);
        }
        else if (ui ->raiseRButton -> isChecked()) {
            raiseLabel->show();
            raiseEdit->show();
            QString chipsString = ui->raiseEdit->text();
            action = 1;
            std::cout<<action<<"\n";
            chips = chipsString.toInt();
            qDebug()<<chips;
            try {
                chips = chipsString.toInt();
                qDebug()<<chips;
                gameView->passUserChoice(action, chips);
            }
            catch (...) {
                QMessageBox::information(this, "Error", "Invalid Chips");
            }
        }
        else if (ui->callCheckRButton -> isChecked()) {
            raiseLabel->hide();
            raiseEdit->hide();
            action = 0;
            chips = 0;
            std::cout<<action<<"\n";
            gameView->passUserChoice(action, chips);
        }
        else if (action == -1) {
            QMessageBox::information(this, "Error", "You need to choose an action");
            this->show();
        }
    }
    else{
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
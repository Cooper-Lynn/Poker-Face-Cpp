#include "userinputgameinitialiser.h"
#include "ui_userinputgameinitialiser.h"

userInputGameInitialiser::userInputGameInitialiser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userInputGameInitialiser)
{
    ui->setupUi(this);
}

userInputGameInitialiser::~userInputGameInitialiser()
{
    delete ui;
}

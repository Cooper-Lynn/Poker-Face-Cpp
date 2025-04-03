#include "usergameinputdialogue.h"
#include "ui_usergameinputdialogue.h"

UserGameInputDialogue::UserGameInputDialogue(QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::UserGameInputDialogue) {
    ui->setupUi(this);
}

UserGameInputDialogue::~UserGameInputDialogue() {
    delete ui;
}

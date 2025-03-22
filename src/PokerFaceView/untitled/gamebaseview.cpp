#include "gamebaseview.h"
#include "ui_gamebaseview.h"

GameBaseView::GameBaseView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameBaseView)
{
    ui->setupUi(this);
}

GameBaseView::~GameBaseView()
{
    delete ui;
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPushButton"
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    findStartQuitChild();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_StartButton_clicked()
{
    if (startButton && quitButton) {
        startButton->hide();
        quitButton->hide();
    }
}



void MainWindow::findStartQuitChild() {
    startButton = this->findChild<QPushButton*>("StartButton");
    quitButton = this->findChild<QPushButton*>("QuitButton");
    if (!startButton) {
        qDebug() << "Error: StartButton not found!";
    }
    if (!quitButton) {
        qDebug() << "Error: QuitButton not found!";
    }

}


void MainWindow::on_QuitButton_clicked()
{
    exit(0);
}


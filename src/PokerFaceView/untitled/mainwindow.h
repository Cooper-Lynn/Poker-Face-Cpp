#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void findStartQuitChild();
    void findMenuLabels();
    void viewGameSetUp();


signals:
    void startGameSignal();

private slots:
    void on_StartButton_clicked();

    void on_QuitButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *startButton;
    QPushButton *quitButton;
    QLabel *TitleLabel;
    QLabel *MenuLabel;

};
#endif // MAINWINDOW_H

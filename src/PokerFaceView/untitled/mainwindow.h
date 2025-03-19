#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

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

private slots:
    void on_StartButton_clicked();

    void on_QuitButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *startButton;
    QPushButton *quitButton;

};
#endif // MAINWINDOW_H

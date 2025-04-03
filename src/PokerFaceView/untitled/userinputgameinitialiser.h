#ifndef USERINPUTGAMEINITIALISER_H
#define USERINPUTGAMEINITIALISER_H

#include <QDialog>
#include <QLineEdit>

class GameBaseView;

namespace Ui {
    class userInputGameInitialiser;
}

class userInputGameInitialiser : public QDialog {
    Q_OBJECT

public:
    explicit userInputGameInitialiser(QWidget *parent = nullptr, GameBaseView *gameBaseView = nullptr);

    ~userInputGameInitialiser();


private slots:
    void on_confirmPush_clicked();

    void on_quitPush_clicked();

    std::vector<std::string> getUserInput();

private:
    Ui::userInputGameInitialiser *ui;
    std::vector<std::string> userInput;
    QLineEdit *userLineEdit;
    QLineEdit *aiNumLineEdit;
    GameBaseView *gameView = nullptr;

    void findLineEdits();
};

#endif // USERINPUTGAMEINITIALISER_H

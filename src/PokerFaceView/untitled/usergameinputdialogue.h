#ifndef USERGAMEINPUTDIALOGUE_H
#define USERGAMEINPUTDIALOGUE_H

#include <QDialog>
#include "gamebaseview.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class GameBaseView;

namespace Ui {
class UserGameInputDialogue;
}

class UserGameInputDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit UserGameInputDialogue(QWidget *parent = nullptr, GameBaseView* gameView = nullptr);
    ~UserGameInputDialogue();

    void on_callCheckRButton_clicked();

    void on_raiseRButton_clicked();

    void on_foldRButton_clicked();

    void updateMaxChips(int chips);

    void updateCheckOrCall(std::string result);

    void updatePot(int pot);

    void setCall(int howMuch);

protected:
    void closeEvent(QCloseEvent *event) override;


private:
    Ui::UserGameInputDialogue *ui;
    int action;
    int chips;
    int maxChips;
    GameBaseView *gameView = nullptr;
    QLabel *cashLabel;
    QLabel *potLabel;
    QLabel *raiseLabel;
    QLineEdit *raiseEdit;
    QPushButton *callCheckButton;

private slots:
    void on_buttonBox_accepted();
    std::pair<int, int> getUserInput();
};

#endif // USERGAMEINPUTDIALOGUE_H

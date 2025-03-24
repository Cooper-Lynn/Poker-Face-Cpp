#ifndef GAMEBASEVIEW_H
#define GAMEBASEVIEW_H

#include <GameRunner.hpp>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include "userinputgameinitialiser.h"


class MainGui;

namespace Ui {
class GameBaseView;
}

class GameBaseView : public QWidget
{
    Q_OBJECT

public:
    explicit GameBaseView(QWidget *parent = nullptr, MainGui *mainGui = nullptr);
    ~GameBaseView();

    std::vector<std::string> allowUserSetup();
    void passUserInput(std::vector<std::string> &userInput);
    void setGameRunner(GameRunner& gameRunner);
    void updateHiddenView();
    void updateShownView();
    void startGameRunner();
    void updateCardShownPositions();
    void updatePlayerGui();

    void updateAIGui();

    void updateCardBackPositions();

private:
    Ui::GameBaseView *ui;
    std::unique_ptr<userInputGameInitialiser> userInitialiser;
    MainGui *mainGui = nullptr;
    GameRunner *gameRunner = nullptr;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::string> currentDeck;
    std::vector<std::pair<int, int>> aiPlayerCardPositions = {
        {110, 23},
        {286, 23},
        {465, 23},
        {676, 23},
        {881, 23},
        {1084 ,23}
    };
    std::vector<std::pair<int, int>> aiPlayerNamePositions = {
        {130, 194},
        {313, 194},
        {492, 194},
        {704, 194},
        {903, 194},
        {1112 ,194}
    };

    std::vector<QLabel*> cardLabels;
    std::vector<std::string> userHand;

    QPainter qPaint;
};

#endif // GAMEBASEVIEW_H

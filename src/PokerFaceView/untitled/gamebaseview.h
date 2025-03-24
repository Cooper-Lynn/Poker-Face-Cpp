#ifndef GAMEBASEVIEW_H
#define GAMEBASEVIEW_H

#include <GameRunner.hpp>
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
    void updateCardBackPositions();

private:
    Ui::GameBaseView *ui;
    std::unique_ptr<userInputGameInitialiser> userInitialiser;
    MainGui *mainGui = nullptr;
    GameRunner *gameRunner = nullptr;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::string> currentDeck;
    std::vector<std::pair<int, int>> aiPlayerCardPositions = {
        {110, 20},
        {286, 24},
        {465, 23},
        {676, 23},
        {881, 23},
        {1084 ,24}
    };
    QPainter qPaint;
};

#endif // GAMEBASEVIEW_H

#ifndef GAMEBASEVIEW_H
#define GAMEBASEVIEW_H

#include <QWidget>

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

private:
    Ui::GameBaseView *ui;
    std::unique_ptr<userInputGameInitialiser> userInitialiser;
    MainGui *mainGui = nullptr;
};

#endif // GAMEBASEVIEW_H

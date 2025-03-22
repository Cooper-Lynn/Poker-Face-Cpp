#ifndef USERINPUTGAMEINITIALISER_H
#define USERINPUTGAMEINITIALISER_H

#include <QDialog>

namespace Ui {
class userInputGameInitialiser;
}

class userInputGameInitialiser : public QDialog
{
    Q_OBJECT

public:
    explicit userInputGameInitialiser(QWidget *parent = nullptr);
    ~userInputGameInitialiser();

private:
    Ui::userInputGameInitialiser *ui;
};

#endif // USERINPUTGAMEINITIALISER_H

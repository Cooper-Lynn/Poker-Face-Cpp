#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDialog>

namespace Ui {
class GameView;
}

class GameView : public QDialog
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    Ui::GameView *ui;
};

#endif // GAMEVIEW_H

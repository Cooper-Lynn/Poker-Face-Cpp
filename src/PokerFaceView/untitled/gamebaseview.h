#ifndef GAMEBASEVIEW_H
#define GAMEBASEVIEW_H

#include <QWidget>

namespace Ui {
class GameBaseView;
}

class GameBaseView : public QWidget
{
    Q_OBJECT

public:
    explicit GameBaseView(QWidget *parent = nullptr);
    ~GameBaseView();

private:
    Ui::GameBaseView *ui;
};

#endif // GAMEBASEVIEW_H

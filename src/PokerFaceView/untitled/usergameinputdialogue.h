#ifndef USERGAMEINPUTDIALOGUE_H
#define USERGAMEINPUTDIALOGUE_H

#include <QDialog>

namespace Ui {
class UserGameInputDialogue;
}

class UserGameInputDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit UserGameInputDialogue(QWidget *parent = nullptr);
    ~UserGameInputDialogue();

private:
    Ui::UserGameInputDialogue *ui;
};

#endif // USERGAMEINPUTDIALOGUE_H

#ifndef RACE_GAME_H
#define RACE_GAME_H

#include <QWidget>

namespace Ui {
class race_game;
}

class race_game : public QWidget
{
    Q_OBJECT

public:
    explicit race_game(QWidget *parent = nullptr);
    ~race_game();

private:
    Ui::race_game *ui;
};

#endif // RACE_GAME_H

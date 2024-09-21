#ifndef TANK_GAME_H
#define TANK_GAME_H

#include <QWidget>

namespace Ui {
class tank_game;
}

class tank_game : public QWidget
{
    Q_OBJECT

public:
    explicit tank_game(QWidget *parent = nullptr);
    ~tank_game();

private:
    Ui::tank_game *ui;
};

#endif // TANK_GAME_H

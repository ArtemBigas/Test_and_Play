#include "tank_game.h"
#include "ui_tank_game.h"

tank_game::tank_game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tank_game)
{
    ui->setupUi(this);
}

tank_game::~tank_game()
{
    delete ui;
}

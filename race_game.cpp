#include "race_game.h"
#include "ui_race_game.h"

race_game::race_game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::race_game)
{
    ui->setupUi(this);
}

race_game::~race_game()
{
    delete ui;
}

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <QWidget>
#include "snake.h"
namespace Ui {
class snake_game;
}

class snake_game : public QWidget
{
    Q_OBJECT

public:
    explicit snake_game(QWidget *parent = nullptr);
    ~snake_game();
    int score_1=0;//очки первого игрока
    void startSnakeTimer();


signals:
    void MainWindowRequested();
    void QuestionSnakeRequested();
protected:
    void keyPressEvent(QKeyEvent *) override;  // Переопределяем keyPressEvent
private slots:
    void on_StartPauseButton_clicked();

    void on_ReturnButton_clicked();


private:
    void updateScore();  // Слот для обновления счёта
    void NoupdateScore();

private:
    Ui::snake_game *ui;
    Snake *Snake_widget; // Указатель на пользовательский виджет Snake
    bool firstquestion=true;
};

#endif // SNAKE_GAME_H

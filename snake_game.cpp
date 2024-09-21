#include "snake_game.h"
#include "ui_snake_game.h"
#include <QTimer>
snake_game::snake_game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::snake_game)
{
    ui->setupUi(this);
    // Создаем пользовательский виджет Snake
    Snake_widget = new Snake(this);
    // Проверяем, есть ли уже компоновка у gamearea
    if (ui->gameareawidget->layout() == nullptr) {
        // Если компоновки нет, создаем новую
        QVBoxLayout *layout = new QVBoxLayout();
        ui->gameareawidget->setLayout(layout);  // Устанавливаем компоновку для gamearea
    }

    // Добавляем пользовательский виджет в существующую компоновку
    ui->gameareawidget->layout()->addWidget(Snake_widget);
    // Устанавливаем фокус на пользовательский виджет
    Snake_widget->setFocus();
    connect(Snake_widget, &Snake::scoreUpdated, this, &snake_game::updateScore);
    connect(Snake_widget, &Snake::scoreNoUpdated, this, &snake_game::NoupdateScore);
}

snake_game::~snake_game()
{
    delete ui;
}

void snake_game::updateScore()
{    score_1++;
    // Обновляем отображение счетчика очков
    ui->scorelcd->display(score_1);
    emit QuestionSnakeRequested();
}

void snake_game::NoupdateScore(){emit QuestionSnakeRequested();}

void snake_game::keyPressEvent(QKeyEvent *e) {
    // Передача события в пользовательский виджет
    Snake_widget->keyPressEvent(e);
}

void snake_game::on_StartPauseButton_clicked()
{
    QString buttonText = ui->StartPauseButton->text();

    if (buttonText == "Start") {
         Snake_widget->startSnakeTimer();
        ui->StartPauseButton->setText("Pause");
    } else if (buttonText == "Pause") {
        Snake_widget->startSnakeTimer();  // Остановите таймер, если нажат Pause
        ui->StartPauseButton->setText("Start");
    }
    if(firstquestion==true){emit QuestionSnakeRequested();};
    firstquestion=false;
}
void snake_game::startSnakeTimer()
{
  Snake_widget->startSnakeTimer();  // Вызываем метод из Snake для запуска таймера
}

void snake_game::on_ReturnButton_clicked()
{
    emit MainWindowRequested();
}


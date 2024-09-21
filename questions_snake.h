#ifndef QUESTIONS_SNAKE_H
#define QUESTIONS_SNAKE_H

#include <QWidget>
#include "MainWindow.h"

namespace Ui {
class questions_snake;
}

class questions_snake : public QWidget
{
    Q_OBJECT

public:
    explicit questions_snake(QWidget *parent = nullptr);  //конструктор теперь будет ждать переменную с именем файла
    ~questions_snake();

signals:
    void Snake_gameRequested();
      // void trueVariant(int variant);

private slots:
    void on_OKButton_clicked();
 public slots:
    //функция заполняет виджеты класса текстом,срабатывает через сигнал в Dialog.cpp в момент активации виджета.
     //int index - номер страницы виджета, который передает сигнал StackedWidget::currentChanged
    void startwork(int index);


private:
    Ui::questions_snake *ui;
    int num_Qs=0;//номер строки текущего вопроса

    std::vector<QString>ColorsQ= {"red", "yellow", "green"};

};
extern int trueVariant;//правильный вариант(изначально хотел через сигнал в Dialog.cpp, но не сработало)
#endif // QUESTIONS_SNAKE_H

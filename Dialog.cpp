#include "Dialog.h"
#include "ui_Dialog.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->Mainwindow, &MainWindow::snake_gameRequested,this, &Dialog::setsnake_game);
    connect(ui->Snake_game, &snake_game::MainWindowRequested,this, &Dialog::ReturnMainWindow);
    connect(ui->Snake_game, &snake_game::QuestionSnakeRequested,this, &Dialog::setquestion_snake);
    connect(ui->Questions_snake, &questions_snake::Snake_gameRequested,this, &Dialog::setsnake_game);
    //сигнал запуска функции startwork(),когда виджет ui->Questions_snake будет активен
     connect(ui->stackedWidget, &QStackedWidget::currentChanged, ui->Questions_snake, &questions_snake::startwork);
     // connect(ui->Questions_snake, &questions_snake::trueVariant, ui->SnakeWidget, &Snake::getTrueVariant);
     connect(ui->Mainwindow, &MainWindow::aboutRequested,this, &Dialog::setabout);
     connect(ui->About, &about::MainWindowRequested,this, &Dialog::ReturnMainWindow);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setsnake_game()
{
    QWidget* widget = findChild<QWidget*>("Snake_game");
    ui->stackedWidget->setCurrentWidget(widget);
}

void Dialog::ReturnMainWindow(){
    QWidget* widget = findChild<QWidget*>("Mainwindow");
    ui->stackedWidget->setCurrentWidget(widget);
}
void Dialog::setquestion_snake(){
    QWidget* widget = findChild<QWidget*>("Questions_snake");
    ui->stackedWidget->setCurrentWidget(widget);
}

void Dialog::setabout(){
    QWidget* widget = findChild<QWidget*>("About");
    ui->stackedWidget->setCurrentWidget(widget);
}

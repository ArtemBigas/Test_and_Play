#include "MainWindow.h"
#include "ui_MainWindow.h"

QString filename;//определяем глобальную переменную
int lineNumber=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ExitButton_clicked()
{
    qApp->exit();
}


void MainWindow::on_LaunchButton_clicked()
{
    if (ui->radio_1player->isChecked())
    {
        players=1;
    };
    if(ui->radio_Snake->isChecked()){game = 1;}
    else if(ui->radio_Tank->isChecked()){game = 2;}
    else if(ui->radio_Racing->isChecked()){game=3;};

    if(players==0){        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("I need at least one player"));};

    if(game==0){        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("I wait your game"));};

    QTextStream out(stdout);
    //QCoreApplication::applicationDirPath() возвращает путь к директории, в которой находится исполняемый файл.
      filename = QCoreApplication::applicationDirPath() + "/tests/" + ui->Title_Edit->text()+ ".txt";
    QFile test(filename);// Создаем объект
    // Убедимся, что директория tests существует, если нет - ошибка
    QDir dir(QCoreApplication::applicationDirPath() + "/tests");
    if (!dir.exists()) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("There is not folder <<tests>>."));
    };
    if(!test.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Cannot open file for reading"));

    }
    else{if(players==1 && game == 1){
            emit snake_gameRequested();     QTextStream in(&test);
        //считаем количество строк в документе
        while (!in.atEnd()){
            QString line = in.readLine();// метод readLine() считывает одну строку из потока, без него цикл бесконечный
            lineNumber++;}
        test.close();}  // Закрываем файл
        };

    };


    void MainWindow::on_AboutButton_clicked()
    {
      emit aboutRequested();
    }


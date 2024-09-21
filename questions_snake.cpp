#include "questions_snake.h"
#include "ui_questions_snake.h"

int trueVariant;

questions_snake::questions_snake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::questions_snake)
{
    ui->setupUi(this);
    ui->numRed->setStyleSheet("color: red;");//изменяем цвет текста красного варианта
    ui->numYellow->setStyleSheet("color: yellow;");
    ui->numGreen->setStyleSheet("color: green;");
}

questions_snake::~questions_snake()
{
    delete ui;
}

void questions_snake::startwork(int index){
    // 3-индекс questions_snake в StakeWidget,иначе функция будет срабатывать при каждой смене виджета
    if(index==4)
    {
        QFile test(filename);
        // Создаем входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
        test.open(QIODevice::ReadOnly);//инициализируем test
        QTextStream in(&test);
        if (num_Qs<lineNumber)
        {
            for(int i=0;i<num_Qs;i++){in.readLine();}//пропуск прошлых вопросов
            QString lineq = in.readLine();
            QStringList partsQ = lineq.split("_");
            ui->numberQ->setText(partsQ[0]);
            ui->textQ->setText(partsQ[1]);
            //варианты ответов
            QString lineRed = in.readLine();
            QStringList partsRed = lineRed.split("_");
            ui->numRed->setText("RED");
            ui->textRed->setText(partsRed[1]);
            if(partsRed[2]=="true"){/*emit trueVariant(1);*/trueVariant=1;};
            QString lineYellow = in.readLine();
            QStringList partsYellow = lineYellow.split("_");
            ui->numYellow->setText("YELLOW");
            ui->textYellow->setText(partsYellow[1]);
            if(partsYellow[2]=="true"){/*emit trueVariant(2);*/trueVariant=2;};
            QString lineGreen = in.readLine();
            QStringList partsGreen = lineGreen.split("_");
            ui->numGreen->setText("GREEN");
            ui->textGreen->setText(partsGreen[1]);
            if(partsGreen[2]=="true"){/*emit trueVariant(3);*/trueVariant=3;};
        }
        test.close();  // Закрываем файл
        num_Qs=num_Qs+4;
    }

}

void questions_snake::on_OKButton_clicked()
{
    emit Snake_gameRequested();
}


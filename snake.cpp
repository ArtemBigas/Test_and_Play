#include <QPainter>
#include <QTime>
#include <cmath> // Для использования sqrt и pow
#include <QMessageBox>
#include "questions_snake.h"
#include "snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {
    // Устанавливаем сильную политику фокуса, чтобы получать события клавиатуры
    setFocusPolicy(Qt::StrongFocus);
    // Получаем текущее разрешение экрана
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
     B_WIDTH = screenGeometry.width()/4;   // Ширина экрана
     B_HEIGHT = screenGeometry.height()/4; // Высота экрана
     DOT_SIZE=screenGeometry.height()/72;//вроде оптимальный размер
    setStyleSheet("background-color:white;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    pause=true;
    resize(B_WIDTH, B_HEIGHT);//размер игрового поля-половина экрана
    // Инициализируем векторы x и y с размером ALL_DOTS
    ALL_DOTS = (B_WIDTH*B_HEIGHT)/(DOT_SIZE*DOT_SIZE);
    x.resize(ALL_DOTS);
    y.resize(ALL_DOTS);
    loadImages();
    initGame();
}

void Snake::loadImages() {//тело змеи
    //Если вставлять как картинки
    /* dot.load("green.jpg");
    head.load("red.png");
    apple.load("apple.png");*/

    //Если заполнить как квадрат
    dot = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    dot.fill(Qt::darkGreen);
    head = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    head.fill(Qt::darkGreen);
    red = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    red.fill(Qt::red);
    yellow = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    yellow.fill(Qt::yellow);
    green = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    green.fill(Qt::green);

}

void Snake::initGame() {
    //создание змеи
    dots = 3;
    //Змею рисуем с хвоста
    for (int z = dots; z >= 0; z--) {
        int i=0;
        x[z] = DOT_SIZE*i;
        y[z] = B_HEIGHT/2;
        i++;
    }

    locateRedApple();//определяем позицию яблока
    locateYellowApple();//определяем позицию яблока
    locateGreenApple();//определяем позицию яблока
}

void Snake::startSnakeTimer()//проверки состояния таймера нужны из-за некорректного переключения,таймер может останавливаться только с второго раза
{
    if (pause) {
        if (timerId == 0) {  // Проверьте, что таймер не запущен
            timerId = startTimer(DELAY);
        }
        pause = false;
    } else {
        killTimer(timerId);
        timerId = 0;  // Сбрасываем значение timerId, чтобы не использовать его повторно
        pause = true;
    }
}
void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {
    QPainter qp(this);
// Масштабируем объекты в зависимости от текущего размера окна
    if (inGame) {
        float scaleX = (float) width() / B_WIDTH;
        float scaleY = (float) height() / B_HEIGHT;
        // Масштабируем яблоко
        int red_x_scaled = red_x * scaleX;
        int red_y_scaled = red_y * scaleY;
        int yellow_x_scaled = yellow_x * scaleX;
        int yellow_y_scaled = yellow_y * scaleY;
        int green_x_scaled = green_x * scaleX;
        int green_y_scaled = green_y * scaleY;
        int dot_size_scaled = DOT_SIZE * scaleX;
        //qp.drawImage(apple_x, apple_y, apple);
        qp.drawImage(red_x_scaled, red_y_scaled, red.scaled(dot_size_scaled, dot_size_scaled));
        qp.drawImage(yellow_x_scaled, yellow_y_scaled, yellow.scaled(dot_size_scaled, dot_size_scaled));
        qp.drawImage(green_x_scaled, green_y_scaled, green.scaled(dot_size_scaled, dot_size_scaled));
         // Масштабируем змейку
        for (int z = 0; z < dots; z++) {
            int x_scaled = x[z] * scaleX;
            int y_scaled = y[z] * scaleY;

            if (z == 0) {
                 //qp.drawImage(x[z], y[z], head);
                qp.drawImage(x_scaled, y_scaled, head.scaled(dot_size_scaled, dot_size_scaled));
                qp.setPen(Qt::black);//цвет линии
                 //qp.drawRect(x[z], y[z], dot.width(), dot.height());//рисуем линию(координаты ячейки, ширина и высота её)
                qp.drawRect(x_scaled, y_scaled, dot_size_scaled, dot_size_scaled);
            } else {
                 //qp.drawImage(x[z], y[z], dot);
                qp.drawImage(x_scaled, y_scaled, dot.scaled(dot_size_scaled, dot_size_scaled));
                qp.setPen(Qt::black);
                //qp.drawRect(x[z], y[z], dot.width(), dot.height());
                qp.drawRect(x_scaled, y_scaled, dot_size_scaled, dot_size_scaled);
            }
        }
    } else {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

 // void Snake::getTrueVariant(int variant){
 //     trueVariant=variant;    QMessageBox::information(this, "Debug", "trueVariant set to: " + QString::number(trueVariant));
 // };


//проверяем столкновение с яблоком
void Snake::checkApple() {
    if ((x[0] == red_x) && (y[0] == red_y))//Если голова сталкивается с яблоком
    {
        if(trueVariant==1){dots++;    emit scoreUpdated();/*QMessageBox::information(this, "Debug", "Send trueVariant: " + QString::number(trueVariant));*/}//отправляем сигнал
        else{emit scoreNoUpdated();};//отправляем сигнал
        locateRedApple();//случайным образом позиционируем новое яблоко
        locateYellowApple();
        locateGreenApple();
    }
    else if ((x[0] == yellow_x) && (y[0] == yellow_y)) {
        if(trueVariant==2){dots++;
            emit scoreUpdated();}//отправляем сигнал
        else{emit scoreNoUpdated();};//отправляем сигнал
        locateRedApple();
        locateYellowApple();
        locateGreenApple();
    }
    else if ((x[0] == green_x) && (y[0] == green_y)) {
        if(trueVariant==3){dots++;
            emit scoreUpdated();}//отправляем сигнал
        else{emit scoreNoUpdated();};//отправляем сигнал
        locateRedApple();
        locateYellowApple();
        locateGreenApple();
    }
}

void Snake::move() {
    //определяет, что вторая «часть» движется туда, где была первая, третья — туда, где была вторая и т.д
    for (int z = dots; z > 0; z--) {//изменение начинается с хвоста
        x[z] = x[(z - 1)];//координата x части 3, становится равна координате x части 2
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;//координата по шкале х становится меньше на размер тела
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {//столкновения

    for (int z = dots; z > 0; z--) {//с своей частью

        // if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {//если координата совпадет с координатой любой её части
        //     inGame = false;
        // }
    }
    //если змея столкнется с стенкой,в комментариях вариант без стен
    if (y[0] >= B_HEIGHT) {
        //inGame = false;
        y[0] = DOT_SIZE;
    }

    if (y[0] < 0) {
        //inGame = false;
        y[0]= B_HEIGHT-DOT_SIZE;
    }

    if (x[0] >= B_WIDTH) {
        //inGame = false;
        x[0] = DOT_SIZE;
    }

    if (x[0] < 0) {
        //inGame = false;
        x[0]= B_WIDTH-DOT_SIZE;
    }

    if(!inGame) {//если inGame==false, таймер заканчивается
        killTimer(timerId);
    }
}

// Функция для проверки расстояния между яблоками
bool Snake::isTooClose(int x1, int y1, int x2, int y2, int minDistance) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distanceSquared = dx * dx + dy * dy;
    return distanceSquared < (minDistance * minDistance);
}

void Snake::locateRedApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int RAND_POS_X = B_WIDTH / DOT_SIZE;
    int RAND_POS_Y = B_HEIGHT / DOT_SIZE;

    int r_x, r_y;
    bool validPosition = false;
     // Проверка, чтобы красное яблоко не совпадало с какой-либо частью змеи
    while (!validPosition) {
        r_x = qrand() % RAND_POS_X;
        r_y = qrand() % RAND_POS_Y;

        red_x = r_x * DOT_SIZE;
        red_y = r_y * DOT_SIZE;

        validPosition = true;
        for (int i = 0; i < dots; ++i) {
            if (x[i] == red_x && y[i] == red_y) {
                validPosition = false;
                break;
            }
        }
    }
 // Дополнительная проверка, чтобы яблоко точно оставалось внутри поля
    if (red_x >= B_WIDTH) {
        red_x = B_WIDTH - DOT_SIZE;
    }
    if (red_y >= B_HEIGHT) {
        red_y = B_HEIGHT - DOT_SIZE;
    }
}

void Snake::locateYellowApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int RAND_POS_X = B_WIDTH / DOT_SIZE;
    int RAND_POS_Y = B_HEIGHT / DOT_SIZE;

    int r_x, r_y;
    bool validPosition = false;
    int minDistance = DOT_SIZE * 2; // Минимальное расстояние между яблоками

    while (!validPosition) {
        r_x = qrand() % RAND_POS_X;
        r_y = qrand() % RAND_POS_Y;

        yellow_x = r_x * DOT_SIZE;
        yellow_y = r_y * DOT_SIZE;

        validPosition = true;

        // Проверка на перекрытие с красным яблоком и змейкой
        if (!isTooClose(yellow_x, yellow_y, red_x, red_y, minDistance)) {
            for (int i = 0; i < dots; ++i) {
                if (x[i] == yellow_x && y[i] == yellow_y) {
                    validPosition = false;
                    break;
                }
            }
        } else {
            validPosition = false;
        }
    }

    if (yellow_x >= B_WIDTH) {
        yellow_x = B_WIDTH - DOT_SIZE;
    }
    if (yellow_y >= B_HEIGHT) {
        yellow_y = B_HEIGHT - DOT_SIZE;
    }
}

void Snake::locateGreenApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int RAND_POS_X = B_WIDTH / DOT_SIZE;
    int RAND_POS_Y = B_HEIGHT / DOT_SIZE;

    int r_x, r_y;
    bool validPosition = false;
    int minDistance = DOT_SIZE * 2; // Минимальное расстояние между яблоками

    while (!validPosition) {
        r_x = qrand() % RAND_POS_X;
        r_y = qrand() % RAND_POS_Y;

        green_x = r_x * DOT_SIZE;
        green_y = r_y * DOT_SIZE;

        validPosition = true;

        // Проверка на перекрытие с красным и желтым яблоком
        if (!isTooClose(green_x, green_y, red_x, red_y, minDistance) &&
            !isTooClose(green_x, green_y, yellow_x, yellow_y, minDistance)) {
            for (int i = 0; i < dots; ++i) {
                if (x[i] == green_x && y[i] == green_y) {
                    validPosition = false;
                    break;
                }
            }
        } else {
            validPosition = false;
        }
    }

    if (green_x >= B_WIDTH) {
        green_x = B_WIDTH - DOT_SIZE;
    }
    if (green_y >= B_HEIGHT) {
        green_y = B_HEIGHT - DOT_SIZE;
    }
}
void Snake::timerEvent(QTimerEvent *e) {//игровой цикл

    Q_UNUSED(e);

    if (inGame) {//если inGame==true

        checkApple();//проверяем столкновение с яблоком
        checkCollision();//проверяем столкновение с стеной или с телом
        move();//двигаемся
    }

    update();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();//извлекаем числовое значение int key из ивента e

    if ((key == Qt::Key_Left) && (!rightDirection)) {//если есть ивент Key_Left, и rightDirection == false(чтобы нельзя было повернуть на 180 градусов)
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(e);
}

#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QScreen>//расчет разрешения экрана
class Snake : public QWidget {

    Q_OBJECT
public:
    Snake(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);

    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void startSnakeTimer();
public slots:
    // void getTrueVariant(int variant);
private:
    QImage dot;
    QImage head;
    QImage red;
    QImage yellow;
    QImage green;

    //размер игрового поля
    int B_WIDTH;
    int B_HEIGHT;

    int DOT_SIZE;//размер яблока и тела змеи
    int ALL_DOTS;//максимальное количество возможных точек на доске размером 10х10 пикселей((300*300)/(10*10))
    int RAND_POS;//используется для вычисления случайной позиции яблока
    static const int DELAY = 300;//скорость игры

    int timerId;
    int dots;
    //координаты яблок
    int red_x;
    int red_y;
    int yellow_x;
    int yellow_y;
    int green_x;
    int green_y;
    //координаты (x;y) всех «частей» тела змеи
    std::vector <int> x;
    std::vector <int> y;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;
    bool pause;


    void loadImages();
    void initGame();
    bool isTooClose(int x1, int y1, int x2, int y2, int minDistance);
    void locateRedApple();
    void locateYellowApple();
    void locateGreenApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &);

signals:
    void scoreUpdated();//сигнал в snake_game для обновления счета
    void scoreNoUpdated();//сигнал в snake_game что счет не изменился
};

#endif // SNAKE_H

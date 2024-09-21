#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void snake_gameRequested();
    void tank_gameRequested();
    void race_gameRequested();
    void aboutRequested();


private slots:
    void on_ExitButton_clicked();

    void on_LaunchButton_clicked();

    void on_AboutButton_clicked();

private:
    Ui::MainWindow *ui;
    int players = 0;//переменная количества игроков
    int game = 0;//переменная выбора игры
};
extern QString filename;//extern - теперь глобальная переменная только здесь, но в cpp её надобудет определить
extern int lineNumber;//номер линии в цикле

#endif // MAINWINDOW_H

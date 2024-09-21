#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();
signals:
    void MainWindowRequested();
private slots:
    void on_returnButton_clicked();
private:
    Ui::about *ui;
};

#endif // ABOUT_H

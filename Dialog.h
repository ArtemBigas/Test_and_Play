#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void ReturnMainWindow();
    void setsnake_game();
    void setquestion_snake();
    void setflinames_g();
    void setabout();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

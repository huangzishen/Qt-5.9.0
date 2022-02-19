#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>
namespace Ui {
class MyButton;
}

class MyButton : public QPushButton
{
    Q_OBJECT

public:
//    explicit MyButton(QWidget *parent = 0);

    MyButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;

    QString pressImgPath;


    // 弹跳效果
    void tantiao();

    // 重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


    ~MyButton();

private:
    Ui::MyButton *ui;
};

#endif // MYBUTTON_H

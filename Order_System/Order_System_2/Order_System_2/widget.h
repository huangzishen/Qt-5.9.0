#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include<QDebug>
#include<QLabel>
#include<QPushButton>
#include<QPainter>
#include <QFont>
#include <QDir>
#include <QFile>
#include <QMessageBox>

#include "ui_widget.h"
#include "login.h"
#include "manager.h"
#include "student.h"
#include "teacher.h"
#include "files.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    // 重写,登入界面背景加载
    void paintEvent(QPaintEvent *);

    // 检查学生，教师，管理员，订单文件是否存在
    void is_file_exist();



    ~Widget();

public:

    // 保存订单文件里的数据
    // int为记录下标，QMap<QString,QString>为数据
    QMap<int,QMap<QString,QString>> order_data;

    // 当前的预约记录最大下标
    int m_order_num;

    // 剩余的机房信息
    int com_1;// 一号机房
    int com_2;// 二号机房
    int com_3;// 三号机房

signals:
    // 当登入成功时进入各自的操作界面
    void enter_student(QString id, QString name,QString password);
    void enter_teacher(QString id, QString name,QString password);
    void enter_manager(QString name,QString password);

public slots:
    // 进入操作界面的槽函数
    void student(QString id, QString name,QString password);
    void teacher(QString id, QString name,QString password);
    void manager(QString name,QString password);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

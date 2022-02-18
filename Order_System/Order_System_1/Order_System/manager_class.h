#ifndef MANAGER_CLASS_H
#define MANAGER_CLASS_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QMap>
#include <QVector>
#include "login.h"
class Manager_Class:public QMainWindow
{
    Q_OBJECT
public:
//    explicit Manager_Class(QWidget * parent = 0);
    Manager_Class(QString m_name,QString m_password);

    void paintEvent(QPaintEvent *event);

    // 添加账号
    void add_people();

    // 查看所有人账号信息
    void check_info();

    // 查看所有人的预约信息
    void check_order();

    // 添加账号的窗口 1:学生，2:老师
    void add_qwidget(int p_type);
    
    


public:
    QString name;
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * m_order_data;
    // 当前的预约记录数量
    int m_order_num;

signals:
    // 自定义信号，返回初始界面
    void back_first_scence();
};

#endif // MANAGER_CLASS_H

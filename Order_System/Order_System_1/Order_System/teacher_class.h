#ifndef TEACHER_CLASS_H
#define TEACHER_CLASS_H

#include <QMainWindow>
#include <QString>
#include "login.h"
#include <QMap>
#include <QVector>
class Teacher_Class:public QMainWindow
{
    Q_OBJECT
public:
//    explicit Teacher_Class(QWidget * parent = 0);
    Teacher_Class(QString m_id,QString m_name,QString m_password);

    void paintEvent(QPaintEvent *event);

    // 查看所有预约
    void check_all_order();

    // 审核预约
    void agree_order();
    
    // 保存审核预约的结果
    void Save_order();

public:
    QString id;// 学生的学号，或教师的职工号
    QString name;// 学生的姓名或教师的姓名
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * t_order_data;
    // 当前的预约记录数量
    int m_order_num;


signals:
    // 自定义信号，返回初始界面
    void back_first_scence();
};

#endif // TEACHER_CLASS_H

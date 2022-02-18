#ifndef STUDENT_CLASS_H
#define STUDENT_CLASS_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <QVector>
#include "login.h"
class Student_Class:public QMainWindow
{
    Q_OBJECT
public:
//    explicit Student_Class(QWidget * parent = 0);
    Student_Class(QString m_id,QString m_name,QString m_password);

    void paintEvent(QPaintEvent *event);


    // 学生申请预约
    void apply_order();
    // 将预约信息写入文件
    void write_s_file(QString week,QString day,QString pos,QWidget * widget);

    // 查看自身预约
    void check_self_order();

    // 查看所有预约
    void check_all_order();

    // 取消预约
    void cancel_order();

    // 保存预约信息
   void Save_order();
    
    


public:
    QString id;// 学生的学号，或教师的职工号
    QString name;// 学生的姓名或教师的姓名
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * s_order_data;
    // 当前的预约记录数量
    int m_order_num;



signals:
    // 自定义信号，返回初始界面
    void back_first_scence();
};

#endif // STUDENT_CLASS_H

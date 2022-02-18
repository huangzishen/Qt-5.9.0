#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QPoint>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QTabWidget>
#include <QFont>
#include <QMessageBox>
#include <QMenuBar>

#include "files.h"
class Student : public QWidget
{
    Q_OBJECT
public:
//    explicit Student(QWidget *parent = nullptr);
    Student(QString m_id,QString m_name,QString m_password);

    void paintEvent(QPaintEvent *event);

    // 学生申请预约
    void apply_order();

    // 查看自身预约
    void check_self_order();

    // 查看所有预约
    void check_all_order();

    // 取消预约
    void cancel_order();

    // 保存预约信息
   void Save_order(QString m_week,QString m_day,QString m_pos, QWidget * parent);

   // 保存取消预约后的信息
   void Save_order();


public:
    QString id;// 学生的学号
    QString name;// 学生的姓名
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * s_order_data;

    // 剩余的机房信息
    int *com_1;// 一号机房
    int *com_2;// 二号机房
    int *com_3;// 三号机房


signals:
    // 自定义信号，返回初始界面
    void back_first_scence();

public slots:
};

#endif // STUDENT_H

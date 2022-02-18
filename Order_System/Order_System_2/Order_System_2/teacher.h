#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
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
class Teacher : public QWidget
{
    Q_OBJECT
public:
//    explicit Teacher(QWidget *parent = nullptr);
    Teacher(QString m_id,QString m_name,QString m_password);

    void paintEvent(QPaintEvent *event);

    // 查看所有预约
    void check_all_order();

    // 审核预约
    void agree_order();

    // 保存审核预约的结果
    void Save_order();

public:
    QString id;//教师的职工号
    QString name;//教师的姓名
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * t_order_data;

    // 剩余的机房信息
    int *com_1;// 一号机房
    int *com_2;// 二号机房
    int *com_3;// 三号机房

signals:
    // 自定义信号，返回初始界面
    void back_first_scence();

public slots:
};

#endif // TEACHER_H

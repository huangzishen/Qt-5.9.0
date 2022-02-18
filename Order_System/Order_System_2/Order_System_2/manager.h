#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <QMap>
#include <QFile>
#include <iterator>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QTextEdit>

#include "files.h"
class Manager : public QWidget
{
    Q_OBJECT
public:
//    explicit Manager(QWidget *parent = nullptr);

    Manager(QString m_name,QString m_password);

    void paintEvent(QPaintEvent *e);

    // 添加账号
    void add_people();

    // 添加账号的窗口 1:学生，2:老师
    void add_qwidget(int p_type);

    // 查看所有人账号信息
    void check_info();

    // 查看所有人的预约信息
    void check_order();

    // 清空预约记录
    void clear_order();

    // 加载老师学生的账号信息
    void login_infos();

    // 保存添加进来的信息
    void save_info(int p_type, QString m_id,QString m_name, QString m_password, QWidget * parent);

    // 更新添加进来的信息 1，学生 2，教师
    void update_infos(int p_type, QString m_id, QString m_name, QString m_password, QWidget * parent);


public:
    QString name;
    QString password;

    // 登入成功过后，将订单的数据地址也传过来
    QMap<int,QMap<QString,QString>> * m_order_data;

    // 是否添加账号成功
    bool add_successed;

    QMap<int,QMap<QString,QString>> teachers_infos;// 保存老师的账号信息
    QMap<int,QMap<QString,QString>> students_infos;// 保存学生的账号信息

    // 判断添加账号是否成功
    bool save_info_successed;

signals:

    // 自定义信号，返回初始界面
    void back_first_scence();

    void back_login();

public slots:
};

#endif // MANAGER_H

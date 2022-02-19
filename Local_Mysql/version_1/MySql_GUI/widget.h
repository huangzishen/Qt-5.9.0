#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QThread>
#include "mythread.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

    void deal_thread_done();

    ~Widget();

signals:
    // 启动子线程的信号
    void start_thread(QSqlDatabase * db,QString table);

    // 停止线程的信号
    void stop_thread();




private slots:
    void on_login_btn_clicked();

    void on_close_btn_clicked();

    void on_add_btn_clicked();

    void on_drop_btn_clicked();

    void on_modifiy_btn_clicked();

    void on_select_btn_clicked();


    void on_table_btn_clicked();

private:
    Ui::Widget *ui;

    QSqlDatabase m_db;

    QString table_name;

    // 保存表的结构，<列名，类型>
    QMap<QString,QString> * table_type;

    // 线程处理函数
    MyThread * thread_fun;

    // 子线程
    QThread * thread;

};

#endif // WIDGET_H

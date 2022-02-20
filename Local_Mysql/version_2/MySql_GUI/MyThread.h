#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
// 子线程，用来连接数据库后获取表的结构
class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    // 线程处理函数
    void table_struct(QSqlDatabase * db,QString table);

public:
    // 保存表的结构，<列名，类型>
    QMap<QString,QString> table_type;
signals:

    // 子线程完成信号
    void isDone();

public slots:
};

#endif // THREAD_H

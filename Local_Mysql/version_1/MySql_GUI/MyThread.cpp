#include "mythread.h"
#include <QThread>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::table_struct(QSqlDatabase * db,QString table)
{
    // 获取数据库当前的表的结构
    qDebug() << "子线程：" << QThread::currentThread();
//    qDebug() << "当前的数据库:" << db->database();

    // 在子线程中新建连接数据库
    QSqlDatabase new_db = QSqlDatabase::addDatabase(db->driverName(),"sub");
    new_db.setHostName(db->hostName());
    new_db.setPort(db->port());
    new_db.setPassword(db->password());
    new_db.setUserName(db->userName());
    new_db.setDatabaseName(db->databaseName());

    // 子线程打开数据库
    if(new_db.open())
    {
//        qDebug() << "子线程打开数据库成功！";
        QSqlQuery query1 = QSqlQuery(new_db);
        // 字段个数
        int cls_num = 0;

        // 执行 表结构 SQL
        if(query1.exec(QString("desc %1;").arg(table)))
        {
            cls_num = query1.size();
//            qDebug() << cls_num;

            while(query1.next())
            {
                this->table_type.insert(query1.value(0).toString(),query1.value(1).toString());
//                qDebug() << query1.value(0).toString() << " " << query1.value(1).toString();
            }
        }

    }


    // 关闭子线程的数据库
    new_db.close();
//    new_db.removeDatabase("sub");

    emit isDone();
}

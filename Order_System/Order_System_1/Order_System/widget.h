#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QVector>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    // 重写,登入界面背景加载
    void paintEvent(QPaintEvent *event);

    // 保存订单文件里的数据
    // int为记录下标，QMap<QString,QString>为数据
    QMap<int,QMap<QString,QString>> order_data;
    // 当前的预约记录数量
    int m_order_num;

    // 检查学生，教师，管理员，订单文件是否存在
    void is_file_exist();

    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

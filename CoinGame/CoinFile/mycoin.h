#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QString>
#include<QTimer>
class MyCoin:public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);

    // 改变标志的函数
    void changFlag();


    QTimer *time1;// 正面翻反面的定时器
    QTimer *time2;// 反面翻正面的定时器
    int min = 1;// 图片编号的最小值
    int max = 8;// 图片编号的最大值


    // 金币的属性
    int posX;// x坐标位置
    int posY;// y坐标位置
    bool flag;// // 正反标志


    bool isAnimation = false;// 判断每次翻转的动画是否完成

    void mousePressEvent(QMouseEvent *e);// 重写按下按钮，每次翻转完再翻转

    bool is_win;

};

#endif // MYCOIN_H

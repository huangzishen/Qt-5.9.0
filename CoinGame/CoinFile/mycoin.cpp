#include "mycoin.h"
#include<QDebug>
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        qDebug() << QString("图片加载失败： %1").arg(btnImg);
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    this->is_win = false;

    // 初始化定时器
    this->time1 = new QTimer(this);
    this->time2 = new QTimer(this);

    // 监听正面翻反面的信号
    connect(this->time1,this->time1->timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        // 判断 如果翻完了，将min充值为1
        if(this->min > this->max)
        {
            this->min = 1;
            // 翻转动画完成
            this->isAnimation = false;
            this->time1->stop();
        }
    });

    // 监听反面翻正面的信号
    connect(this->time2,this->time2->timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        // 判断 如果翻完了，将max重置为8
        if(this->max < this->min)
        {
            this->max = 8;
            // 翻转动画完成
            this->isAnimation = false;
            this->time2->stop();
        }
    });



}


void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->is_win)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

void MyCoin::changFlag()
{
    // 如果是正面就翻成反面
    if(this->flag)
    {
        // 开启正面翻反面的定时器
        this->time1->start(30);
        // 开始做动画
        this->isAnimation = true;
        this->flag = false;
    }
    else
    {
        // 开启反面翻正面的定时器
        this->time2->start(30);
        // 开始做动画
        this->isAnimation = true;
        this->flag = true;
    }
}

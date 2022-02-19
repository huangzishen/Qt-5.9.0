#include "mybutton.h"
#include "ui_mybutton.h"

//MyButton::MyButton(QWidget *parent) :
//    QPushButton(parent),
//    ui(new Ui::MyButton)
//{
//    ui->setupUi(this);
//}

MyButton::MyButton(QString normalImg,QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    // 设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    // 设置图标
    this->setIcon(pix);

    // 设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyButton::tantiao()
{
    // 向下弹起
    // 创建动态对象
    QPropertyAnimation * animation_1 = new QPropertyAnimation(this,"geometry");
    // 设置动画时间间隔
    animation_1->setDuration(200);

    // 起始位置
    animation_1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    // 结束位置
    animation_1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    // 设置弹跳曲线
    animation_1->setEasingCurve(QEasingCurve::OutBounce);

    // 执行动画
    animation_1->start();

    // 向上弹起
    // 创建动态对象
    QPropertyAnimation * animation_2 = new QPropertyAnimation(this,"geometry");

    // 设置动画时间间隔
    animation_2->setDuration(200);

    // 起始位置
    animation_2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    // 结束位置
    animation_2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    // 设置弹跳曲线
    animation_2->setEasingCurve(QEasingCurve::OutBounce);

    // 执行动画
    animation_2->start();
    delete animation_1,animation_2;// 防止多次点击造成堆区积累，用完就释放

}



void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        // 设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        // 设置图标
        this->setIcon(pix);

        // 设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }


    // 让父类执行其他的鼠标操作
    return QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        // 设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        // 设置图标
        this->setIcon(pix);

        // 设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }


    // 让父类执行其他的鼠标操作
    return QPushButton::mouseReleaseEvent(e);
}

MyButton::~MyButton()
{
    delete ui;
}

#include "mainscence.h"
#include "ui_mainscence.h"
#include "mybutton.h"
#include <QTimer>
#include <QSound> // 多媒体模块
MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);

    // 配置主场景
    this->setWindowFlag(Qt::Window);
    // 设置固定大小
    this->setFixedSize(320,588);

    // 设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("翻金币主场景");

    // 准备开始按钮的音效
    QSound * startsound = new QSound(":/res/TapButtonSound.wav",this);


    connect(ui->action1,&QAction::triggered,[=](){
        this->close();
    });



    // 开始按钮
    MyButton * startBtn = new MyButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5,this->height() * 0.7);

    // 实例化 选择关卡场景
    this->chooseScene = new ChooseLevelSence;

    // 监听选择关卡的返回按钮的信号
    connect(chooseScene,chooseScene->choosesceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();// 重新显示主场景
    });


    connect(startBtn,startBtn->clicked,[=](){
//        qDebug() << "点击开始了";
        // 开始播放音效
        startsound->play();

        // 做弹跳特效
        startBtn->tantiao();

        // 延时操作，0.5秒
        QTimer::singleShot(200,this,[=](){
            // 设置choosescene场景的位置
            chooseScene->setGeometry(this->geometry());
            // 进入到关卡选择界面
            // 将自身隐藏,进入到关卡场景
            this->hide();
            chooseScene->show();
        });


    });

}


void MainScence::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 画背景上的图标
    pix.load(":/res/Title.png");

    // 缩放图片
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);

    painter.drawPixmap(10,30,pix);

}

MainScence::~MainScence()
{
    delete ui;
}

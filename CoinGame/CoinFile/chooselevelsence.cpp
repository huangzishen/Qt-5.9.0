#include "chooselevelsence.h"

ChooseLevelSence::ChooseLevelSence(QWidget * parent) : QMainWindow(parent)
{
    // 配置选择关卡场景
    this->setFixedSize(320,588);

    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle("选择关卡");

    // 创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    // 创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    // 创建退出菜单
    QAction * quitAction = startMenu->addAction("退出");

    connect(quitAction,quitAction->triggered,[=](){
        this->close();
    });

    // 添加选择关卡按钮的音效
    QSound * choosesound = new QSound(":/res/LevelWinSound.wav",this);

    // 添加返回按钮的音效
    QSound * backsound = new QSound(":/res/BackButtonSound.wav",this);

    // back 按钮
    MyButton * backBtn = new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    // 点击back按钮
    connect(backBtn,backBtn->clicked,[=](){
//        qDebug() << "back!";



        // 延时返回

        backsound->play();
        QTimer::singleShot(200,this,[=](){
            // 告诉主场景 返回了
            emit this->choosesceneBack();
        });
    });


    // 创建关卡按钮
    for(int i = 0; i < 20;i++)
    {
        MyButton * menuBtn = new MyButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4 * 70 + 25,i/4 * 70 + 130);
//        menuBtn->setText(QString::number(i+1));

        // 监听每个关卡按钮的点击事件
        connect(menuBtn,menuBtn->clicked,[=](){


            // 开始播放选择关卡按钮的音效
            choosesound->play();

            QString str = QString("您选择的是第 %1 关").arg(i+1);
            qDebug() << str;
            this->hide();
            // 进入到游戏场景
            PlayScence * play = new PlayScence(i+1);
            play->show();// 显示游戏场景

            connect(play,play->quitsound,[=](){
                choosesound->stop();
            });

            // 设置当前场景的窗口位置
            play->setGeometry(this->geometry());
            connect(play,play->quitplay,[=](){
                this->setGeometry(play->geometry());
                this->show();
            });
        });



        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4 * 70 + 25 ,i/4 * 70 + 130);
        // 设置 label 上的文字对齐方式 水平居中 和 垂直剧中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


        // 设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelSence::paintEvent(QPaintEvent *event)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}

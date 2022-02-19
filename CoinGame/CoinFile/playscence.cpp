#include "playscence.h"
#include<QDebug>
#include<QLabel>
#include<mycoin.h>
#include<QPropertyAnimation>
#include <QSound>
//PlayScence::PlayScence(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScence::PlayScence(int levelNum)
{
    qDebug() << QString("进入了第 %1 关").arg(levelNum);
    this->levelIndex = levelNum;


    // 初始化游戏场景
    // 设置固定大小
    this->setFixedSize(320,588);

    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    // 设置标题
    this->setWindowTitle(QString("第%1关翻金币").arg(levelNum));

    // 添加返回按钮的音效
    QSound * backsound = new QSound(":/res/BackButtonSound.wav",this);
    // 添加翻金币音效
    QSound * filpsound = new QSound(":/res/ConFlipSound.wav");


    // 添加胜利后的音效
    QSound * winsound = new QSound(":/res/winGain.mp3");

    QMenuBar * bar = new QMenuBar(this);
    bar->setFixedSize(this->width(),bar->height());
    QMenu * menu = bar->addMenu("开始");
    QAction * action = menu->addAction("退出");

    connect(action,action->triggered,[=](){
        this->close();
        // 如果此时关卡按钮的声音还在播放就停止
        backsound->play();

        emit this->quitsound();
        emit this->quitplay();
    });


    // 显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    // 将字体设置到label中
    label->setFont(font);
    label->setText("Level："+QString::number(this->levelIndex));
    label->setGeometry(30,this->height() - 50,120,50);

    dataConfig config;

    // 初始化每个关卡的二维数组
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }


//    for(int i = 0;i < 4;i++)
//    {
//           qDebug() << this->gameArray[i][0] << " "
//                                             << this->gameArray[i][1] << " "
//                                                << this->gameArray[i][2] << " "
//                                                   << this->gameArray[i][3] << " ";
//    }


    // 胜利图片显示
    QLabel * winlabel = new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->setPixmap(pix);
    winlabel->setParent(this);
    winlabel->move((this->width() - pix.width()) * 0.5, -pix.height());


    // 显示金币背景图案
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            // 绘制背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            // 创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);

            // 维护该关卡的每个金币按钮
            this->btn_Coin[i][j] = coin;

            // 给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];


            // 点击金币，进行翻转
            connect(coin,coin->clicked,[=](){
                // 点击该按钮时，防止手快点击其他按钮，禁止点击其他按钮
                for(int i = 0;i < 4;i++)
                {
                    for(int j = 0;j < 4;j++)
                    {
                        // 胜利后不能继续点击金币按钮
                        btn_Coin[i][j]->is_win = true;
                    }
                }
                filpsound->play();
                coin->changFlag();
                this->gameArray[i][j] = (this->gameArray[i][j] == 0 ? 1 : 0);


                // 对该金币的周围金币进行延时翻转
                this->filp_arround(coin);

                // 判断是否胜利
                if(this->if_win())
                {
                    qDebug() << "胜利了";
                    for(int i = 0;i < 4;i++)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            // 胜利后不能继续点击金币按钮
                            btn_Coin[i][j]->is_win = true;
                        }
                    }


                    // 将胜利按钮移动下来
                    QPropertyAnimation * animation = new QPropertyAnimation(winlabel,"geometry");
                    // 设置事件间隔
                    animation->setDuration(1000);
                    // 设置开始位置
                    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));

                    // 设置结束位置
                    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+124,winlabel->width(),winlabel->height()));

                    // 设置缓和曲线
                    animation->setEasingCurve(QEasingCurve::OutBounce);

                    // 播放胜利音效和执行动画
                    winsound->play();
                    animation->start();
                }
                else
                {
                    for(int i = 0;i < 4;i++)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            // 没有胜利后能继续点击金币按钮
                            btn_Coin[i][j]->is_win = false;
                        }
                    }
                    qDebug() << "还没胜利";
                }

            });

        }
    }
}

void PlayScence::filp_arround(MyCoin * coin)
{
    // 对该金币按钮的上下左右同时进行翻转
    if(coin->posX + 1 < 4)// 翻转右侧的金币
    {
        this->btn_Coin[coin->posX+1][coin->posY]->changFlag();
        this->gameArray[coin->posX+1][coin->posY] = (this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0);
    }

    if(coin->posX - 1 >= 0)// 翻转左侧的金币
    {
        this->btn_Coin[coin->posX-1][coin->posY]->changFlag();
        this->gameArray[coin->posX-1][coin->posY] = (this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0);
    }

    if(coin->posY - 1 >= 0)// 翻转上面的金币
    {
        this->btn_Coin[coin->posX][coin->posY-1]->changFlag();
        this->gameArray[coin->posX][coin->posY-1] = (this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0);
    }

    if(coin->posY + 1 < 4)// 翻转下面的金币
    {
        this->btn_Coin[coin->posX][coin->posY+1]->changFlag();
        this->gameArray[coin->posX][coin->posY+1] = (this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0);
    }
}

bool PlayScence::if_win()
{
//    for(int i = 0;i < 4;i++)
//    {
//           qDebug() << this->gameArray[i][0] << " "
//                                             << this->gameArray[i][1] << " "
//                                                << this->gameArray[i][2] << " "
//                                                   << this->gameArray[i][3] << " ";
//    }

    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            if(this->btn_Coin[i][j]->flag == false)
            {
                return false;
            }
        }
    }

    return true;
}

void PlayScence::paintEvent(QPaintEvent *event)
{
    // 创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

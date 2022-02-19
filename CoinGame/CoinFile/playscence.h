#ifndef PLAYSCENCE_H
#define PLAYSCENCE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include"dataconfig.h"
#include "mycoin.h"
class PlayScence : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScence(QWidget *parent = nullptr);
    PlayScence(int levelNum);

    void paintEvent(QPaintEvent *event);

    int levelIndex;// 内部成员属性 记录所选的关卡

    int gameArray[4][4];// 保存每个关卡的游戏数据

    MyCoin * btn_Coin[4][4];// 维护每个关卡的金币按钮

    void filp_arround(MyCoin * coin);// 对该金币的上下左右进行延时翻转

    bool if_win();// 每次翻转判断是否胜利，全为金色金币


signals:
    void quitplay();

    void quitsound();

public slots:
};

#endif // PLAYSCENCE_H

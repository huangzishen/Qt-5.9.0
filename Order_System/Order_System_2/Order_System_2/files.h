#ifndef FILES_H
#define FILES_H

#include <QDir>
// 文件都保存在当前路径下的files文件夹下
#define Students_File QDir::currentPath()+"/files/Students.txt"
#define Managers_File QDir::currentPath()+"/files/Managers.txt"
#define Teachers_File QDir::currentPath()+"/files/Teachers.txt"
#define Orders_File QDir::currentPath()+"/files/Orders.txt"

#define MAX_COMPUTER_1 20 // 一号机房最大容量 20
#define MAX_COMPUTER_2 50 // 二号机房最大容量 50
#define MAX_COMPUTER_3 100 // 三号机房最大容量 100

#endif // FILES_H

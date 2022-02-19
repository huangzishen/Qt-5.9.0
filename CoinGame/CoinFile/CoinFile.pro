#-------------------------------------------------
#
# Project created by QtCreator 2022-01-23T14:36:06
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinFile
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainscence.cpp \
    mybutton.cpp \
    chooselevelsence.cpp \
    playscence.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS += \
        mainscence.h \
    mybutton.h \
    chooselevelsence.h \
    playscence.h \
    mycoin.h \
    dataconfig.h

FORMS += \
    mainscence.ui \
    mybutton.ui

RESOURCES += \
    res.qrc

OBJECTS_DIR = tmp
MOC_DIR = tmp

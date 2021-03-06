#-------------------------------------------------
#
# Project created by QtCreator 2022-01-27T16:27:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Order_System
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
        widget.cpp \
    student_class.cpp \
    teacher_class.cpp \
    manager_class.cpp \
    login.cpp

HEADERS += \
        widget.h \
    student_class.h \
    teacher_class.h \
    manager_class.h \
    login.h \
    files.h

FORMS += \
        widget.ui

RESOURCES += \
    res.qrc

OBJECTS_DIR = tmp
MOC_DIR = tmp

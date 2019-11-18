#-------------------------------------------------
#
# Project created by QtCreator 2019-11-18T10:30:46
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logging
TEMPLATE = app


SOURCES += main.cpp\
#        mainwindow.cpp

#HEADERS  += mainwindow.h

#FORMS    += mainwindow.ui



unix{
    #32bit系统
    contains(QT_ARCH, i386){

        CONFIG += c++11
        message("增加头文件搜索相对路径")
        message($$PWD/../depends/log4cplus/linux_x32/inc/log4cplus)

        INCLUDEPATH += $$PWD/../depends/log4cplus/linux_x32/inc/

        LIBS += -L$$PWD/depends/log4cplus/linux_x32/lib -llog4cplus
    }
    #64bit系统
    contains(QT_ARCH, x86_64){

        CONFIG += c++11

        INCLUDEPATH += $$PWD/../depends/log4cplus/linux_x32/inc/

        LIBS += -L$$PWD/depends/log4cplus/linux_x32/lib -llog4cplus
    }
}



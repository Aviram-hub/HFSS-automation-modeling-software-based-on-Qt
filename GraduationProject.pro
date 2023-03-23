#-------------------------------------------------
#
# Project created by QtCreator 2023-01-18T00:07:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraduationProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mydialog.cpp \
    project_type.cpp \
    action_label.cpp

HEADERS  += mainwindow.h \
    mydialog.h \
    project_type.h \
    action_label.h

FORMS    += mainwindow.ui \
    mydialog.ui \
    project_type.ui \
    action_label.ui

RESOURCES += \
    res.qrc

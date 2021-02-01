#-------------------------------------------------
#
# Project created by QtCreator 2019-10-31T12:03:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = semiautodoc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

#QMAKE_PRE_LINK=$$PWD/parser/build_script.sh
QMAKE_PRE_LINK= cd $$PWD/parser/build/ && make


semiautodoc.depends = parser

parser.target = libparser.a

QMAKE_EXTRA_TARGETS += parser

parser.commands = cd $$PWD/parser/build/ && make

PRE_TARGETDEPS += parser
#PRE_TARGETDEPS += $$OUT_PWD/parser/build/libparser.a
INCLUDEPATH += $$OUT_PWD/parser/build

INCLUDEPATH += $$OUT_PWD/parser/parser/include
INCLUDEPATH += $$OUT_PWD/gui/include

LIBS+= -L$$OUT_PWD/parser/build/parser -lparser

SOURCES += \
        gui/src/edit-text-delegate.cpp \
        gui/src/main.cpp \
        gui/src/tree-model.cpp \
        gui/src/widget.cpp \
        gui/src/model-widget.cpp

HEADERS += \
        gui/include/edit-text-delegate.h \
        gui/include/tree-model.h \
        gui/include/widget.h \
        gui/include/model-widget.h

FORMS += \
        gui/widget.ui

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
    OBJECTS_DIR = build/debug/.obj
    MOC_DIR = build/debug/.moc
    RCC_DIR = build/debug/.rcc
    UI_DIR = build/debug/.ui
} else {
    DESTDIR = build/release
    OBJECTS_DIR = build/release/.obj
    MOC_DIR = build/release/.moc
    RCC_DIR = build/release/.rcc
    UI_DIR = build/release/.ui
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

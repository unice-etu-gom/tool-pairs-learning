#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T16:04:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tool-pairs-learning
TEMPLATE = app

# ##############################################################################
# ##############################################################################

CONFIG(debug, debug|release) {
    DIR_BUILD   = $$PWD/build/debug
}else{
    DIR_BUILD   = $$PWD/build/release
}

MOC_DIR     = $$DIR_BUILD/moc
OBJECTS_DIR = $$DIR_BUILD/obj
RCC_DIR     = $$DIR_BUILD/rcc
UI_DIR      = $$DIR_BUILD/ui

DESTDIR = out/$$TEMPLATE

# ##############################################################################
# ##############################################################################

INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/ui/MainWindow.cpp \
    src/main.cpp \
    src/core/CFileParser.cpp \
    src/core/CTranslation.cpp \
    src/core/CDataManager.cpp \
    src/ui/WQuestion.cpp

HEADERS  += \
    src/ui/MainWindow.h \
    src/core/CFileParser.h \
    src/core/CTranslation.h \
    src/core/Log.h \
    src/core/CDataManager.h \
    src/ui/WQuestion.h

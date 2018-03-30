TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    translate_koi8.cpp \
    translate_win1251.cpp \
    create_tableh.cpp \
    tables.cpp

HEADERS += \
    translate_win1251.h \
    translate_koi8.h \
    tables.h


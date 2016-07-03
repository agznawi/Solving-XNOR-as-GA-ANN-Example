TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    population.cpp \
    individual.cpp \
    evolution.cpp

HEADERS += \
    population.h \
    individual.h \
    globals.h \
    evolution.h


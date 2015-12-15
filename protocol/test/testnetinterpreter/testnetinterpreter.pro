TEMPLATE = app
CONFIG += console
QMAKE_CXXFLAGS += -std=c++14
INCLUDEPATH += . ../../src

SOURCES += main.cpp

include(deployment.pri)


######################################################################
# Automatically generated by qmake (3.0) lun. nov. 30 11:21:53 2015
######################################################################

TEMPLATE = app
TARGET = testNetInterpreter
INCLUDEPATH += . ../../src ../../src/vnet .. ../../src/net
DEPENDPATH  += . ../../src ../../src/vnet .. ../../src/net
QMAKE_CXXFLAGS += -std=c++14
OBJECTS_DIR = bin
QT += testlib

unix:!macx: LIBS += -L$$OUT_PWD/../../ -lprotocol
unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../libprotocol.a

# Input
HEADERS += \
    testnetinterpreter.hpp
SOURCES += \
    testnetinterpreter.cpp

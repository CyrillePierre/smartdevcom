######################################################################
# Automatically generated by qmake (3.0) dim. d�c. 6 15:26:03 2015
######################################################################

TEMPLATE = app
TARGET = testAddr
INCLUDEPATH += . ../../src ../../src/vnet .. ../../src/net
DEPENDPATH  += . ../../src ../../src/vnet .. ../../src/net
QMAKE_CXXFLAGS += -std=c++14
OBJECTS_DIR = bin
QT += testlib

unix:!macx: LIBS += -L$$OUT_PWD/../../ -lprotocol
unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../libprotocol.a

# Input
HEADERS += \
    testaddr.hpp
SOURCES += \
    testaddr.cpp

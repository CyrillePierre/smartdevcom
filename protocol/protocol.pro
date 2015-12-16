######################################################################
# Automatically generated by qmake (3.0) ven. nov. 27 17:26:31 2015
######################################################################

TEMPLATE = app
TARGET = protocol
INCLUDEPATH += src src/net
QT += testlib
QMAKE_CXXFLAGS += -std=c++14
OBJECTS_DIR = bin

# Input
HEADERS += src/types.hpp \
           src/net/netmanager.hpp \
           src/net/netstream.hpp \
           src/dynamicbitset.hpp \
           src/net/netinterpreter.hpp \
           src/net/varpheader.hpp \
           src/net/netdevice.hpp \
	   src/net/vipinterpreter.h \
    src/net/vipheader.h \
    src/vnet/sdcpinterpreter.hpp

SOURCES += src/main.cpp \
           src/net/netmanager.cpp \
           src/net/netstream.cpp \
           src/net/netinterpreter.cpp \
           src/net/varpheader.cpp \
	   src/net/netdevice.cpp \
	   src/net/vipinterpreter.cpp \
    src/net/vipheader.cpp \
    src/vnet/sdcpinterpreter.cpp

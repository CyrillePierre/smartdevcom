######################################################################
# Automatically generated by qmake (3.0) ven. nov. 27 17:26:31 2015
######################################################################

TEMPLATE = lib
TARGET = protocol
INCLUDEPATH += src src/net
QT += testlib
QMAKE_CXXFLAGS += -std=c++14 -fPIC
OBJECTS_DIR = bin
CONFIG += static

# Input
HEADERS += src/types.hpp \
           src/net/netmanager.hpp \
           src/net/netstream.hpp \
           src/dynamicbitset.hpp \
           src/net/netinterpreter.hpp \
           src/net/varpheader.hpp \
		   src/vnet/vipinterpreter.h \
		   src/vnet/vipheader.h \
		   src/vnet/sdcpinterpreter.hpp \
    src/device.hpp \
    src/sensor.hpp \
    src/element.hpp \
    src/actuator.hpp \
    src/action.hpp \
    src/net/netdevice.hpp \
    src/net/addr.hpp \
    src/net/routingtable.hpp \
    src/view/view.hpp \
    src/view/list.hpp \
    src/typetraits.hpp

SOURCES +=  \
           src/net/netmanager.cpp \
           src/net/netstream.cpp \
           src/net/netinterpreter.cpp \
		   src/net/netdevice.cpp \
		   src/vnet/vipinterpreter.cpp \
		   src/vnet/sdcpinterpreter.cpp \
    src/device.cpp \
    src/net/addr.cpp \
    src/net/routingtable.cpp \
    src/view/view.cpp \
    src/view/list.cpp

SUBDIRS += \
    test/testSdcpInterpreter/testSdcpInterpreter.pro

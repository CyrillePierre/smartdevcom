######################################################################
# Automatically generated by qmake (3.0) ven. nov. 27 17:26:31 2015
######################################################################

TEMPLATE = app
TARGET = protocol
INCLUDEPATH += src src/net
QT += testlib
CONFIG += c++11
OBJECTS_DIR = bin

# Input
HEADERS += src/types.hpp \
           src/net/netmanager.hpp \
           src/net/netstream.hpp \
           src/net/socket.hpp \
           src/dynamicbitset.hpp
SOURCES += src/main.cpp \
           src/net/netmanager.cpp \
           src/net/netstream.cpp \

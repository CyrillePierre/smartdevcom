TEMPLATE = app
TARGET = testUart
INCLUDEPATH += src
QMAKE_CXXFLAGS += -std=c++14
OBJECTS_DIR = bin

SOURCES += \
    src/main.cpp \
    src/uart.cpp

HEADERS += \
    src/uart.h

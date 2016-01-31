TEMPLATE = app
TARGET = uartPc
INCLUDEPATH += src
QMAKE_CXXFLAGS += -std=c++14
OBJECTS_DIR = bin

HEADERS += \
    src/uart.h

SOURCES += \
    src/uart.cpp \
    src/main.cpp

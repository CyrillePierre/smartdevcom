#ifndef TESTNETSTREAM_HPP
#define TESTNETSTREAM_HPP

#include <vector>
#include <QtTest/QtTest>
#include "net/netstream.hpp"

class TestNetStream : public QObject {
    Q_OBJECT

public:
    struct DeviceTest : sdc::net::NetDevice {
        sdc::type::Byte *buf;
        int pos;

        DeviceTest() : pos(0) {}

        virtual void read(sdc::type::Byte *, int);
        virtual void write(sdc::type::Byte const *, int);
    };

    DeviceTest dt;

private slots:
    void testRead();
};

#endif // TESTNETSTREAM_HPP

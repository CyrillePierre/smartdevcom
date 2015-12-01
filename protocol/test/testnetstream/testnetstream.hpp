#ifndef TESTNETSTREAM_HPP
#define TESTNETSTREAM_HPP

#include <vector>
#include <QtTest/QtTest>
#include "net/netstream.hpp"

class TestNetStream : public QObject
{
    Q_OBJECT

public:
    struct SockTest : sdc::net::Socket {
        sdc::type::Byte buf[32];

        virtual void read(sdc::type::Byte *, int);
        virtual void write(sdc::type::Byte const *, int);
    };

    SockTest st;

private slots:
    void write();
    void read();
};

#endif // TESTNETSTREAM_HPP

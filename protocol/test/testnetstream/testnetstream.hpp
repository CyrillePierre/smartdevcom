#ifndef TESTNETSTREAM_HPP
#define TESTNETSTREAM_HPP

#include <vector>
#include <QtTest/QtTest>
#include "net/netstream.hpp"
#include "../fakedevice.hpp"

class TestNetStream : public QObject {
    Q_OBJECT

private slots:
    void testRead();
};

#endif // TESTNETSTREAM_HPP

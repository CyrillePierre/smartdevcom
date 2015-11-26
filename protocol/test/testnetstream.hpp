#ifndef TESTNETSTREAM_HPP
#define TESTNETSTREAM_HPP

#include <QtTest/QtTest>

class TestNetStream : public QObject
{
    Q_OBJECT

private slots:
    void write();
    void read();
    void listener();
};

#endif // TESTNETSTREAM_HPP

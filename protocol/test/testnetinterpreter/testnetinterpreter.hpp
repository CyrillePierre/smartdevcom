#ifndef TESTNETINTERPRETER_HPP
#define TESTNETINTERPRETER_HPP

#include <QtTest/QtTest>

class TestNetInterpreter : public QObject
{
    Q_OBJECT

private slots:
    void vipAddrRequests();
    void testVarp();
};

#endif // TESTNETINTERPRETER_HPP

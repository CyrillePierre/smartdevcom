#ifndef TESTSDCPINTERPRETER_HPP
#define TESTSDCPINTERPRETER_HPP

#include <QtTest/QtTest>

class TestSDCPInterpreter : public QObject
{
    Q_OBJECT

private slots:
    void testTest();
    void testSensors();
    void testActuators();
    void testActions();
    void testActionDef();
    void testExec();
};

#endif // TESTSDCPINTERPRETER_HPP

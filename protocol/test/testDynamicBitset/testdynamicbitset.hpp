#ifndef TESTDYNAMICBITSET_HPP
#define TESTDYNAMICBITSET_HPP

#include <QtTest/QtTest>

class TestDynamicBitset : public QObject {
    Q_OBJECT

private slots:
    void testEmpty() const;
    void testClear() const;
    void testPush() const;
    void testPushPtr() const;
};

#endif // TESTDYNAMICBITSET_HPP

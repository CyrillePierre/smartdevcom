#ifndef TESTDYNAMICBITSET_HPP
#define TESTDYNAMICBITSET_HPP

#include <QtTest/QtTest>

class TestDynamicBitset : public QObject {
    Q_OBJECT

public slots:
    void testPush() const;
};

#endif // TESTDYNAMICBITSET_HPP

#ifndef TESTADDR_HPP
#define TESTADDR_HPP

#include <QtTest/QtTest>

class TestAddr : public QObject
{
    Q_OBJECT

private slots:
    void constructors() const;
};

#endif // TESTADDR_HPP

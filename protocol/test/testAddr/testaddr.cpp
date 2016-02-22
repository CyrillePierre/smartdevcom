#include "testaddr.hpp"
#include "net/addr.hpp"

using sdc::net::Addr;
using sdc::net::makeAddr;

void TestAddr::constructors() const {
    sdc::type::Byte const b1[]{1, 2, 3},
                          b2[]{0xf3, 0x34, 0x6b, 0x55},
                          b3[]{1};

    Addr a1{b1, sizeof(b1)}, a2{b2, sizeof(b2)}, a3{b3, sizeof(b3)};
    Addr const a4 = makeAddr<0x23, 0x52, 0xf4, 0xbc, 0x45, 0x8a>();
    Addr a5 = makeAddr<0x1f, 0xec, 0xb3, 2>();
    char * hex;

    QCOMPARE(a1.size, sizeof(b1));
    QCOMPARE(a2.size, sizeof(b2));
    QCOMPARE(a3.size, sizeof(b3));
    QCOMPARE(a4.size, (std::size_t) 6);
    QCOMPARE(a5.size, (std::size_t) 4);

    hex = QTest::toHexRepresentation((char const *) a1.vals, a1.size);
    QCOMPARE(hex, "01 02 03");
    hex = QTest::toHexRepresentation((char const *) a2.vals, a2.size);
    QCOMPARE(hex, "F3 34 6B 55");
    hex = QTest::toHexRepresentation((char const *) a3.vals, a3.size);
    QCOMPARE(hex, "01");
    hex = QTest::toHexRepresentation((char const *) a4.vals, a4.size);
    QCOMPARE(hex, "23 52 F4 BC 45 8A");
    hex = QTest::toHexRepresentation((char const *) a5.vals, a5.size);
    QCOMPARE(hex, "1F EC B3 02");
}

void TestAddr::compare() const {
    Addr a1 = makeAddr<0x41, 0x7a, 0xb3>(),
         a2 = makeAddr<0x41, 0xfa, 0xd1>(),
         a3 = makeAddr<0x41, 0x7a, 0x23>(),
         a4 = makeAddr<0x41, 0x7a, 0xb3>(),
         a5 = makeAddr<0x12, 0x01, 0x04>();

    QCOMPARE(a1 == a2, false);
    QCOMPARE(a1 == a3, false);
    QCOMPARE(a1 == a4, true);
    QCOMPARE(a1 == a5, false);
    QCOMPARE(a2 != a3, true);
    QCOMPARE(a4 != a3, true);
    QCOMPARE(a4 != a1, false);
}

void TestAddr::broadcast() const {
    Addr a1 = makeAddr<0x41, 0x7a, 0xb3>(),
         a2 = makeAddr<0x41, 0x7a, 0xff>(),
         a3 = makeAddr<0x41, 0xff, 0xff>(),
         a4 = makeAddr<0xff, 0xff, 0xff>(),
         a6 = makeAddr<0x41, 0xff, 0xb3>();

    QCOMPARE(a1.broadcastLvl(), 0);
    QCOMPARE(a2.broadcastLvl(), 1);
    QCOMPARE(a3.broadcastLvl(), 2);
    QCOMPARE(a4.broadcastLvl(), 3);
    QCOMPARE(a6.broadcastLvl(), 0);
}

void TestAddr::accept() const {
    Addr a1 = makeAddr<0x41, 0x7a, 0xb3>(),
         a2 = makeAddr<0x41, 0x7a, 0xff>(),
         a3 = makeAddr<0x41, 0xff, 0xff>(),
         a4 = makeAddr<0xff, 0xff, 0xff>(),
         a5 = makeAddr<0x41, 0x7b, 0xff>(),
         a6 = makeAddr<0x41, 0xff, 0xb3>();

    QCOMPARE(a1.accept(a1), true);
    QCOMPARE(a1.accept(a2), true);
    QCOMPARE(a1.accept(a3), true);
    QCOMPARE(a1.accept(a4), true);
    QCOMPARE(a1.accept(a5), false);
    QCOMPARE(a6.accept(a1), false);
    QCOMPARE(a1.accept(a6), false);
}

QTEST_MAIN(TestAddr);
#include "moc_testaddr.cpp"

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
    Addr const a5 = makeAddr<0x1f, 0xec, 0xb3, 2>();
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

QTEST_MAIN(TestAddr);
#include "moc_testaddr.cpp"

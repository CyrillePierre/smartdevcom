#include <sstream>
#include "testnetstream.hpp"

namespace type = sdc::type;
using sdc::net::NetStream;

void TestNetStream::SockTest::write(type::Byte const *b, int size) {
    type::Byte *it = buf;
    while (size--) *it++ = *b++;
}

void TestNetStream::SockTest::read(type::Byte *b, int size) {
    type::Byte *it = buf;
    while (size--) *b++ = *it++;
}

void TestNetStream::write() {
    NetStream ns(st);
    uint32_t a = 0x23ff12ee;
    uint16_t c = 0xff00;
    uint8_t  d = 0xa2;

    ns.write(d, 8);
    ns.flushOut();
    QCOMPARE(*(uint8_t *)st.buf, uint8_t(0xa2));

    ns.write(d, 6);
    ns.flushOut();
    QCOMPARE(uint8_t(*(uint8_t *)st.buf & 0x3f), uint8_t(0x22));

    ns.write(c, 13);
    ns.flushOut();
    qDebug() << QTest::toHexRepresentation((char *)st.buf, 8);
    qDebug() << QTest::toHexRepresentation((char *)&c, 2);
    QCOMPARE(uint16_t(*(uint16_t *)st.buf & 0x1fff), uint16_t(0x1f00));

//    ns.write(c, 16);
//    ns.flushOut();
//    QCOMPARE(*(uint16_t *)st.buf, uint16_t(0xff00));

//    ns.write(a, 32);
//    ns.flushOut();
//    QCOMPARE(*(uint32_t *)st.buf, uint32_t(0x23ff12ee));

//    ns.write(a, 25);
//    ns.flushOut();
//    QCOMPARE(*(uint32_t *)st.buf, uint32_t(0x1ff12ee));

//    ns.write(a, 7);
//    ns.flushOut();
//    QCOMPARE(*(uint32_t *)st.buf, uint32_t(0x6e));

//    ns.write(a, 11);
//    ns.flushOut();
//    QCOMPARE(*(uint32_t *)st.buf, uint32_t(0x2ee));
}

void TestNetStream::read() {
}

QTEST_APPLESS_MAIN(TestNetStream)
#include "moc_testnetstream.cpp"

#include <sstream>
#include "testnetstream.hpp"

namespace type = sdc::type;
using sdc::net::NetStream;

void TestNetStream::testRead() {
    type::Byte com[] = {0xaa, 0xdd};
    type::Byte virt[] = {0xB0, 0xB1, 0xB2};
    type::Byte deviceBuf[32] = {0xa2, 0xf3, 0xee, 0x28, 0x90, 0xf7, 0xa4};
    type::Byte buf[32];
    sdc::test::FakeDevice fk{com, virt, 2};
    NetStream ns(fk);
    char *hex;

    fk.buf = deviceBuf;

    // 1010 0010 1111 0011 1110 1110 0010 1000 1001 0000 1111 0111 1010 0100
    //                     |-----||--||||-----------||---------------------|

    ns.read(buf, 2);
    hex = QTest::toHexRepresentation((char *) buf, 2);
    QCOMPARE(hex, "A2 F3");

    type::Byte i;
    ns.read(i, 6);
    hex = QTest::toHexRepresentation((char *) &i, 1);
    QCOMPARE(hex, "3B");

    ns.read(i, 3);
    hex = QTest::toHexRepresentation((char *) &i, 1);
    QCOMPARE(hex, "04");

    ns.read(i, 2);
    hex = QTest::toHexRepresentation((char *) &i, 1);
    QCOMPARE(hex, "01");

    type::Word w;
    ns.read(w, 10);
    hex = QTest::toHexRepresentation((char *) &w, 2);
    QCOMPARE(hex, "12 01");

    type::DWord d;
    ns.read(d, 19);
    hex = QTest::toHexRepresentation((char *) &d, 4);
    QCOMPARE(hex, "A4 F7 00 00");
}

QTEST_APPLESS_MAIN(TestNetStream)
#include "moc_testnetstream.cpp"

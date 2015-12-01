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
//    QVERIFY2(*st.buf == uint8_t(0xa2), (int)*st.buf + " " + (int)0xa2);
    QVERIFY2(*st.buf == uint8_t(0xa2), "cheval rouge");
}

void TestNetStream::read() {
}

QTEST_APPLESS_MAIN(TestNetStream)
#include "moc_testnetstream.cpp"

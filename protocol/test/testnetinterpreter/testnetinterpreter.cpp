#include "types.hpp"
#include "testnetinterpreter.hpp"
#include "net/netmanager.hpp"
#include "fakedevice.hpp"

using namespace sdc;

void TestNetInterpreter::vipAddrRequests() {
    test::FakeDevice fd(net::makeAddr<0xc0, 0xa7, 0xd9, 0x78>(),
                        net::makeAddr<0x1b, 0xc7, 0x05>(),
                        net::makeAddr<0x1b, 0xc7, 0x00>());

    net::NetManager mgr;

    auto callTest = [&mgr, &fd] (type::Byte * buf, int size, char const * str) {
        fd.reset();
        fd.buf = buf;
        net::NetStream ns(fd);
        mgr.net()(ns);
        char *hex = QTest::toHexRepresentation((char *) buf, size);
        QCOMPARE(hex, str);
    };

    type::Byte buf1[32] = {0x08, 0x04,
                           0xc0, 0xa7, 0x1c, 0x04, 	0x1b, 0xc7, 0x03,
                           0xff, 0xff, 0xff, 0xff,	0x1b, 0xc7, 0x05};

    type::Byte buf2[32] = {0x08, 0x24,
                           0xc0, 0xa7, 0x1c, 0x04, 	0x1b, 0xc7, 0x03,
                           0xc0, 0xa7, 0xd9, 0x78,	0x1b, 0xff, 0xff};

    callTest(buf1, 16, "08 44 C0 A7 D9 78 1B C7 05 C0 A7 1C 04 1B C7 03");
    callTest(buf2, 16, "08 44 C0 A7 D9 78 1B C7 05 C0 A7 1C 04 1B C7 03");
}

void TestNetInterpreter::testVarp() {

}

QTEST_MAIN(TestNetInterpreter);
#include "moc_testnetinterpreter.cpp"


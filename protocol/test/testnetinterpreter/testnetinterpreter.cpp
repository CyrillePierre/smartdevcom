#include "types.hpp"
#include "testnetinterpreter.hpp"
#include "sdcpinterpreter.hpp"
#include "vipinterpreter.h"
#include "netinterpreter.hpp"
#include "fakedevice.hpp"

using namespace sdc;

void TestNetInterpreter::vipAddrRequests() {
    type::Byte deviceBuf[32] =
        {0x08, 0x04,
         0xc0, 0xa7, 0x1c, 0x04, 	0x1b, 0xc7, 0x03,
         0xff, 0xff, 0xff, 0xff,	0x1b, 0xc7, 0x05};

    test::FakeDevice fd(net::makeAddr<0xc0, 0xa7, 0x1c, 0x04>(),
                        net::makeAddr<0x1b, 0xc7, 0x03>());
    net::NetStream ns(fd);
    vnet::SDCPInterpreter sdcp;
    vnet::VIPInterpreter vip(sdcp);
    net::NetInterpreter net(vip);
    char *hex;

    fd.buf = deviceBuf;
    net(ns);
    hex = QTest::toHexRepresentation((char *) deviceBuf, 16);
    QCOMPARE(hex, "00 32 B0 B1 B2 A0 A1 A2 00 01 01");
}

void TestNetInterpreter::testVarp() {

}

QTEST_MAIN(TestNetInterpreter);
#include "moc_testnetinterpreter.cpp"


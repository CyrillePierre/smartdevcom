#include "types.hpp"
#include "testsdcpinterpreter.hpp"
#include "sdcpinterpreter.hpp"
#include "fakedevice.hpp"
#include "netstream.hpp"
#include "net/netmanager.hpp"
#include "addr.hpp"

using namespace sdc;

void TestSDCPInterpreter::testTest() {
    type::Byte deviceBuf[32] = {0x00, 0xff, 0xa0, 0xa1, 0xa2, 0xb0, 0xb1, 0xb2,
                                0x00, 0x00, 0x00};
    test::FakeDevice fd(net::makeAddr<0xaa, 0xdd>(),
                        net::makeAddr<0xb0, 0xb1, 0xb2>(),
                        net::makeAddr<0xb0, 0xb1, 0x00>());
    net::NetStream        ns(fd);

    net::NetManager mgr;
    char *hex;

    fd.buf = deviceBuf;
    mgr.net()(ns);
    hex = QTest::toHexRepresentation((char *) deviceBuf, 11);
    QCOMPARE(hex, "00 32 B0 B1 B2 A0 A1 A2 00 01 01");
}

void TestSDCPInterpreter::testSensors() {
}

void TestSDCPInterpreter::testActuators() {

}

void TestSDCPInterpreter::testActions() {

}

void TestSDCPInterpreter::testActionDef() {

}

void TestSDCPInterpreter::testExec() {

}

QTEST_MAIN(TestSDCPInterpreter);
#include "moc_testsdcpinterpreter.cpp"

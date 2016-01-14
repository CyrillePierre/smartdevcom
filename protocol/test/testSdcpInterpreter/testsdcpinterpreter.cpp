#include "types.hpp"
#include "testsdcpinterpreter.hpp"
#include "sdcpinterpreter.hpp"
#include "fakedevice.hpp"
#include "netstream.hpp"
#include "vipinterpreter.h"

using namespace sdc;

void TestSDCPInterpreter::testTest() {
    type::Byte com[] = {0xaa, 0xdd};
    type::Byte virt[] = {0xB0, 0xB1, 0xB2};
    type::Byte deviceBuf[32] = {0x00, 0xff, 0xa0, 0xa1, 0xa2, 0xb0, 0xb1, 0xb2,
                                0x00, 0x00, 0x00};
    test::FakeDevice fd(com, virt);
    net::NetStream ns(fd);
    vnet::VIPInterpreter vip;
    char *hex;

    fd.buf = deviceBuf;
    vip(ns);
    hex = QTest::toHexRepresentation((char *) deviceBuf, 11);
    QCOMPARE(hex, "00 FF B0 B1 B2 A0 A1 A2 00 80 00");
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

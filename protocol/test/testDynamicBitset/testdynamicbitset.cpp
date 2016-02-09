#include "testdynamicbitset.hpp"
#include "dynamicbitset.hpp"
#include <iostream>

using namespace sdc;

void TestDynamicBitset::testEmpty() const {
    DynamicBitset db;
    QCOMPARE(db.empty(), true);

    db.push(0, 1);
    QCOMPARE(db.empty(), false);
}

void TestDynamicBitset::testClear() const {
    DynamicBitset db;

    db.clear();
    QCOMPARE(db.empty(), true);
    db.clear();
    QCOMPARE(db.empty(), true);
    db.push(0, 1);
    db.clear();
    QCOMPARE(db.empty(), true);
    db.push(0, 32);
    db.push(0, 31);
    db.clear();
    QCOMPARE(db.empty(), true);
}

void TestDynamicBitset::testPush() const {
    DynamicBitset db;
    DynamicBitset::BlockType *data;
    char *buf;

    db.push(uint8_t(0xf2), 8);
    db.push(uint8_t(0x0a), 5);
    db.push(uint8_t(0x39), 6);
    db.push(uint8_t(0x0f), 1);
    db.push(uint8_t(0x73), 7);
    db.push(uint8_t(0xcb), 8);
    data = db.data();
    // 0b(1111 0010 0101 0111 0011 1110 0111 1001 0110 0000)  0x(f2 57 3e 79 60)
    buf = QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(35));
    QCOMPARE(buf, "F2 57 3E 79 60");

    db.clear();
    db.push(uint16_t(0xfce4), 16);
    db.push(uint16_t(0x099e), 12);
    db.push(uint16_t(0xffff), 2);
    db.push(uint16_t(0x0000), 7);
    db.push(uint16_t(0xabcd), 15);
    data = db.data();
    // 0b(1111 1100 1110 0100 1001 1001 1110 1100 0000 0010 1011 1100 1101 0000)
    buf = QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(16+12+2+7+15));
    QCOMPARE(buf, "FC E4 99 EC 02 BC D0");

    db.clear();
    db.push(uint32_t(0x01a7e9f3), 32);
    db.push(uint8_t(0), 3);
    db.push(uint16_t(0x55cc), 16);
    db.push(uint32_t(0x37ed2806), 23);
    data = db.data();
    // 0b(0000 0001 1010 0111 1110 1001 1111 0011 0000 1010 1011 1001
    //    1001 1011 0100 1010 0000 0001 1000 0000)
    buf = QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(32+3+16+23));
    QCOMPARE(buf, "01 A7 E9 F3 0A B9 9B 4A 01 80");
}

void TestDynamicBitset::testPushPtr() const {
    DynamicBitset db;
    DynamicBitset::BlockType *data;
    char *buf;

    type::Byte  bytes[]  = {0x12, 0xaf, 0xa5, 0x3c, 0x23, 0x0e};
    type::Word  words[]  = {0xaefc, 0x3490, 0x0040, 0x1f2a};
    type::DWord dwords[] = {0xab4fe812, 0xaabbcc33, 0x0f1e2d3b};

    db.push(bytes, sizeof(bytes));
    data = db.data();
    buf =  QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(sizeof(bytes) << 3));
    QCOMPARE(buf, "12 AF A5 3C 23 0E");

    db.clear();
    db.push(5, 4);
    db.push(words, sizeof(words));
    data = db.data();
    buf = QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType((sizeof(words) << 3) + 4));
    QCOMPARE(buf, "5A EF C3 49 00 04 01 F2 A0");

    db.clear();
    db.push(dwords, sizeof(dwords));
    data = db.data();
    buf = QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(sizeof(dwords) << 3));
    QCOMPARE(buf, "AB 4F E8 12 AA BB CC 33 0F 1E 2D 3B");
}

void TestDynamicBitset::testValue() const
{
    DynamicBitset db;

    for (int i = 0; i < 0x100; ++i) {
        db.clear();
        db.push(i, 8);
        QCOMPARE((int) *db.data(), i);
    }

}

QTEST_MAIN(TestDynamicBitset);
#include "moc_testdynamicbitset.cpp"


#include "testdynamicbitset.hpp"
#include "dynamicbitset.hpp"

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
    using BlockType = DynamicBitset::BlockType;

    DynamicBitset db;
    BlockType *data;

    db.push(uint8_t(0xf2), 8);
    db.push(uint8_t(0x0a), 5);
    db.push(uint8_t(0x39), 6);
    db.push(uint8_t(0x0f), 1);
    db.push(uint8_t(0x73), 7);
    db.push(uint8_t(0xcb), 8);
    data = db.data();
    // 0b(1111 0010 0101 0111 0011 1110 0111 1001 0110 0000)  0x(f2 57 3e 79 60)
    qDebug() << QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(35));
    for (BlockType byte : {0xf2, 0x57, 0x3e, 0x79, 0x60})
        QCOMPARE(*data++, byte);

    db.clear();
    db.push(uint16_t(0xfce4), 16);
    db.push(uint16_t(0x099e), 12);
    db.push(uint16_t(0xffff), 2);
    db.push(uint16_t(0x0000), 7);
    db.push(uint16_t(0xabcd), 15);
    data = db.data();
    // 0b(1111 1100 1110 0100 1001 1001 1110 1100 0000 0010 1011 1100 1101 0000)
    qDebug() << QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(16+12+2+7+15));
    for (BlockType byte : {0xfc, 0xe4, 0x99, 0xec, 0x02, 0xbc, 0xd0})
        QCOMPARE(*data++, byte);

    db.clear();
    db.push(uint32_t(0x01a7e9f3), 32);
    db.push(uint8_t(0), 3);
    db.push(uint16_t(0x55cc), 16);
    db.push(uint32_t(0x37ed2806), 23);
    data = db.data();
    // 0b(0000 0001 1010 0111 1110 1001 1111 0011 0000 1010 1011 1001
    //    1001 1011 0100 1010 0000 0001 1000 0000)
    qDebug() << QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(32+3+16+23));
    for (BlockType byte : {0x01, 0xa7, 0xe9, 0xf3, 0x0a, 0xb9,
                           0x9b, 0x4a, 0x01, 0x80})
        QCOMPARE(*data++, byte);
}

void TestDynamicBitset::testPushPtr() const {
    using BlockType = DynamicBitset::BlockType;

    DynamicBitset db;
    BlockType *data;

    type::Byte bytes[] = {0x12, 0xaf, 0xa5, 0x3c, 0x23, 0x0e};

    db.push(bytes, 6);
    data = db.data();
    qDebug() << QTest::toHexRepresentation((char *)data, db.blockSize());
    QCOMPARE(db.size(), DynamicBitset::SizeType(16+12+2+7+15));
    for (BlockType byte : {0xfc, 0xe4, 0x99, 0xec, 0x02, 0xbc, 0xd0})
        QCOMPARE(*data++, byte);
}

QTEST_MAIN(TestDynamicBitset);
#include "moc_testdynamicbitset.cpp"


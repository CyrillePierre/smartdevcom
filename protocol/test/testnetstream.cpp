#include "testnetstream.hpp"
#include "netstream.hpp"

void TestNetStream::write() {
    NetStream ns;
    ns << 12 << '\n';
    ns << "test" << '\n';
    ns << 4.3 << ' ' << 2.6d << '\n';
    ns.write("salut\n", 6);
}

void TestNetStream::read() {
    NetStream ns;
    int i;
    float f;
    double d;
    char c;
    std::string s;

    ns << "Entrez un entier : ";
    ns >> i;
    ns << "Entrez un float : ";
    ns >> f;
    ns << "Entrez un double : ";
    ns >> d;
    ns << "Entrez un char : ";
    ns >> c;
    std::cin.get();
    ns << "Entrez une chaine : ";
    ns >> s;

    ns << i << ' ' << f << ' ' << d << ' ' << c << ' ' << s << '\n';
}

void TestNetStream::listener() {
    NetStream ns;
    QCOMPARE(ns.listenerEnabled(), true);
    ns.enableListener(false);
    QCOMPARE(ns.listenerEnabled(), false);
    ns.setListener([](std::string const & s){ std::cout << s; },
                   "Event receved.\n");
}

QTEST_MAIN(TestNetStream)
#include "moc_testnetstream.cpp"

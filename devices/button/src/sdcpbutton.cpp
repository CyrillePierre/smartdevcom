#include "sdcpbutton.hpp"
#include "view/view.hpp"
#include "view/list.hpp"

void sdc::SDCPButton::onRise() {
//    _sdcp.request(_addr, vnet::ReqID::test, [] (view::View const &) {
//        std::cout << "Response of test request" << std::endl;
//    });

    _sdcp.request(_addr, vnet::ReqID::getActions, [] (view::View const & v) {
        view::List const & list = static_cast<view::List const &>(v);

        for (view::List::Elem const & elem : list)
            std::cout << "(" << (int) elem.id << ", " << (int) elem.type << ") ";
        std::cout << std::endl;
    });
}

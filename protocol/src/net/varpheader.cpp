#include "varpheader.hpp"

using sdc::net::VARPHeader;

VARPHeader::VARPHeader(uint8_t scAddrSize)
    : version(0),
      op(0),
      scal(0),
      addr_src{0},
      addr_dest{0}
{
    sc_addr_src  = new sdc::type::Byte[scAddrSize];
    sc_addr_dest = new sdc::type::Byte[scAddrSize];
}

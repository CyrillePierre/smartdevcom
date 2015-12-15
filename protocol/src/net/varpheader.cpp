#include "varpheader.hpp"

using sdc::net::VARPHeader;

VARPHeader::VARPHeader(uint8_t scAddrSize)
    : version(0),
      op(0),
      scale(0),
      addrSrc{0},
      addrDest{0}
{
    scAddrSrc  = new sdc::type::Byte[scAddrSize];
    scAddrDest = new sdc::type::Byte[scAddrSize];
}

VARPHeader::~VARPHeader()
{
    delete [] scAddrDest;
    delete [] scAddrSrc;
}

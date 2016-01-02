#include "vipheader.h"

using sdc::vnet::VIPHeader;

const uint8_t VIPHeader::TTL_LIFE = 50;

VIPHeader::VIPHeader(): version(0),
                        ttl(TTL_LIFE),
                        addrSrc{0},
                        addrDest{0}
{
}





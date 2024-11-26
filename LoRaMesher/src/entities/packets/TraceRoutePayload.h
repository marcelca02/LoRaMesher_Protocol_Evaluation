#ifndef _LORAMESHER_DATA_PACKET_H
#define _LORAMESHER_DATA_PACKET_H

#include "BuildOptions.h"

#pragma pack(1)
class TraceRoutePayload final {
public:
    uint8_t ttl;
    uint8_t hopCount;
    uint16_t hops[];
};
#pragma pack()

#endif

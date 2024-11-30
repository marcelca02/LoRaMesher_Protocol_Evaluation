#ifndef _LORAMESHER_DATA_PACKET_H
#define _LORAMESHER_DATA_PACKET_H

#include "BuildOptions.h"

#pragma pack(1)
class TraceRoutePayload final {
public:
    uint8_t ttl;
    uint16_t newhop;
};
#pragma pack()

#endif

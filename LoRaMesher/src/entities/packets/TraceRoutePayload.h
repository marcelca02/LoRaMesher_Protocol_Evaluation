#include "BuildOptions.h"

#pragma pack(1)
class TraceRoutePayload final {
public:
    int8_t ttl;
    uint16_t newhop;
    int8_t id;
};
#pragma pack()

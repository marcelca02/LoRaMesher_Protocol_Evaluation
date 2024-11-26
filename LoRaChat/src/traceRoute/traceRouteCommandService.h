#pragma once

#include "Arduino.h"

#include "commands/commandService.h"

#include "traceRouteMessage.h"

class TraceRouteCommandService: public CommandService {
public:
    TraceRouteCommandService();
};

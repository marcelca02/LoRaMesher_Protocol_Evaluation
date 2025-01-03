#include "traceRouteCommandService.h"
#include "traceRoute.h"

TraceRouteCommandService::TraceRouteCommandService() {
    addCommand(Command("/traceRouteOn", "Set the TraceRoute On specifying the source in hex (like the display)", TraceRouteCommand::TROn, 1,
        [this](String args) {
        return String(TraceRoute::getInstance().traceRouteOn(strtol(args.c_str(), NULL, 16)));
    }));
}
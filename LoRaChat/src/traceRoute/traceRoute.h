#pragma once

#include <Arduino.h>

#include "message/messageService.h"

#include "message/messageManager.h"

#include "traceRouteCommandService.h"

#include "config.h"

#include "LoraMesher.h"

#include "led/led.h"

class TraceRoute : public MessageService {

public: 

    static TraceRoute& getInstance() {
        static TraceRoute instance;
        return instance;
    }

    TraceRouteCommandService* traceRouteCommandService = new TraceRouteCommandService();

    String traceRouteOn(uint16_t dst);

    void createSendingTask();

    String getJSON(DataMessage* message);

    DataMessage* getDataMessage(JsonObject data);

    DataMessage* getTraceRouteMessage(TraceRouteCommand command, uint16_t dst);

    void processReceivedMessage(messagePort port, DataMessage* message);

    void createAndSendTraceRoute();

private:
    
    TraceRoute() : MessageService(TraceRouteApp, "TraceRoute") {
        commandService = traceRouteCommandService;
    }

    TraceRouteCommand traceRouteCommandS; 
    u_int32_t traceRouteValueS;
    int16_t traceRouteDstS;
    String traceRouteAddressesS;

    uint8_t traceRouteId = 0;


    // More private variables for managing the service
    // More private functions for managing the service
    
};


#include "traceRoute.h"
#include <vector>

static const char* TAG = "traceRoute";

static const char* TRACE_ROUTE_TAG = "TraceRouteService";

// LoRaChat default app methods

void TraceRoute::init() {
    pinMode(LED, OUTPUT);
}

String TraceRoute::traceRouteOn(uint16_t dst) {
    std::vector<uint16_t> addresses;
    addresses = LoraMesher::getInstance().traceRoute(dst);
    
    DataMessage* msg = getTraceRouteMessage(TraceRouteCommand::TROn, dst);
    MessageManager::getInstance().sendMessage(messagePort::LoRaMeshPort, msg);

    delete msg;

    String ret; 

    for (size_t i = 0; i < addresses.size(); ++i) {
        ret += String(addresses[i]);
        if (i < addresses.size() - 1) {
            ret += ",";
        }
    }

    return ret;
}

void TraceRoute::processReceivedMessage(messagePort port, DataMessage* message) {
    TraceRouteMessage* traceRouteMessage = (TraceRouteMessage*) message; 

    Log.infoln(F("FF: TraceRoute ::processReceivedMessage  perform local actions") );

    traceRouteCommandS = traceRouteMessage->traceRouteCommand;
    traceRouteValueS = traceRouteMessage->value;
    traceRouteDstS = traceRouteMessage->traceRouteDst;
    
    Log.verboseln(F("FF in TraceRoute::processReceivedMessage traceRouteCommandService %d"),traceRouteCommandService);
    Log.verboseln(F("FF in TraceRoute::processReceivedMessage traceRouteResult %d"),traceRouteValueS);


    switch (traceRouteMessage->traceRouteCommand) {
        case TraceRouteCommand::TROn:
            traceRouteAddressesS = traceRouteOn(traceRouteDstS);
            break;
        case TraceRouteCommand::TROff:
            break;
        default:
            break;
    }
    
    Log.infoln(F("FF: TraceRoute::processReceivedMess  createAndSendTraceRoute()") );
    createAndSendTraceRoute();
}

void TraceRoute::createAndSendTraceRoute() {
    uint16_t messageWithHeaderSize = sizeof(TraceRouteMessage);// + metadataSensorSize;

    TraceRouteMessage* message = new TraceRouteMessage();  // FF: instead of malloc

    Log.verboseln(F("FF Echo::createAndSendTraceRoute: Sending TraceRoute message"));

    if (message) {

        message->appPortDst = appPort::MQTTApp;
        message->appPortSrc = appPort::TraceRouteApp;
        message->addrSrc = LoraMesher::getInstance().getLocalAddress();
        message->addrDst = 0;
        message->messageId = traceRouteId++;

        message->traceRouteCommand = traceRouteCommandS;  //FF added
        message->value = traceRouteValueS;    //FF added
        message->addresses = traceRouteAddressesS;

        message->messageSize = messageWithHeaderSize - sizeof(DataMessageGeneric);

        MessageManager::getInstance().sendMessage(messagePort::MqttPort, (DataMessage*) message);

        delete message;
    }
    else {
        Log.errorln(F("Failed to allocate memory for traceRoute message"));
    }
}

String TraceRoute::getJSON(DataMessage* message) {
    Log.verboseln(F("FF: TraceRoute::getJSON"));
    TraceRouteMessage* traceRouteMessage = (TraceRouteMessage*) message;

    StaticJsonDocument<200> doc;  // FF: was 200

    JsonObject data = doc.createNestedObject("data");

    traceRouteMessage->serialize(data);

    String json;
    serializeJson(doc, json);

    return json;
}

DataMessage* TraceRoute::getDataMessage(JsonObject data) {
    TraceRouteMessage* traceRouteMessage = new TraceRouteMessage();
    Log.infoln(F("TraceRoute::getDataMessage new TraceRouteMessage()") );
    Log.infoln(F("FF: Heap after new TraceRouteMessage(): %d %d %d %d"),ESP.getFreeHeap(), ESP.getMinFreeHeap(), ESP.getHeapSize(), ESP.getMaxAllocHeap());

    traceRouteMessage->deserialize(data);  //FF commented.

    traceRouteMessage->messageSize = sizeof(TraceRouteMessage) - sizeof(DataMessageGeneric);

    return ((DataMessage*) traceRouteMessage);
}

DataMessage* TraceRoute::getTraceRouteMessage(TraceRouteCommand command, uint16_t dst) {
    TraceRouteMessage* traceRouteMessage = new TraceRouteMessage();
    Log.infoln(F("FF TraceRoute::getTraceRouteMessage: new TraceRouteMessage()") );

    traceRouteMessage->messageSize = sizeof(TraceRouteMessage) - sizeof(DataMessageGeneric);

    traceRouteMessage->traceRouteCommand = command;

    traceRouteMessage->appPortSrc = appPort::TraceRouteApp;
    traceRouteMessage->appPortDst = appPort::TraceRouteApp;

    traceRouteMessage->addrSrc = LoraMesher::getInstance().getLocalAddress();
    Log.infoln(F("TraceRoute::getTraceRouteMessage: traceRouteMessage->addrSrc: %d"), traceRouteMessage->addrSrc );
    traceRouteMessage->addrDst = dst;

    return (DataMessage*) traceRouteMessage;
}
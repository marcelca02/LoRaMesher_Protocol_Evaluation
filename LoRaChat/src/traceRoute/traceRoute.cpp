#include "traceRoute.h"

static const char* TAG = "traceRoute";

static const char* TRACE_ROUTE_TAG = "TraceRouteService";

// LoRaChat default app methods

void TraceRoute::init() {
    pinMode(LED, OUTPUT);
}

String TraceRoute::traceRouteOn() {
    digitalWrite(LED, LED_ON);
    ESP_LOGV(TRACE_ROUTE_TAG, "Led On");
    return "TraceRoute On";
}

String TraceRoute::traceRouteOn(uint16_t dst) {
    ESP_LOGV(TRACE_ROUTE_TAG, "Led On to %X", dst);
    if (dst == LoraMesher::getInstance().getLocalAddress())
        return traceRouteOn();

    DataMessage* msg = getTraceRouteMessage(TraceRouteCommand::POn, dst);
    MessageManager::getInstance().sendMessage(messagePort::LoRaMeshPort, msg);

    delete msg;

    return "TraceRoute On";
}

String TraceRoute::traceRouteOff() {
    digitalWrite(LED, LED_OFF);
    ESP_LOGV(TRACE_ROUTE_TAG, "Led Off");
    return "TraceRoute Off";
}

String TraceRoute::traceRouteOff(uint16_t dst) {
    ESP_LOGV(TRACE_ROUTE_TAG, "Led Off to %X", dst);
    if (dst == LoraMesher::getInstance().getLocalAddress())
        return traceRouteOff();

    DataMessage* msg = getTraceRouteMessage(TraceRouteCommand::POff, dst);
    MessageManager::getInstance().sendMessage(messagePort::LoRaMeshPort, msg);

    delete msg;

    return "TraceRoute Off";
}

String TraceRoute::getJSON(DataMessage* message) {
    Log.verboseln(F("FF: TraceRoute::getJSON"));
    TraceRouteMessage* traceRouteMessage = (TraceRouteMessage*) message;

    StaticJsonDocument<400> doc;  // FF: was 200
    //DynamicJsonDocument doc(400); // FF: do not make dynamic

    JsonObject data = doc.createNestedObject("data");

    traceRouteMessage->serialize(data);

    String json;
    serializeJson(doc, json);

    return json;
}

DataMessage* TraceRoute::getDataMessage(JsonObject data) {
    TraceRouteMessage* traceRouteMessage = new TraceRouteMessage();
    Log.infoln(F("TraceRoute::getDataMessage new TraceRouteMessage()") );
    //Log.infoln(F("FF: Heap after new TraceRouteMessage() getFreeHeap() :%d"), ESP.getFreeHeap() );
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

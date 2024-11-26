#include "Arduino.h"

#include "ArduinoLog.h"

#include "message/dataMessage.h"

#pragma pack(1)

enum TraceRouteCommand: uint8_t {
    POff = 0,
    POn = 1
};

class TraceRouteMessage: public DataMessageGeneric {
public:
    TraceRouteCommandService traceRouteCommand;
    u_int32_t value;

    void serialize(JsonObject& doc) {
        // Call the base class serialize function
        ((DataMessageGeneric*) (this))->serialize(doc);

        // Add the derived class data to the JSON object
        
        doc["traceRouteCommand"] = traceRouteCommand;
        doc["traceRoute"] = value;
        Log.verboseln(F("FF in class TraceRouteMessage: void serialize flkwsCommand %d"), traceRouteCommand);
        Log.verboseln(F("FF in class TraceRouteMessage: void serialize value %d"), value);
        
    }

    void deserialize(JsonObject& doc) {
        // Call the base class deserialize function
        ((DataMessageGeneric*) (this))->deserialize(doc);

        // Add the derived class data to the JSON object
        Log.verboseln(F("FF in class TraceRouteMessage: deserialize: seeing local variables in TraceRouteMessage class"));

        traceRouteCommand = doc["traceRouteCommand"];
        Log.verboseln(F("FF in class traceRouteMessage: void deserialize %d"),traceRouteCommand );
        value = doc["traceRoute"];
        Log.verboseln(F("FF in class TraceRouteMessage: void deserialize %d"), value);
    }
};
#pragma pack()
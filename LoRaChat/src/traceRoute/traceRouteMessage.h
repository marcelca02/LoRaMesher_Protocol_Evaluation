#include "Arduino.h"

#include "ArduinoLog.h"

#include "message/dataMessage.h"

#pragma pack(1)

enum TraceRouteCommand: uint8_t {
    TROn = 0,
    TROff = 1
};

class TraceRouteMessage: public DataMessageGeneric {
public:
    TraceRouteCommand traceRouteCommand;
    u_int32_t value;
    int16_t traceRouteDst;
    String addresses;

    void serialize(JsonObject& doc) {
        // Call the base class serialize function
        ((DataMessageGeneric*) (this))->serialize(doc);

        // Add the derived class data to the JSON object
        
        doc["traceRouteCommand"] = traceRouteCommand;
        Log.verboseln(F("FF in class TraceRouteMessage: void serialize traceRouteCommand %d"), traceRouteCommand);
        doc["traceRouteResult"] = value;
        Log.verboseln(F("FF in class TraceRouteMessage: void serialize value %d"), value);
        doc["traceRouteAddresses"] = addresses;
        Log.verboseln(F("FF in class TraceRouteMessage: void serialize addresses %d"), addresses);
        
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
        traceRouteDst = doc["traceRouteDst"];
        Log.verboseln(F("FF in class TraceRouteMessage: void deserialize %d"), traceRouteDst);
        
    }
};
#pragma pack()
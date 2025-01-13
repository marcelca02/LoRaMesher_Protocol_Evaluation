import paho.mqtt.client as mqtt
import json
import time
import argparse

# Configuración del broker MQTT
BROKER_ADDRESS = "localhost"  # Cambia esto a la dirección de tu broker
PORT = 1883
TIMEOUT = 60

# Variables globales para almacenar el resultado
trace_route_result = None
trace_route_addresses = None

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conectado al broker MQTT")
    else:
        print(f"Error de conexión, código: {rc}")

def on_message(client, userdata, msg):
    global trace_route_result, trace_route_addresses

    # Procesar el mensaje recibido
    payload = json.loads(msg.payload.decode())
    data = payload.get("data", {})

    if "traceRouteResult" in data:
        trace_route_result = data["traceRouteResult"]
        trace_route_addresses = data.get("traceRouteAddresses", [])
        print("Respuesta recibida del trace route:")
        print(json.dumps(data, indent=2))

def publish_trace_route(client, origin, destination, gateway):
    topic = f"from-server/{gateway}"
    message = {
        "data": {
            "appPortDst": 18,
            "appPortSrc": 18,
            "addrDst": int(origin),
            "traceRouteCommand": 0,
            "traceRouteDst": int(destination)
        }
    }

    client.publish(topic, json.dumps(message))


def main():
    parser = argparse.ArgumentParser(description="Trace Route para LoRaMesher usando MQTT")
    parser.add_argument("origin", type=int, help="Dirección origen")
    parser.add_argument("destination", type=int, help="Dirección destino")
    parser.add_argument("gateway", type=int, help="Dirección gateway")
    args = parser.parse_args()

    origin = args.origin
    destination = args.destination
    gateway = args.gateway

    # Crear cliente MQTT
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # Conectar al broker MQTT
    client.connect(BROKER_ADDRESS, PORT, 60)

    # Suscribirse al topic para recibir respuestas
    topic_subscribe = f"to-server/{gateway}"
    client.subscribe(topic_subscribe)
    print(f"Suscrito al topic {topic_subscribe}")

    # Iniciar loop en segundo plano
    client.loop_start()

    # Enviar solicitud de trace route
    publish_trace_route(client, origin, destination, gateway)

    # Esperar respuesta durante 10 segundos
    timeout = time.time() + TIMEOUT 
    while time.time() < timeout:
        if trace_route_result is not None:
            break
        time.sleep(1)

    # Mostrar resultado
    if trace_route_result is not None:
        print(f"Resultado del trace route: {trace_route_result}")
        print(f"Direcciones: {trace_route_addresses}")
    else:
        print("No se recibió respuesta dentro del tiempo límite.")

    # Finalizar conexión MQTT
    client.loop_stop()
    client.disconnect()


if __name__ == "__main__":
    main()


# LoRaMesher-Protocol-evaluation

Este proyecto incluye una versión del framework **LoRaChat** y una versión de la librería **LoRaMesher**, con una herramienta de diagnóstico Traceroute, y un script Python para automatizarla en LoRaChat. 

## Estructura del Proyecto

La estructura del proyecto está organizada de la siguiente manera:

```
├── LoRaChat/                # Implementación personalizada del framework LoRaChat
├── LoRaMesher/              # Versión adaptada de la librería LoRaMesher
└── traceRoute.py            # Script para la herramienta Traceroute
```

### 1. LoRaChat
El directorio `LoRaChat` contiene la implementación del framework **LoRaChat**, que actúa como una capa de abstracción para facilitar la comunicación entre aplicaciones y la red mesh basada en LoRaMesher. Su estructura modular permite interactuar con diferentes tecnologías de red como MQTT, HTTP y Bluetooth.

#### Características principales:
- Inclusión de la aplicación `traceRoute` en la carpeta `src/traceRoute` para análisis de rutas.

### 2. LoRaMesher
El directorio `LoRaMesher` contiene la librería **LoRaMesher**, adaptada para soportar funcionalidades avanzadas de redes mesh sobre LoRa.

#### Mejoras y características respecto a la versión estable:
- Nuevo tipo de paquete de control TRACE_P dedicado a hacer un Traceroute 
- Método público de 'traceRoute' para hacer un Traceroute a un destino de la red

### 3. Traceroute
El script `traceRoute.py` implementa una herramienta de diagnóstico para redes mesh basadas en LoRaMesher.

#### Funcionalidad:
- Permite analizar la conectividad y descubrir las rutas entre dos nodos en la red.
- Automatiza el proceso de traceroute tomando como argumentos:
  - **Dirección de origen.**
  - **Dirección de destino.**
  - **Gateway** (opcional, si es necesario).

#### Uso:
Para ejecutar el script, utiliza el siguiente comando:
```bash
python3 traceRoute.py <origen> <destino> <gateway>
```
Ejemplo:
```bash
python3 traceRoute.py 0x1234 0x4567 0x1234
```
Este comando traza la ruta desde el nodo `0x1234` al nodo `0x4567`, utilizando `0x1234` como gateway.

## Instalación y Ejecución

1. **Configurar LoRaMesher y LoRaChat:**
   - Sigue las instrucciones en la carpeta correspondiente para cargar el código en los dispositivos LoRa.

2. **Ejecutar Traceroute:**
   - Asegúrate de tener Python instalado.
   - Ejecuta el script `traceRoute.py` con los argumentos necesarios.

## Contribuciones
Este proyecto fue desarrollado como parte de un análisis y mejora de redes mesh basadas en LoRa.

---
¡Gracias por explorar este proyecto! 🚀

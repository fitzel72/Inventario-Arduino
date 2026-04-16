# Sistema de Inventario RFID con Arduino

## Descripción del proyecto  
Este proyecto consiste en un sistema de inventario basado en tecnología RFID que permite registrar automáticamente la entrada y salida de productos.  

Al acercar una tarjeta o llavero RFID, el sistema identifica el elemento, determina si corresponde a una entrada o salida y guarda el registro junto con la fecha y hora en una tarjeta microSD.  

Su propósito es ofrecer una solución práctica y accesible para el control de inventarios mediante el uso de sensores y microcontroladores.

--------

## Requisitos e instalación  

### Hardware  
- Arduino Nano  
- Módulo RFID RC522  
- Módulo lector de tarjetas microSD  
- Módulo RTC DS1307  
- Tarjeta microSD  
- Tarjetas o llaveros RFID  
- Protoboard  
- Cables puente
- Resistencia de 330 ohms 

### Software  
- Arduino IDE  
- Librerías:
  - MFRC522 (GitHub)  
  - SD (Arduino)  
  - RTClib (Adafruit)  

### Instalación  

1. Clonar el repositorio:
```bash
git clone https://github.com/fitzel72/Inventario-Arduino.git
```

2. Abrir el archivo `Inventario.ino` en Arduino IDE  

3. Instalar las librerías necesarias desde el gestor de bibliotecas  

4. Conectar los módulos:

**RFID RC522 (SPI)**  
- SDA → D10  
- SCK → D13  
- MOSI → D11  
- MISO → D12  

**microSD (SPI)**  
- CS → D4  
- SCK → D13  
- MOSI → D11  
- MISO → D12  

**RTC DS1307 (I2C)**  
- SDA → A4  
- SCL → A5  

5. Seleccionar la placa Arduino Nano y el puerto correspondiente  
6. Compilar y subir el código  

--------

## Cómo usarlo  

1. Conectar el sistema mediante USB  
2. Subir el código al Arduino  
3. Acercar una tarjeta RFID al lector  
4. El sistema registrará:
   - ID del producto  
   - Tipo de movimiento (entrada/salida)  
   - Fecha y hora  
5. Los datos se almacenan en la tarjeta microSD  

(Opcional) Usar el monitor serial para visualizar los datos en tiempo real  

--------

## Estructura del proyecto  

```
- README.md
- inventario.ino
- /diagramas
   - diagrama-bloques.png
   - diagrama-esquematico.png
   - diagrama-pictorico.png
```

--------

## Diagramas de arquitectura  

El sistema se organiza en los siguientes módulos:

- Entrada: RFID RC522  
- Procesamiento: Arduino Nano  
- Almacenamiento: microSD  
- Tiempo: RTC DS1307  

Flujo del sistema:  
RFID → Arduino → RTC → microSD  

--------

## Resumen técnico del sistema  

- Microcontrolador: Arduino Nano  
- Comunicación SPI: RFID y microSD  
- Comunicación I2C: RTC  
- Registro de datos en memoria externa (microSD)  
- Sistema de lectura continua en ciclo (loop)  
- Identificación de eventos de entrada y salida  

--------

## Guía paso a paso de instalación  

1. Instalar Arduino IDE  
2. Instalar librerías (MFRC522, SD, RTClib)  
3. Conectar los módulos correctamente  
4. Insertar la tarjeta microSD  
5. Cargar el código en el Arduino  
6. Alimentar el sistema  
7. Probar con tarjetas RFID  

--------

## FAQ (Preguntas frecuentes)

**¿Por qué no detecta la tarjeta RFID?**  
Verifica las conexiones SPI y que el módulo esté alimentado correctamente (3.3V), además de revisar la resistencia de 330 ohms.

**¿Por qué no se guardan los datos en la microSD?**  
Asegúrate de que esté formateada en FAT32 y bien insertada, si se necesita formatear la memoria, es necesario no realizar un formateo rápido.

**¿Por qué la fecha y hora son incorrectas?**  
El módulo RTC debe configurarse previamente.

**¿Cómo sé si es entrada o salida?**  
El sistema lo determina automáticamente según la lógica del código.

**¿Puedo usar otro Arduino?**  
Sí, siempre que sea compatible con SPI e I2C.

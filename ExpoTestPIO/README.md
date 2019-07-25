#ExpoText

Programa 

# For Develod

Segid las siguientes recomendaciones para el desarrollo del codigo:

Si se esta desarrollando las aplicaicon web cree la carpeta data para guardar los ficheros.

## Programación OTA 



EL modulo ESP-WROM02 permite subir el skeact por medio de OTA.Para subir el proyecto al microcontrolador se debe correr el siguiente comando desde la consola de platformio:

```bash
pio run  -t upload -e esp_wroom_02_OTA
```
Para actualizar el ficheros en SPIFFS

```bash
pio run  -t uploadfs -e esp_wroom_02_OTA
```

**NOTA:** La primera instalacion del programa se debe realizar por serial.
**NOTA:** Si se sube por serial no se puede tener el monitor abierto.
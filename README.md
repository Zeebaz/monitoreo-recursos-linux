# monitoreo-recursos-linux

Dashboard simple para obtener información sobre la memoria RAM y CPU del sistema haciendo uso de módulos del kernel escritos en C. 

## GCC y Make
Instalaciones necesarias para manejo de modulos en linux
```
sudo apt install build-essential
sudo apt-get install manpages-dev
```

# Modulo
## Creación y eliminación de modulo
Para compilar archivo, se debe de estar en el directorio con las configuraciones del modulo y archivo **Makefile** (archivo para compilación de modulo)
```
make all
```

Comando para limpiar modulo (limpia todos los archivos creados)
```
make clean
```

**Por cada cambio a realizar se debe de realizar un make alll y make clean**

## Acciones con modulo

Obtener los mensajes de entrada y salida del modulo
```
sudo dmesg
```


Limpiar los mensajes de salida
```
sudo dmesg -C
```


Insertar modulo, despues usa **dmesg** para ver mensaje de inserción de modulo.
```
sudo insmod <<nombre_modulo>>.ko
```

Verificar informacion de los procesos en el directorio proc/
```
cd /proc
```

Listar modulos y deberia de visualizar su modulo
```
ls
```

Leer archivo escrito
```
cat <<nombre_modulo>>
```

Desmontar modulo, despues usa **dmesg** para ver mensaje de eliminación de modulo.
```
sudo rmmod <<nombre_modulo>>.ko
```


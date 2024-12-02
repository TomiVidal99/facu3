# Entregable práctica 4

## TODO
- [ ] Hay que hacer que la llave pública implemente la encriptación.

## Interpretación de los problemas dados

### Redes

### Cliente TCP

Se requiere que se haga un cliente capaz de recibir una secuencia de 26 enteros encriptados, los cuales deben ser desencriptados y presentados en pantalla (por la _salida estándard_); y luego una palabra de confirmación de finalizado (_FIN_) de la cual debe hacer eco al servidor (es decir enviarla al mismo). Esta debe hacerse mediante el uso de librerías estándares, además tiene que se capaz de recibir por argumentos la *IP* y el *puerto* al que se tiene que conectar.

### Servidor TCP

Se requiere un servidor capaz de enviar números de 0 al 26 encriptados (mediante una clave pública provista por el cliente que se conecta). El mismo debe emitir la cadena _FIN_ cuando finalice el envío de los números. También se debe programar con librerías estándares.


## diagrama de flujo del algoritmo implementado
<!-- ![diagrama de flujo](./diagFlujoTP3.png) -->
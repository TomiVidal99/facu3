## TCP y UDP
- Multiplexan
- No hay garantía en el orden (osea no es su rol)
### TCP (Transmission Control Protocol)
Mensajes de sincronizacion:
- SYN
- SYN ACK
- ACK


### Checkeos
- Overflow (demanda/concurrencia) (CONTROL DE FLUJO)
- De bits checksum? (CONTROL DE CONGESTIÓN)

CRFC -> Especificaciones

NATP -> matcheo de puertos e IPs para tener más dispositivos que puedan comunicarse con redes externas


## Comandos
- ss -anultp
- nc "IP" "PORT" -> POR DEFECTO TCP
- ip route -> revelar tabla de enroutamiento -> se podría implementar con el valor de la cabecera TTL


## Preservar topologías en core
- save y resto
- Entrar al config y configurar la tabla con comandos
		- Apagar, servicios -> staticroute.sh -> agregar los comandos -> activar el servicio staticroute

ip route add "cual"/24 via "el router que lo contiene"


# Preguntas TP 4

1. En la asignación de las IP, cuál es el criterio para asignar? Ahora asigno dirrecciones divididas equitativamente


# TPC/IP

- Application
- Transport
- Network
- Data Link
- Physical


## Configurar NAT

```bash
iptables -t nat -A POSTROUTING -s 172.16.0.0/22 -o eth0 -j MASQUERADE
```
- `-t nat`: Indica que estamos configurando la tabla NAT.
- `-A POSTROUTING`: Aplicará NAT después de que el paquete haya sido procesado.
- `-s 172.16.0.0/22`: Especifica la red privada (la red interna del router **Electro**).
- `-o eth0`: La interfaz conectada a Internet.
- `-j MASQUERADE`: Permite la traducción de direcciones para cualquier dirección IP pública asignada dinámicamente a la interfaz.

https://www.linuxjournal.com/content/linux-networking-configuring-network-address-translation-nat

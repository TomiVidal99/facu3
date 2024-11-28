## TCP y UDP
- Multiplexan
- No hay garantía en el orden


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

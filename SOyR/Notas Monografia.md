## DHCP (Dynamic Host Configuration Protocol)

1. Capa de aplicación?
2. Automatizar la asignación de IPs (a los hosts o dispositivos) en un red
3. Topología servidor/cliente
4. Se debe configurar la interfaz para que use este protocolo

Funcionamiento:

1. Servidor provee los datos necesarios para la conexión IP, máscara, etc. (el servicio tiene que exitir en el servidor)
2.  DORA
	1. DISCOVER: va a todos los elementos de la red (broadcast).
	2. OFFER: responde con los datos disponibles que tiene el router. Tienen tiempo de concesión (7 días normalmente)
	3. REQUEST: Confirma al servidor que quiere tomar esa IP y etc. (ya conoce la dirección del servidor)
	4. ACKNOWLEDGE: El server responde con un ACKNOWLEDGE confirmando la dirección IP.
3. Provee: IP, MASCARA DE SUBRED, PUERTA DE ENLACE Y DNS
4. Cuando se termina el lease time el cliente pide que se le renueve la IP, entonces ahí el servidor decide que es lo más conveniente, podría ser renovar el tiempo o asignar una IP diferente.
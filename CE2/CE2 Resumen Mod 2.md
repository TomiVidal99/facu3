# Osciladores sinusoidales
![[Osciladores sinusoidales_031121_1625.pdf#page=7&rect=85,39,254,752|Osciladores sinusoidales_031121_1625, p.7]]
![[Osciladores sinusoidales_031121_1625.pdf#page=7&rect=282,136,591,748|Osciladores sinusoidales_031121_1625, p.7]]
![[Osciladores sinusoidales_031121_1625.pdf#page=8&rect=92,37,583,740|Osciladores sinusoidales_031121_1625, p.8]]
## Cómo se sintetiza una resistencia negativa?
- Método 1: Usando un dispositivo cuya caracterísitca de presente una resistencia dinámica negativa. (más usual en microondas)
- Método 2: Realimentación con dispositivos activos
Nosotros en esta materia vemosel método 2:
![[Osciladores sinusoidales_031121_1625.pdf#page=10&rect=186,193,484,595|Osciladores sinusoidales_031121_1625, p.10]]

## El famoso y siempre bien ponderado Colpitts
![[Osciladores sinusoidales_031121_1625.pdf#page=11&rect=115,71,271,319|Osciladores sinusoidales_031121_1625, p.11]]
Acá hay que acordase de la topología y que los componentes comparten corriente solamente, desp el resto sale sólo practicamente.

![[Osciladores sinusoidales_031121_1625.pdf#page=14&rect=26,22,579,755|Osciladores sinusoidales_031121_1625, p.14]]

En ambos casos buscamos que los polos se hagan cero 1-AGH=0, es decir que AGH=1 (condición de Barkhausen)

![[Osciladores sinusoidales_031121_1625.pdf#page=20&rect=236,95,449,695|Osciladores sinusoidales_031121_1625, p.20]]

Todos estos circuitos se pueden pensar como:
![[Osciladores sinusoidales_031121_1625.pdf#page=16&rect=191,271,379,595|Osciladores sinusoidales_031121_1625, p.16]]
![[Osciladores sinusoidales_031121_1625.pdf#page=22&rect=80,39,590,686|Osciladores sinusoidales_031121_1625, p.22]]

## Puente de Wein
Hay que fijarse bien donde corta el lazo, es decir que considera Vi y Vo, entonces la transferencia sale fácil:![[Osciladores sinusoidales_031121_1625.pdf#page=36&rect=154,33,530,358|Osciladores sinusoidales_031121_1625, p.36]]
![[Osciladores sinusoidales_031121_1625.pdf#page=36&rect=154,413,244,613|Osciladores sinusoidales_031121_1625, p.36]]

![[Osciladores sinusoidales_031121_1625.pdf#page=37&rect=85,34,198,686|Osciladores sinusoidales_031121_1625, p.37]]

El problema de esta configuración del puente de Wein es que si no está justo justo justo a la ganancia correcta o se atenúa o se satura, entonces hay que poner un AGC (automatica gain control)

Hay varias formas de tener AGC: puede ser con una lámpara, diodos o un dispositivo activo como un FET
![[Osciladores sinusoidales_031121_1625.pdf#page=46&rect=137,80,364,399|Osciladores sinusoidales_031121_1625, p.46]]

![[Osciladores sinusoidales_031121_1625.pdf#page=47&rect=123,51,390,276|Osciladores sinusoidales_031121_1625, p.47]]

![[Osciladores sinusoidales_031121_1625.pdf#page=48&rect=92,41,499,474|Osciladores sinusoidales_031121_1625, p.48]]

# Osciladores con cristales

![[Osciladores sinusoidales_031121_1625.pdf#page=51&rect=80,33,395,560|Osciladores sinusoidales_031121_1625, p.51]]
![[Osciladores sinusoidales_031121_1625.pdf#page=51&rect=396,54,592,738|Osciladores sinusoidales_031121_1625, p.51]]

## Ventajas del cristal:
- Alto Q
- Alta estabilidad en frecuencia
- No hay que fabricar el L
Igual requieren de dispositivos activos claramente:

![[Osciladores sinusoidales_031121_1625.pdf#page=52&rect=82,50,499,411|Osciladores sinusoidales_031121_1625, p.52]]

![[Osciladores sinusoidales_031121_1625.pdf#page=55&rect=85,48,483,680|Osciladores sinusoidales_031121_1625, p.55]]

# Osciladores NO sinusoidales

![[Osciladores No-sinusoidales_031121_1644.pdf#page=1&rect=165,84,573,660|Osciladores No-sinusoidales_031121_1644, p.1]]

# Importante consejo
Estos tipos de circuitos involucran muchos operacionales, una buena forma de encarar los problemas es asumir un estado inicial del o los OP-AMP/Comparadores

Esto no es un oscilador como tal, sino un bloque fundamental de algunos diseños
![[Osciladores No-sinusoidales_031121_1644.pdf#page=4&rect=38,17,576,771|Osciladores No-sinusoidales_031121_1644, p.4]]

![[Osciladores No-sinusoidales_031121_1644.pdf#page=6&rect=83,43,291,598|Osciladores No-sinusoidales_031121_1644, p.6]]

![[Osciladores No-sinusoidales_031121_1644.pdf#page=7&rect=91,46,310,528|Osciladores No-sinusoidales_031121_1644, p.7]]

## Generador  de onda cuadrada
![[Osciladores No-sinusoidales_031121_1644.pdf#page=9&rect=200,456,380,754|Osciladores No-sinusoidales_031121_1644, p.9]]
![[Osciladores No-sinusoidales_031121_1644.pdf#page=11&rect=276,242,515,534|Osciladores No-sinusoidales_031121_1644, p.11]]


## Onda cuadrada de ciclo variable
Se pueden independizar los $\tau$ en la carga y la descarga agregando un único camino para cada caso
![[Osciladores No-sinusoidales_031121_1644.pdf#page=12&rect=159,57,382,339|Osciladores No-sinusoidales_031121_1644, p.12]]

## Onda triangular

![[Osciladores No-sinusoidales_031121_1644.pdf#page=13&rect=167,40,371,332|Osciladores No-sinusoidales_031121_1644, p.13]]

![[Osciladores No-sinusoidales_031121_1644.pdf#page=14&rect=72,37,277,742|Osciladores No-sinusoidales_031121_1644, p.14]]
![[Osciladores No-sinusoidales_031121_1644.pdf#page=14&rect=338,37,456,764|Osciladores No-sinusoidales_031121_1644, p.14]]
con distintos $R_{s}$ se pueden lograr diferentes tipos de ondas triangulares, pero depende de las características del FET

## Onda triangular y cuadrada

![[Osciladores No-sinusoidales_031121_1644.pdf#page=15&rect=158,32,586,766|Osciladores No-sinusoidales_031121_1644, p.15]]

Después hay otros circuitos como los VCO con PUTs y otros integrados, pero dudo que los tomen



# Amplificador clase C
Hay con válvulas para grandes potencias (KW) o transistorizados para bajas potencias

![[amplisintoGS_051119_0903.pdf#page=9&rect=77,64,545,743|amplisintoGS_051119_0903, p.9]]

![[amplisintoGS_051119_0903.pdf#page=11&rect=63,55,560,370|amplisintoGS_051119_0903, p.11]]
Básicamente el pentodo resuelve el problema de alta capacidad de salida, para poder transmitir a mayor frecuencia

![[amplisintoGS_051119_0903.pdf#page=13&rect=74,55,570,805|amplisintoGS_051119_0903, p.13]]
La idea es mandar pulsos de corriente que el filtro los convierte en sinusoides

## Tanque a frecuencia fundamental (el caso que se trata en la materia)
- Tensión de grilla: sinusoidal a fo montada en –Vp (tensión de polarización)
- Tensión de placa: sinusoidal a fo montada en Vplaca (tensión de alim. de placa)
- Fase relativa entre ambas: 180 grados, cátodo común (carga colgada en placa, equivalente a emisor común)Fase relativa entre ambas: 180 grados, cátodo común (carga colgada en placa, equivalente a emisor común)

![[amplisintoGS_051119_0903.pdf#page=15&rect=79,68,568,791|amplisintoGS_051119_0903, p.15]]

## Puntos elementales en el diseño
- Necesito saber qué pulso de corriente tiene que circular por la placa para entregar la potencia deseada a la carga
- Necesito saber cómo polarizar la reja y qué corriente debo entregarle
Adicionalmente se requiere:
- Punto de funcionamiento
- Fuente de alimentación (tensión y potencia)
- Valores de polarización.

## Para hacer esto se emplea el método gráfico de Chafee (1936)
Como las características de las válvulas son consistentes en las mismas (no hay tanta dispersión como en los transistores) el método es bastante preciso.
![[amplisintoGS_051119_0903.pdf#page=20&rect=69,68,586,772|amplisintoGS_051119_0903, p.20]]
De diseñar esta recta de carga se obtienen los diferentes valores de la corriente (25A, 20A, 15A, 10A, 5A, 1A) y con los mismos se hacen los calculos propuestos por Chafee:
![[amplisintoGS_051119_0903.pdf#page=21&rect=66,60,563,719|amplisintoGS_051119_0903, p.21]]
Con las mismas fórmlas y las características de corriente constante también se pueden obtener:
- Valor medio de la corriente de reja
- Valor pico de la primera armónica de la corriente de reja
(esto es lo que el driver debe entregar)
![[amplisintoGS_051119_0903.pdf#page=23&rect=70,61,578,786|amplisintoGS_051119_0903, p.23]]

![[amplisintoGS_051119_0903.pdf#page=24&rect=72,64,524,726|amplisintoGS_051119_0903, p.24]]

## Balances de potencia
$$P_{grilla} = P_{VRF} + P_{Vp}$$
![[amplisintoGS_051119_0903.pdf#page=28&rect=94,77,396,466|amplisintoGS_051119_0903, p.28]]

Para diseñar el filtro que adapta la carga y filtra los armónicos se emplea la nota de motorola AN297
Recordar:
$$\eta = 1- \frac{Q_{c}}{Q_{D}}$$
# Amplificadores Clase C transistorizados
![[amplisintoGS_051119_0903.pdf#page=50&rect=86,80,576,748|amplisintoGS_051119_0903, p.50]]
![[amplisintoGS_051119_0903.pdf#page=52&rect=77,80,573,645|amplisintoGS_051119_0903, p.52]]

Cuando se diseña usando este método sólo hay que tener en cuenta que el transistor pondrá una resistencia de salida y Capacidad de salida equivalente que hay que considerar.

## Calculo de consumo de potencia de la fuente:
![[TP6 P3 Clase C transistor 111202-imprimir-1.pdf#page=13&rect=123,607,452,711|TP6 P3 Clase C transistor 111202-imprimir-1, p.13]]


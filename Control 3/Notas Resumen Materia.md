![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=19&rect=180,136,825,239|Tema 01 - IntroduccionControlRobusto_2023, p.19]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=19&rect=284,8,675,89|Tema 01 - IntroduccionControlRobusto_2023, p.19]]

## Sistema bien planteado (definición)
Significa que todas las transferencias de lazo cerrado existen.
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=23&rect=12,262,490,454|Tema 01 - IntroduccionControlRobusto_2023, p.23]]
El sistema está automáticamente bien planteado si k,f y g son propias, y una de ellas estrictamente propia. (por lo general g es estrictamente propia)
Si no se puede emplear lo siguiente:
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=24&rect=72,286,377,403|Tema 01 - IntroduccionControlRobusto_2023, p.24]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=25&rect=12,186,581,267|Tema 01 - IntroduccionControlRobusto_2023, p.25]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=25&rect=589,134,959,398|Tema 01 - IntroduccionControlRobusto_2023, p.25]]


# Estabilidad interna nominal
Se trata de explicar que si bien existe una estabilidad relacionada al par entrada-salida. No significa que internamente el sistema sea estable, es decir que internamente puede que una transferencia sea inestable.
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=30&rect=8,20,943,445|Tema 01 - IntroduccionControlRobusto_2023, p.30]]
Fundamentalmente me quedaría con el Lema de la no cancelación. Porque es más fácil de aplicar.

# Control robusto
Para la teoría de control robusto, estabilidad robusta significa estabilidad de todos los posibles modelos que son descriptos por la combinación
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=33&rect=90,235,494,323|Tema 01 - IntroduccionControlRobusto_2023, p.33]]![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=33&rect=599,224,935,328|Tema 01 - IntroduccionControlRobusto_2023, p.33]]
Este conjunto de modelos de planta pueden ser escritos como una familia de modelos
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=33&rect=207,76,632,125|Tema 01 - IntroduccionControlRobusto_2023, p.33]]

Para tener en cuenta la incertidumbre se emplean modelos de incertidumbre dinámica global:
En particular usamos la mulitplicativa, pero existen otras que se ajustan mejor dependiendo del caso a tratar:
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=39&rect=83,241,555,417|Tema 01 - IntroduccionControlRobusto_2023, p.39]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=39&rect=606,236,948,421|Tema 01 - IntroduccionControlRobusto_2023, p.39]]

La función de peso $W(s)$ representa la "dinámica" de la incertidumbre, en otras palabras su "distribución en frecuencia".

# Estabilidad robusta
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=43&rect=79,273,435,324|Tema 01 - IntroduccionControlRobusto_2023, p.43]]
La noción de robustez requiere de un controlador, un conjunto de plantas y alguna característica del sistema.

## Interpretación gráfica 
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=44&rect=16,178,654,273|Tema 01 - IntroduccionControlRobusto_2023, p.44]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=44&rect=670,137,954,395|Tema 01 - IntroduccionControlRobusto_2023, p.44]]

# Teorema de pequeña ganancia

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=45&rect=615,40,951,399|Tema 01 - IntroduccionControlRobusto_2023, p.45]]

## Otros modelos
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=46&rect=89,218,588,352|Tema 01 - IntroduccionControlRobusto_2023, p.46]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=46&rect=605,93,954,446|Tema 01 - IntroduccionControlRobusto_2023, p.46]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=47&rect=195,173,753,360|Tema 01 - IntroduccionControlRobusto_2023, p.47]]

# Performance nominal
En control clásico la medida de performance del sistema a lazo cerrado está basada en la habilidad del mismo en rechazar perturbaciones conocidas (se conoce la forma de la perturbación, no se conoce el tiempo en el que la misma ocurre).

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=54&rect=16,280,933,450|Tema 01 - IntroduccionControlRobusto_2023, p.54]]

## Interpretación gráfica

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=55&rect=37,219,597,266|Tema 01 - IntroduccionControlRobusto_2023, p.55]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=55&rect=607,22,900,241|Tema 01 - IntroduccionControlRobusto_2023, p.55]]

# Performance robusta
El objetivo final del control robusto es conseguir los requerimientos de performance para todos los miembros de la familia de modelos, es decir performance robusta con un solo controlador.

Estabilidad robusta y performance nominal son prerrequisitos para poder obtener performance robusta.

Recordar que las condiciones necesarias y suficientes para performance nominal y estabilidad robusta son:
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=56&rect=680,245,896,342|Tema 01 - IntroduccionControlRobusto_2023, p.56]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=56&rect=28,108,651,261|Tema 01 - IntroduccionControlRobusto_2023, p.56]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=56&rect=518,13,954,228|Tema 01 - IntroduccionControlRobusto_2023, p.56]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=57&rect=512,24,908,310|Tema 01 - IntroduccionControlRobusto_2023, p.57]]

# Loopshaping

Método gráfico que funciona muy bien para plantas SISO de mínima fase estables.

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=62&rect=11,15,600,372|Tema 01 - IntroduccionControlRobusto_2023, p.62]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=62&rect=607,121,943,223|Tema 01 - IntroduccionControlRobusto_2023, p.62]]

## Procedimiento
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=66&rect=602,134,956,365|Tema 01 - IntroduccionControlRobusto_2023, p.66]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=66&rect=9,4,599,449|Tema 01 - IntroduccionControlRobusto_2023, p.66]]


# Sistemas con retardo

![[Tema 02 - Sistemas con retardo_2024.pdf#page=29&rect=4,34,909,456|Tema 02 - Sistemas con retardo_2024, p.29]]

## Aproximaciones (modelos)
![[Tema 02 - Sistemas con retardo_2024.pdf#page=14&rect=608,42,952,171|Tema 02 - Sistemas con retardo_2024, p.14]]
![[Tema 02 - Sistemas con retardo_2024.pdf#page=14&rect=614,334,948,449|Tema 02 - Sistemas con retardo_2024, p.14]]
### Y hay otros, como el polo-cero

# Modelos de sistemas con retardo
## FOPDT
![[Tema 02 - Sistemas con retardo_2024.pdf#page=22&rect=69,152,577,243|Tema 02 - Sistemas con retardo_2024, p.22]]

## SOPDT
![[Tema 02 - Sistemas con retardo_2024.pdf#page=23&rect=18,158,580,348|Tema 02 - Sistemas con retardo_2024, p.23]]

## IPDT (integrative plus dead time)
![[Tema 02 - Sistemas con retardo_2024.pdf#page=24&rect=89,282,531,348|Tema 02 - Sistemas con retardo_2024, p.24]]

## SOIPDT (second order integrative plus dead time)
![[Tema 02 - Sistemas con retardo_2024.pdf#page=24&rect=62,148,589,212|Tema 02 - Sistemas con retardo_2024, p.24]]

## Constante de tiempo dominante o retardo dominante?
La relación entre el retardo y la constante de tiempo asociada con la parte libre de retardo del proceso representa una característica importante del proceso.
Una forma de tener en cuenta esta relación es normalizar el retardo utilizando la constante de tiempo del modelo FOPDT
![[Tema 02 - Sistemas con retardo_2024.pdf#page=27&rect=164,210,409,278|Tema 02 - Sistemas con retardo_2024, p.27]]
![[Tema 02 - Sistemas con retardo_2024.pdf#page=27&rect=14,129,283,197|Tema 02 - Sistemas con retardo_2024, p.27]]
A $\tau$ se la suele llamar "razón de controlabilidad"
# IMPORTANTE
![[Tema 02 - Sistemas con retardo_2024.pdf#page=27&rect=31,48,606,98|Tema 02 - Sistemas con retardo_2024, p.27]]

## Margen de retardo

Para evaluar el efecto que el error en la estimación del retardo tiene sobre la robustez, se define el margen de retardo del sistema como la variación más grande que puede ocurrir en el retardo del proceso 𝑃(𝑠) antes de que el sistema a LC se vuelva inestable.

El margen de retardo $𝐷_{m}$ se define como:
![[Tema 02 - Sistemas con retardo_2024.pdf#page=34&rect=186,186,366,257|Tema 02 - Sistemas con retardo_2024, p.34]]
![[Tema 02 - Sistemas con retardo_2024.pdf#page=34&rect=29,67,533,160|Tema 02 - Sistemas con retardo_2024, p.34]]

Digamos que la definición tiene sentido cuando sólo se cierra el lazo, y sin controlador ni nada.
![[Tema 02 - Sistemas con retardo_2024.pdf#page=34&rect=605,129,953,305|Tema 02 - Sistemas con retardo_2024, p.34]]

# Predictor de Smith (SP)

![[Tema 02 - Sistemas con retardo_2024.pdf#page=43&rect=53,160,513,356|Tema 02 - Sistemas con retardo_2024, p.43]]
![[Tema 02 - Sistemas con retardo_2024.pdf#page=43&rect=704,125,892,202|Tema 02 - Sistemas con retardo_2024, p.43]]
![[Tema 03 - Predictor de Smith_2024.pdf#page=13&rect=77,117,286,205|Tema 03 - Predictor de Smith_2024, p.13]]

- El SP es un caso particular del IMC (Control por Modelo Interno)
- Se require un buena estimación del retardo
- Puede dar mejoras en la respuesta a cambios de referencia, pero puede ser más sensible a incertidumbres de modelado.
- El SP ofrece un mejor rendimiento a costa de una mayor acción de control en los transitorios de la referencia.
- El sistema a lazo cerrado se volvería inestable para pequeñas diferencias entre el modelo y el proceso real
- Las propiedades de rechazo de perturbaciones no se pueden definir arbitrariamente
- El controlador no se puede utilizar con procesos inestables. 
- El SP no puede eliminar los polos de P(s), exepto un polo en el origen
![[Tema 03 - Predictor de Smith_2024.pdf#page=19&rect=78,59,400,126|Tema 03 - Predictor de Smith_2024, p.19]]

![[Tema 03 - Predictor de Smith_2024.pdf#page=19&rect=451,67,954,454|Tema 03 - Predictor de Smith_2024, p.19]]

# SP de dos grados de libertad (SP con filtro)
![[Tema 03 - Predictor de Smith_2024.pdf#page=25&rect=14,102,556,247|Tema 03 - Predictor de Smith_2024, p.25]]
El filtro elimina el sobre pico

![[Tema 03 - Predictor de Smith_2024.pdf#page=27&rect=342,109,540,166|Tema 03 - Predictor de Smith_2024, p.27]]

![[Tema 03 - Predictor de Smith_2024.pdf#page=32&rect=31,146,219,211|Tema 03 - Predictor de Smith_2024, p.32]]

![[Tema 03 - Predictor de Smith_2024.pdf#page=32&rect=607,16,957,415|Tema 03 - Predictor de Smith_2024, p.32]]


# Sintonización de PID para sistemas con retardo

Es un lazo de control clásico con el PID como controlador, pero principalmente hay dos enfoques para el diseño de este PID:

## Basado en predicción
Este enfoque se basa en considerar que se tiene una estructura del SP, donde se puede pensar en el Controlador serie equivalente como un PID, si el controlador primario es uno por adelanto, por lo que se pueden obtener los parámetros que los relacionen, y luego hacer una cancelación para que quede un polo de LC dominante dependiente de los parámetros de diseño.
Para considerar el Ce hay que hacer una aproximación del retardo del sistema, generalmente se usa la de Padé 1

## Asignación de polos
Se aproxima la planta con Padé 1, luego se cancelan los dos polos de la planta con el PID y quedan dos polos y un cero del controlador en el lazo cerrado que se pueden usar para ajustar la dinámica de la planta.

## Importante sobre ambos acercamientos
Debido a la cancelación polo-cero utilizada en los dos diseños, el rechazo de perturbación será pobre si el polo cancelado es lento en comparación con los de lazo cerrado deseados.

# Sintonización para sistemas con retardo dominante

Si se cumple que L >= 2T, para una planta con FOPDT con retardo L y polo en 1+sT, entonces se puede ajustar el PID:
$$P(s) = \frac{K_{p}e^{-Ls}}{(1+Ts)},\ L\geq2T$$
$$C_{x}(s) = \frac{K_{x}(1+Ts)(1+0.5Ls)}{Ts(1+0.5 \alpha Ls)}$$
Se diseñan $K_{x}$ y $\alpha$ para que haya un polo doble en $s=\frac{-1}{T_{0}}$
_Si el proceso es igual al modelo entonces el polo doble garantiza respuestas rápidas sin oscilaciones_
$$\alpha = \frac{4T_{0}^{2}}{(L+4T_{0})L}$$
## Sistemas con integradores
$$P(s) = \frac{K_{v}e^{-Ls}}{s}$$
Se aproxima con Padé:
$$P_{i}(s) = \frac{K_{v}(1-0.5Ls)}{s(1+0.5Ls)}$$


1. Estabilizar la planta con una ganancia $K_{0}=\frac{1}{2K_{v}L}$
2. Sintonía del PID para la planta equivalente (es decir considerar el bloque equivalente de P(s) con la realimentación negativa de $K_{0}$) estable $P_{2}(s)$
	[[Tema 04 - Control PID de Sistemas con retardo_2024.pdf#page=31|Tema 04 - Control PID de Sistemas con retardo_2024, p.31]]
3. Filtro a la referencia: Es necesario un filtro de referencia para atenuar el sobrepaso en la respuesta a la referencia

## Sistemas con constante de tiempo dominante
Si $T>>L$ entonces se considera la siguiente aproximación:
$$P(s) = \frac{K_{p}e^{-Ls}}{Ts+1}\cong\frac{K_{p}e^{-Ls}}{Ts}=\frac{Kve^-Ls}{s}$$
y luego se procede como si fuera una planta integradora

# Funciones descriptivas
Se define la función descriptiva o función sinusoidal descriptiva de un elemento no lineal, como la relación compleja entre la componente armónica fundamental de la salida respecto a la entrada (similar al concepto de respuesta en frecuencia)

# TODO
- MPC
- 2DOF-PID
- FUNC DESC
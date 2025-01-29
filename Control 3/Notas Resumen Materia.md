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

i![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=62&rect=11,15,600,372|Tema 01 - IntroduccionControlRobusto_2023, p.62]]
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=62&rect=607,121,943,223|Tema 01 - IntroduccionControlRobusto_2023, p.62]]

## Procedimiento
![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=66&rect=602,134,956,365|Tema 01 - IntroduccionControlRobusto_2023, p.66]]

![[Tema 01 - IntroduccionControlRobusto_2023.pdf#page=66&rect=9,4,599,449|Tema 01 - IntroduccionControlRobusto_2023, p.66]]


# Sistemas con retardo

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

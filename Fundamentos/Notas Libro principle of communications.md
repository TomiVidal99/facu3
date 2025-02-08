[[Funda Preguntas]]

## Relación Wiener-Khinchine
Dice simplemente que la DEP es la TF de la autocorrelación.

## Transformada de Hilbert
Es una transformada que se usa para facilitar los cálculos y definiciones en las señales de los emisores y receptores.
$$ x_{p(t)} =x(t) + j\hat{x}(t)$$
$$\hat{x}(t) = Hilbert\{x(t)\} = F^{-1}\{ -j.sgn(f).X(f) \}$$$$ X_{p}(f) = X(f)[1+sgn(f)] $$
O lo que es equivalente: $X_{p}(f) = 2.X(f)$ si f > 0, y $X_{p}(f) = 0$ si f<0

### También se define para valores negativos:
$$ x_{n(t)} =x(t) - j\hat{x}(t)$$
$$ X_{p}(f) = X(f)[1-sgn(f)] $$
Estas dos definiciones sirven para considerar los ancho de banda equivalentes:

### Se puede emplear la transformada de Hilbert para hacer la representación compleja de una señal pasa-banda

# Potencia media normalizada a la salida de filtro
Si se saca el ancho de banda equivalente de ruida $B_N$ entonces se puede calcular como:
$$ P_{N_{0}} = N_{0}B_{N}H_{0}^{2}$$
Por lo que sólo abría que saber la densidad espectral de potencia de ruido a la entrada y el máximo del filtro

# Ancho de banda equivalente de ruido
A la salida de un filtro se tiene un ruido filtrado que tiene un ancho de banda siempre mayor que el filtro, para filtros de primer orden se tiene que la relación es $B_{N}=\frac{\pi}{2}BW$ (BW ancho de banda del filtro) y también se cumple para algunos filtros de orden mayor, como por ejemplo uno LC serie. Esto viene dado por la siguiente ecuación:
$$ B_{N} = \frac{1}{2H_{0}}\int_{-\infty}^{+\infty}|H(f)|^{2}df $$
## importante: aclarar que esto es para cuando se considera bilateral (para unilateral solamente sacar el 2)

# Ruido térmico
(Se considera que el espectro es simétrico, osea bilateral)
Se analiza a partir de su potencia media normalizada:
$$ V_{rms}^{2}= <V_{n}^{2}(t)>=4kTRB\ [V^2]$$
$$ i_{rms}^{2}= \frac{<V_{n}^{2}(t)>}{R^{2}}=4kTGB\ [A^2]$$
# Ruido shot
### Polarización directa
$$i_{rms}^{2}=2eI_{t}B\ [A^2]$$
$I_{t}=I+2I_{s}$ , Donde $I_{s}$ es la corriente de saturación inversa.
### Polarización directa
$$i_{rms}^{2}=2eI_{s}B\ [A^2]$$
### Pequeña señal
$$i_{rms}^{2}=2kTg_{0}B\ [A^{2}]$$

# Potencia disponible
Cuando hay matcheo de impedancias se da que la potencia máxima transferida es la mitad, por lo que: $P_{a} =\frac{1}{2}P$ o lo que es equivalente: $P_{a}=\frac{1}{R}(\frac{1}{2}V_{rms})^{2}=\frac{V_{rms}^{2}}{4R}$

# DEP disponible
La DEP disponible unilateral a $T=T_{0}=290°K$
$$S_{a}(f)\cong-204\frac{dBW}{Hz}=-174\frac{dBm}{Hz}$$
# Temperatura equivalente de ruido
Para cualquier fuente de DEP constante se define la temperatura equivalente de ruido:
$$T_{e}=\frac{P_{a}}{kB}\ [°K]$$
Y si la fuente de ruido no es de DEP constante:
$$T_{e}=\frac{2S_{a}(f)}{k}\ [°K]$$


# VCO
![[FdCom_Com_29102024.pdf#page=6&rect=414,150,698,249|FdCom_Com_29102024, p.6]]
![[FdCom_Com_29102024.pdf#page=6&rect=90,38,357,155|FdCom_Com_29102024, p.6]]
![[FdCom_Com_29102024.pdf#page=6&rect=553,28,692,88|FdCom_Com_29102024, p.6]]

# PLL
En condiciones de enganche o cercanas a ella:
![[FdCom_Com_29102024.pdf#page=7&rect=127,161,761,400|FdCom_Com_29102024, p.7]]

## Modelo lineal
![[FdCom_Com_29102024.pdf#page=7&rect=75,37,310,102|FdCom_Com_29102024, p.7]]
![[FdCom_Com_29102024.pdf#page=8&rect=37,291,833,390|FdCom_Com_29102024, p.8]]

Si aumento el rango de captura del PLL tengo más ancho de banda equivalente de ruido 
![[FdCom_Com_29102024.pdf#page=13&rect=34,74,909,416|FdCom_Com_29102024, p.13]]

## Modelo de orden 2

- TODO


# Modulación de pulsos

w
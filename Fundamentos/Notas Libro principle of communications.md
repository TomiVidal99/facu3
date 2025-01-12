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

Se analiza a partir de su potencia media normalizada:
$$ V_{rms}^{2}= <V_{n}^{2}(t)>=4kTRB[V^2]$$
$$ i_{rms}^{2}= \frac{<V_{n}^{2}(t)>}{R^{2}}=4kTGB[A^2]$$

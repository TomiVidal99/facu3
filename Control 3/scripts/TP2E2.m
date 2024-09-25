% Resuelvo el problema 1 del TP 2 de control 3

% Se grafica la plata para los valores extremos de la incerteza
% contexto: se tiene un polo y un retardo de modelo de planta: FOPDT,
% donde el retardo varía entre un mínimo y máximo

s = tf('s');
plantaNominal = 0.04/(30*s+1)

retardoMin = exp(-(14.73e-3)*s)
retardoMax = exp(-(14.73e-3)*s)

figure();
bode(plantaNominal*retardoMin);
figure();
bode(plantaNominal*retardoMax);
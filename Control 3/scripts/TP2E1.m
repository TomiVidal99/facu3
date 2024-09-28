% Se resulve el ej 1 del TP 2 de control 3
close all;

% Contexto: Se tiene una planta con 1 polo y retardo: FOPDT
% el retardo varía entre un mínimo y máximo.
% El objetivo es ver el margen de fase y ganacia para los valores extremos

s=tf('s');

plantaNominal=0.04/(30*s+1)

retardoMin=14.73;
retardoMax=58.90;

plantaNominal.OutputDelay=retardoMin;
figure();
bode(plantaNominal);
title('Retardo minimo');
grid on;

plantaNominal.OutputDelay=retardoMax;
figure();
bode(plantaNominal);
title('Retardo maximo');
grid on;
% Se resulve el ej 2 del TP 2 de control 3
close all;

% Contexto: Se tiene una planta con 1 polo y retardo: FOPDT
% el retardo varía entre un mínimo y máximo.
% El objetivo es ver el bode cuando se emplean aproximaciones del retardo

s=tf('s');

plantaNominal=0.04/(30*s+1)

retardoMax=58.90e-3;
aproxTaylor=1+retardoMax*s
aproxPade=(1-retardoMax*s*0.5)/(1+retardoMax*s*0.5)

figure();
bode(plantaNominal*aproxTaylor);
title('Aprox Taylor');
grid on;

figure();
bode(plantaNominal*aproxPade);
title('Aprox Pade');
grid on;

figure();
plantaNominal.OutputDelay=retardoMax;
bode(plantaNominal);
title('Sin aprox');
grid on;
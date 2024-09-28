% Se resuelve el ejercicio 4 del TP 2
close all;

% Contexto:
% Se tiene una planta de orden 5 y se quiere un modelo de FOPDT 
% y otro modelo SOPDT

s = tf('s');
planta = 1/( (1+120*s)^5 );

t1=350;
FOPDT = 1/(1+t1*s);
FOPDT.OutputDelay=300;

t1=200;
SOPDT = 1/((1+t1*s)^2);
SOPDT.OutputDelay=200;

%[planta_mag, planta_pha, planta_w]=bode(planta); planta_mag=reshape(planta_mag, size(planta_w));
%[FOPDT_mag, FOPDT_pha]=bode(FOPDT, planta_w);FOPDT_mag=reshape(FOPDT_mag, size(planta_w));

%figure; hold on; grid on;
%plot(planta_w, 20*log10(planta_mag), 'r', 'linewidth', 3);
%plot(planta_w, 20*log10(FOPDT_mag), 'b', 'linewidth', 3);

[planta_y, planta_t]=step(planta); planta_y=reshape(planta_y, size(planta_t));
[FOPDT_y, FOPDT_t]=step(FOPDT, planta_t);FOPDT_y=reshape(FOPDT_y, size(planta_t));
[SOPDT_y, SOPDT_t]=step(SOPDT, planta_t);SOPDT_y=reshape(SOPDT_y, size(planta_t));

figure; hold on; grid on;
plot(planta_t, planta_y, 'r', 'linewidth', 3);
plot(planta_t, FOPDT_y, 'b', 'linewidth', 3);
plot(planta_t, SOPDT_y, 'k', 'linewidth', 3);
% Se resuelve el TP2 Ej 2
% Contexto: se quiere hacer control con un PI ajustado por Ziegler-Nichols
% Quarter-decay response

close all;

s=tf('s');

planta=10/((s+4)*(s+2)*(s+0.1));

%% Sistema a lazo abierto
figure('units','normalized','outerposition',[0 0 1 1])
rlocus(planta, [0:1e-1:1e3]); hold on; grid on;
figure('units','normalized','outerposition',[0 0 1 1])
margin(planta); hold on; grid on;

%% Ahora simulo el sistema a lazo cerrado
close all;
controlador=1;
sistema_lc=(planta*controlador)/(1+planta*controlador);
figure('units','normalized','outerposition',[0 0 1 1])
rlocus(sistema_lc); hold on; grid on;
figure('units','normalized','outerposition',[0 0 1 1])
margin(sistema_lc); hold on; grid on;

%% Claramente a este punto se ve que hay que estabilizar la plata
% se procede a hacer un controlador que a LC lleve los polos a -5

% Trabajo de Aplicación 1
% Control Automático 3
% Grupo 10

% IMPORTANTE:
% a data lo normlizo más adelante con respecto a 5v para trabajar entre 0-1
% NOTAS:
% Por ahí estaría bueno cambiar la interpolación en la linealizacion de la
% señal, ahora es de orden 0, estaría bueno usar splines o algo más
% complejo, seguro que eso mejora el error cuadrático medio.

clear all;
close all;
s = tf('s');

%% Load file data
%addpath('c:\Users\tomi\Github\facu3\Control 3\TPA\1');
%savepath;
data = open('prot_sim_data.dat');


%% Code
%disp(dataFile.data);
%size(data.data)

close all;

time = data.data(:,1);
y6 = data.data(:,7)/5; % divido por 5 para normalizar los datos con respecto al pico de 5v

figure();
plot(time, y6, 'r', 'linewidth', 4);
hold on;
grid on;
title('Data');

time_diff = 1e-3;
lineal_time = [0:time_diff:10];
lineal_y6 = zeros(1, length(lineal_time));
n = 2;
while_break = 0;
for (i = 2:length(lineal_time))
    while (lineal_time(i) > time(n) && while_break < 50000)
        n = n + 1;
        while_break = while_break + 1;
    end    
    lineal_y6(i) = y6(n-1);
end

figure;
plot(lineal_time, lineal_y6, 'b', 'linewidth', 4);
hold on;
grid on;
title('Data con tiempo lineal');

%% FOPDT
close all;
% acomodo los datos
step_resp = lineal_y6((3/time_diff):(5/time_diff));
step_resp=step_resp-0.2; % muevo los datos 0.2 porque se comenzó con 20% de duty cycle
step_resp=step_resp/0.6; % escalo a que la referencia sea 1, porque se puso 80% de duty cycle como step
step_time = lineal_time(1:length(step_resp));
step_input = ones(1, length(step_resp)); step_input(1)=0; % esto es para el programa de estimación que necesita una entrada

figure;
plot(step_time, step_resp, 'b', 'linewidth', 4);
hold on;
grid on;
title('Respuesta al escalón (de 20% a 80% ciclo de trabajo)');
plot(step_time, step_input, 'r', 'linewidth', 2);

% De los graficos generados se estima el delay
fopdt_delay = 0.415;
% De System Identification se obtuvieron los siguientes parámetros
fopdt_time_constant = 0.28562;
fopdt_gain = 1;

% Modelo FOPDT resultante
fopdt_estimated = fopdt_gain/(s*fopdt_time_constant+1);
fopdt_estimated.inputDelay = fopdt_delay;

[fopdt_est_y, fopdt_est_t] = step(fopdt_estimated, step_time); fopdt_est_y=reshape(fopdt_est_y, size(step_resp));

% figure;
plot(fopdt_est_t, fopdt_est_y, 'k', 'linewidth', 3);
% hold on;
% grid on;
% title('Modelo FOPDT estimado');

error_fopdt = immse(step_resp, fopdt_est_y);
fprintf('El error cuadrático medio entre la estimada y los datos es: %f', error_fopdt);

legend('Respuesta al escalón (datos)', 'Escalón', sprintf('Respuesta estimada con modelo FOPDT (%f)', error_fopdt));

%% Modelo SOPDT

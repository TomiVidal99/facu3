% Trabajo de Aplicación 1
% Control Automático 3
% Grupo 10

% IMPORTANTE:
% a data lo normlizo más adelante con respecto a 5v para trabajar entre 0-1
% NOTAS:
% 1) Por ahí estaría bueno cambiar la interpolación en la linealizacion de la
% señal, ahora es de orden 0, estaría bueno usar splines o algo más
% complejo, seguro que eso mejora el error cuadrático medio.
% 2) En el modelo de ecuaciones a partir del circuito, para que encaje
% perfecto a los datos hay que agregarle un retardo, no entiendo por qué,
% no debería ser así no?

clear;
close all;
s = tf('s');

%% Load file data
% addpath('c:\Users\tomi\Github\facu3\Control 3\TPA\1');
% savepath;
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
lineal_time = 0:time_diff:10;
lineal_y6 = zeros(1, length(lineal_time));
n = 2;
while_break = 0;
for i = 2:length(lineal_time)
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

fig = figure; set(fig, 'Units', 'Normalized', 'OuterPosition', [0 0 1 1]); set(fig, 'Toolbar', 'none', 'Menu', 'none');
plot(step_time, step_resp, 'b', 'linewidth', 6);
hold on;
grid on;
title('Respuesta al escalón (de 20% a 80% ciclo de trabajo)');
xlabel('Tiempo [Segundos]');
ylabel('Tensión normalizada (a 5V) [Volts]');
plot(step_time, step_input, '--r', 'linewidth', 2);

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
plot(fopdt_est_t, fopdt_est_y, 'k', 'linewidth', 2);
% hold on;
% grid on;
% title('Modelo FOPDT estimado');

error_fopdt = immse(step_resp, fopdt_est_y);
fprintf('El error cuadrático medio entre la estimada y los datos es: %f\n', error_fopdt);

% Modelo SOPDT
% Parámetros obtenidos de System Identification
sopdt_delay = 0.3272;
sopdt_time_constant_1 = 0.1798;
sopdt_time_constant_2 = 5;
sopdt_gain = 1;

% Modelo FOPDT resultante
sopdt_estimated = sopdt_gain/((s*sopdt_time_constant_1+1)*(s*sopdt_time_constant_1+1));
sopdt_estimated.inputDelay = sopdt_delay;

[sopdt_est_y, sopdt_est_t] = step(sopdt_estimated, step_time); sopdt_est_y=reshape(sopdt_est_y, size(step_resp));
plot(sopdt_est_t, sopdt_est_y, 'm', 'linewidth', 2);

error_sopdt = immse(step_resp, sopdt_est_y);
fprintf('El error cuadrático medio (SOPDT) entre la estimada y los datos es: %f\n', error_sopdt);

fprintf('La mejora del modelo SOPDT contra FOPDT es de "%f%%"\n', (error_fopdt-error_sopdt)/error_fopdt);

% Modelo completo a partir de las ecuaciones en diferencias
% No entiendo por que tengo que agregarle InputDelay al modelo a partir de
% las ec. en diferencias
R1=10e3;
C1=10e-6;
complete_model = 1/((R1*C1*s+1)^6);
complete_model.InputDelay = 0.0753;

[ec_diff_y, ec_diff_t] = step(complete_model, step_time); ec_diff_y=reshape(ec_diff_y, size(step_resp));
plot(ec_diff_t, ec_diff_y, 'g', 'linewidth', 2);

error_ec_diff = immse(step_resp, ec_diff_y);
fprintf('El error cuadrático medio (SOPDT) entre la estimada y los datos es: %f\n', error_ec_diff);

legend('Respuesta al escalón (datos)', 'Escalón', sprintf('Respuesta estimada con modelo FOPDT (%f)', error_fopdt), sprintf('Respuesta estimada con modelo SOPDT (%f)', error_sopdt), sprintf('Modelo a partir de las ec. en diferencias (%f)\n', error_ec_diff));

%% Parte de la PRBS
data_prbs = open('prot_sim_data_prbs.dat');

%%
close all;
MAX_TIME=80;

time_prbs = data_prbs.data(:,1);
pwm_prbs = data_prbs.data(:,2)/5;  % divido por 5 para normalizar los datos con respecto al pico de 5v
y6_prbs = data_prbs.data(:,3)/5; % divido por 5 para normalizar los datos con respecto al pico de 5v

figure();
plot(time_prbs, y6_prbs, 'r', 'linewidth', 3);
hold on;
grid on;
title('Data PRBS');
plot(time_prbs, pwm_prbs, 'b', 'linewidth', 1);

lineal_time_prbs = 1:time_diff:MAX_TIME;
lineal_pwm_prbs = interp1(time_prbs(1:10:length(time_prbs)), pwm_prbs(1:10:length(time_prbs)), lineal_time_prbs);
lineal_y6_prbs = interp1(time_prbs(1:10:length(time_prbs)), y6_prbs(1:10:length(time_prbs)), lineal_time_prbs);

figure;
plot(lineal_time_prbs, lineal_y6_prbs, 'r', 'linewidth', 4);
hold on;
grid on;
title('Data PRBS con tiempo lineal');
plot(lineal_time_prbs, lineal_pwm_prbs, 'b', 'linewidth', 2);

%% Transformada de fourier de la PRBS
close all;
plot(lineal_pwm_prbs)
tf_prbs = fft(lineal_pwm_prbs);
tf_sys = fftn(lineal_y6_prbs);
w = 1:length(tf_prbs);

figure;
plot(abs(tf_prbs), 'b', 'linewidth', 2);
hold on;
grid on;
title('FFT PRBS');
plot(tf_sys, 'r', 'linewidth', 2);

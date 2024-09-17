% Loopshaping
% Control Automatico 3
% TP 1. Problema 7
% DATOS:
% g0 = 1/(s(s+1))
% Wdelta = 100*(s+0.1)/(s+100)
% S < 0.1, 0<w<0.1rad/seg -> Wd < 10, 0<w<0.1rad/seg

clear; close all; clc;

s = tf('s');

g0 = 1/(s*(s+1)); % Planta nominal
Wdelta = (0.1)*(s/0.1+1)/(s/100+1); % Funcion de incertidumbre para la estabilidad robusta
Wdmax = 10; % Valor maximo de performance nominal
w0 = 0.01; wf = 100;
w = logspace(log10(w0), log10(wf), 1000); % vector de frecuencias angulares
WdFunc = @(w_) (Wdmax).*(w_<=(0.1));
Wd = transpose(WdFunc(w));

[WdeltaMag, ~] = bode(Wdelta, w);
WdeltaMag = squeeze(WdeltaMag);
WdeltaMag_dB = 20 * log10(WdeltaMag);

% Donde cruza 0db Wdelta?
zero_dB_index = find(WdeltaMag_dB >= 0, 1, 'first');
w_zero_dB = w(zero_dB_index);

% Gráficos
fig = figure(); hold on; grid on; screenSize = get(0, 'ScreenSize');
set(fig, 'Position', [0 0 screenSize(3) screenSize(4)]);
set(gca, 'XScale', 'log');  % hago el eje logaritmico

% Performance nominal
semilogx(w, 20*log10(Wd), 'b--', 'linewidth', 3);

% Estabilidad robusta
estabilidad_robusta = (1-abs(Wd))./(1+abs(WdeltaMag));
semilogx(w(zero_dB_index:end), 20*log10(estabilidad_robusta(zero_dB_index:end)), 'r--', 'linewidth', 3);
semilogx(w(zero_dB_index:end), WdeltaMag_dB(zero_dB_index:end), 'r--', 'linewidth', 3);

% grafico la cota inferior de la region B: esto es lo que está fallando
% RegionB = (1 + Wdmax) / (1 - abs(WdeltaMag));
wRegionB = logspace(log10(w_zero_dB), log10(wf));
% semilogx(w, 1/WdeltaMag_dB, 'y--', 'linewidth', 3);

% Grafico mi controlador
L0 = 15/(s*(s/0.2+1)*(s/0.2+1)*(s/0.2+1)); % mi controlador propuesto
K0 = L0/g0;
[cMag, ~] = bode(K0, w); cMag = squeeze(cMag);
cMag_dB = 20*log10(cMag);
semilogx(w, cMag_dB, 'g', 'linewidth', 2);


% Grafico los polos del controlador
K0_poles = abs(pole(K0));
for i = 1:length(K0_poles)
    if (K0_poles(i) == 0)
        limits = xlim;
        plot(limits(1), 0, 'r*', 'linewidth', 5);
    else
        plot(K0_poles(i), 0, 'r*', 'linewidth', 5);
    end
end

% Lineas que delimitan las regiones prohibidas
plot([0.1 0.1], ylim, 'k--', 'LineWidth', 1); % la que limita el performance nominal
plot([w_zero_dB w_zero_dB], ylim, 'k--', 'LineWidth', 1); % la que limita la estabilidad robusta

xlabel('Frecuencia (rad/sec)');
ylabel('Magnitud (dB)');
title('Loopshaping');
% legend('W_{\delta} ', 'W_{d}', 'W_{\delta}', 'controlador', 'polo del controlador','polo del controlador',  'delimitadores', 'delimitadores');

% Grafico la condicion de performance robusta para sistemas SISO
% || |WdS| + |WdeltaT| || <= 1
% en terminos de L -> | Wd(jw) / ( 1 + L(jw) ) | + | Wdelta(jw)*L(jw) / ( 1 + L(jw) ) |
[L0Mag, ~] = bode(L0, w); L0Mag = squeeze(L0Mag);
rjw = (Wd + WdeltaMag.*L0Mag)/(1 + L0Mag);
figure(); grid on; hold on;
plot(w, rjw, 'r', 'linewidth', 3);

%% Grafico el controlador en el tiempo
figure(); grid on; hold on;
T0 = K0*g0/(1+g0*K0) % lazo cerrado para la planta nominal y el controlador
g0_delta = [-1:0.5:1]; % incerteza del modelo que da lugar a las familias de plantas
[y_g0, stepTime] = step(T0, 50);
grid on; hold on;
plot(stepTime, y_g0, 'linewidth', 3);
plot(stepTime, heaviside(stepTime), 'linewidth', 3);

figure();
pzmap(T0); grid on;

% grafico la respuesta temporal para la familia
% for i = 1:length(g0_delta)
%     delta = g0_delta(i);
%     G_uncertain = g0 * (1 + Wdelta * delta); % incerteza de la planta
%     T_uncertain = (L0 * G_uncertain) / (1 + L0 * G_uncertain); % funcion de lazo cerrado
%     step(T_uncertain, 10, '-');
% end

% % overlay
% step_input_time = linspace(0, 10, 1000);
% step_input = ones(size(step_input_time));
% plot(step_input_time, step_input, 'r--', 'LineWidth', 1);

% xlabel('Time (seconds)');
% ylabel('Response');
% title('Step Response of the Closed-Loop System with Uncertainty');
% legend('Nominal Plant (T0)', 'delta = -1', 'delta = -0.5', 'delta = 0', 'delta = 0.5', 'delta = 1', 'Step Input');
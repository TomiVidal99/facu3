% Script para diseño de controlador por loopshaping

% % % % % % % % % % % % % % % % % % % % 
% Teorema:
% % % % % % % % % % % % % % % % % % % % 
% Condicion necesaria y suficiente para performance robusta:
% || |WdS| + |WsT| || <= 1
% Ws -> W(delta)
% - - - - - - - - - - - - - - - - - - - - 

close all; clc;
s = tf('s');

% % % % % % % % % % % % % % % % % % % % 
% DATOS
% % % % % % % % % % % % % % % % % % % % 

ww = logspace(-2, 3, 1000); % vector de frecuencias
G0 = 1/(s*(s+1)); % Planta nominal
deltaIncertidumbrePlanta = [-1:0.5:1];

% Incertidumbre Wd (performance nominal)
wd_resp=10.*ones(size(ww));wd_resp=wd_resp.*(ww<0.1)+ 0.001*(ww>=0.1);

% Incertidumbre Wm (estabilidad robusta)
wm = 100*(s+0.1)/(s+100);
wm_resp=freqresp(wm,ww);wm_resp=reshape(wm_resp,size(ww));

% Controlador K = L0/G0
L0 = 10;
L0 = 10/(s);
L0 = 15/((s+1)*(s+1)*(s/0.1+1));
% L0 = K*G0;
L0_resp=freqresp(L0,ww);L0_resp=reshape(L0_resp,size(ww));

% - - - - - - - - - - - - - - - - - - - - 

T=L0_resp./(1+L0_resp); % Sensibilidad complementaria
S=1-T; % Sensibilidad

% % % % % % % % % % % % % % % % % % % % 
% Performance nominal y estabilidad robusta
% % % % % % % % % % % % % % % % % % % % 
% regionTop=20*log10(real(wd_resp)); regA0dbIndex=find(regionA<=0,1);regionA=regionA(1:regA0dbIndex);
regionA=20*log10((1+abs(wd_resp))./(1+abs(wm_resp)));
regionB2=20*log10(1./abs(wm_resp));
regionB=20*log10(1./(abs(wm_resp)+1));

fig = figure(); hold on; grid on; screenSize = get(0, 'ScreenSize');
set(fig, 'Position', [0 0 screenSize(3) screenSize(4)]);
set(gca, 'XScale', 'log');  % hago el eje logaritmico
semilogx(ww(1:length(wd_resp)), real(wd_resp), 'm--','linewidth',2);
semilogx(ww(1:length(regionA)), real(regionA), 'b--','linewidth',2);
semilogx(ww(1:length(regionB)), real(regionB), 'r--','linewidth',2);
semilogx(ww(1:length(regionB2)), real(regionB2), 'k--','linewidth',1);
semilogx(ww(1:length(wm_resp)), real(wm_resp), 'r--','linewidth',2);
semilogx(ww(1:length(abs(L0_resp))), real(20*log10(L0_resp)), 'g','linewidth',2);

% - - - - - - - - - - - - - - - - - - - - 

% % % % % % % % % % % % % % % % % % % % 
% Performance robusta
% % % % % % % % % % % % % % % % % % % % 
cond_perf_robust=20*log10(abs(S.*wd_resp)+abs(T.*wm_resp));

fig = figure(); hold on; grid on; screenSize = get(0, 'ScreenSize');
set(fig, 'Position', [0 0 screenSize(3) screenSize(4)]);
set(gca, 'XScale', 'log');  % hago el eje logaritmico
semilogx(ww, cond_perf_robust);

% Lleno las áreas con rojo donde la curva no cumple la condicion
% TODO
% - - - - - - - - - - - - - - - - - - - - 

% % % % % % % % % % % % % % % % % % % % 
% Respuesta al escalón
% % % % % % % % % % % % % % % % % % % % 

% Step response of the closed-loop system (T = L0/(1+L0))
T_closed_loop = L0 / (1 + L0);
figure; hold on;
step(T_closed_loop); grid on;
title('Respuesta al escalon lazo cerrado');

% - - - - - - - - - - - - - - - - - - - - 
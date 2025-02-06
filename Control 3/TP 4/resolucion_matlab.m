% CA3 TP4

%% Init
clear all;
close all;
s = tf('s');
% systemIdentification

%% Ejercicio 1
Ps = exp(-4.8*s)/((2+s)*(1+s)*(1+0.5*s)*(1+0.25*s));
[step_resp_y, step_resp_t] = step(Ps);
step_resp_x = ones(length(step_resp_y), 1);
step_resp_x(1) = 0;
time_step = step_resp_t(2) - step_resp_t(1);

% modelo FOPDT
Kp=0.5;
Tp=1.43;
Lp=5.7;
Gn = Kp/(s*Tp+1);
FOPDT_model = Gn;
FOPDT_model.InputDelay = Lp;

[FOPDT_step_y] = step(FOPDT_model, step_resp_t);

% close all;
fig = figure;
hold on; grid on;
plot(step_resp_t,step_resp_y, 'b', 'LineWidth', 2);
plot(step_resp_t,FOPDT_step_y, 'r', 'LineWidth', 2);
plot(step_resp_t,step_resp_x, '--k', 'LineWidth', 1);

FOPDT_error = immse(step_resp_y, FOPDT_step_y);
legend('Modelo alto orden', sprintf('Modelo FOPDT (%.6f)', FOPDT_error), 'Referencia');

%% Controlador PID equivalente de la estructura del SP
% La idea es que si uno pone un C=Kc(1+T1*s)/(T1*s),entonces al hacer padé
% del Ce = C/(1+C*(Gn-Pn)) = C  / (1+CGn*(1-e^(-Ls)))
% Se puede obtener un Ce que se aproxima a un PID, con este PID se puede
% ajustar la respuesta del sistema bastante bien.
% 
% Entonces todo concluye a que es equivalente reemplazar toda la estructura
% del SP por un PID?
clc

alpha=[0.35, 0.4, 0.48, 0.49, 0.5];

H=tf([1],[1]);
responses=cell(1,length(alpha)+1);
for i=1:length(alpha)
    
    if (alpha(i) < 0 || alpha(i) > 1)
        fprintf("ERROR: se espera que el alpha del PID esté contenido entre 0 y 1 (alpha=%.1f)\n", alpha(i));
    end

    T0=[(alpha(i)*alpha(i)+alpha(i))^(0.5)+alpha(i)]*(0.5*Lp);
    Kc=2*Tp/((Lp+4*T0)*Kp);
    
    PID=Kc*(1*Tp*s)*(1+0.5*Lp*s)/( (Tp*s)*(0.5*alpha(i)*Lp*s) );

    % sin retardo
    closed_loop_system = PID*Gn/(1+PID*Gn);
    % [cl_poles, cl_zeros]  = pzmap(closed_loop_system);
    % fprintf("alpha=%.2f\n",alpha(i));
    % disp("polos")
    % cl_poles
    % disp("ceros")
    % cl_zeros
    
    step_time_apply=1;
    perturbance_time_apply=10*Lp;

    closed_loop_system = PID*Ps/(1+PID*Ps);
    time=0:1e-3:150;
    reference=ones(1, length(time)); reference(1)=0;
    perturbance=zeros(1, length(time));perturbance(round(length(perturbance)*0.75):end)=0.2;
    reference=reference-perturbance;
    [y] = lsim(closed_loop_system, reference, time);

    responses{i}={y,sprintf('Sistema a lazo cerrado con PID (alpha=%.2f, T0=%.2f, Kc=%.2f)', alpha(i), T0, Kc)};
end

% La respuesta natural del sistema sin controlador
H=tf([0],[1]);
PID=tf([1],[1]);

% syst = sim("PID_tp4", 20*Lp);
% y = get(syst, "y").Data;
% time2 = syst.tout;
[y] = lsim(Ps, reference, time);
responses{6}={y,'Sistema a Lazo abierto'};

close all;
fig = figure;
hold on; grid on;
ylim([-1 2])
plot(time, responses{1}{1},'LineWidth', 2);
plot(time, responses{2}{1},'LineWidth', 2);
plot(time, responses{3}{1},'LineWidth', 2);
plot(time, responses{4}{1},'LineWidth', 2);
plot(time, responses{5}{1},'LineWidth', 2);
plot(time, responses{6}{1},'LineWidth', 2);
plot(time, reference, '--k', 'LineWidth', 1);

legend( responses{1}{2}, ...
        responses{2}{2}, ...
        responses{3}{2}, ...
        responses{4}{2}, ...
        responses{5}{2}, ...
        responses{6}{2}, ...
        'Referencia');


%% Ahora para plantas integrativas
% Plantas de la siguiente forma:
% P(s) = Kv*e^(-Ls)/s
Kv=1;
L=5;
Pn=Kv/s;
P=Pn;
P.InputDelay=L;

% Primero se tiene que estabilizar la planta realimentando con ganancia
% osea esto es teórico, despues se hace un controlador unico PID y listo
close all
K0=0.5/(Kv*L);
PK0=P/(1+P*K0); % esta sería la planta estabilizada
% pzmap(PK0)
% step(PK0)
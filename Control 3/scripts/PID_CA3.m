% Sintonizacion de PID para diferentes casos
%% Seteo inicial
clear all; close all;
s=tf('s');


%% Para sistemas con retardo dominante
L=10;
T=1.5;
if (L<T)
    fprintf("No se puede continuar, el retardo tiene que ser dominante: L=%f, T=%f\n", L, T);
    return;
end

% Planta a controlar
Kp=1;
P = Kp*exp(-9.7*s)/( (1+s)*(1+0.5*s)*(1+0.25*s)*(1+0.125*s) );
Gn = 1/(T*s+1);
Pn = exp(-L*s)*Gn;

% Controlador
T0=0.05; % Polos de LC deseado
Kx=(2*T)/((L+4*T0)*Kp);
alpha=(4*T0*T0)/((L+4*T0)*L);
C = Kx*(1+T*s)*(1+0.5*L*s)/(T*s*(1+0.5*alpha*L*s));
fprintf("Kx(%f) y alpha(%f) se diseñan para un polo doble en s=-1/T0(%f), T0=%f\n",  Kx, alpha, -1/T0, T0);

% Cosas para la simulación
perturbanceAmplitude = 0.25; % Cuanto es la perturbación
perturbanceStepTime = 10*L; % Cuando se dispara la perturbación

% Corro simulación
out = sim('PID_CA3_SIM');
SymSystem; % grafico la simulación

%% Ahora hago lo mismo pero sintonizando para diferentes alpha y Kx
alpha=[0.1, 0.3, 0.5];
Kx = [0.66, 0.086, 0.0829];

Pn=P;

outputs=cell(length(alpha), 1);
legends=cell(length(alpha), 1);
for i=1:length(alpha)
    T0 = (L/2)*(sqrt(alpha(i)*alpha(i)+alpha(i))+alpha(i));
    C = Kx(i)*(1+T*s)*(1+0.5*L*s)/(T*s*(1+0.5*alpha(i)*L*s));
    legends{i} = sprintf('alpha=%.3f, Kx=%.3f', alpha(i),  Kx(i));
    outputs{i} = sim('PID_CA3_SIM');
end

y1 = get(outputs{1}, 'y').Data;
y2 = get(outputs{2}, 'y').Data;
y3 = get(outputs{3}, 'y').Data;
time1 = get(outputs{1}, 'y').Time;
time2 = get(outputs{2}, 'y').Time;
time3 = get(outputs{3}, 'y').Time;

close all;
fig = figure();
hold on; grid on;
xlabel('Tiempo [Segundos]');
ylabel('Amplitud');
set(fig,'Position',[400 200 1200 600]);
title('PID para plantas con retardo dominante');

plot(time1, y1, 'r', 'LineWidth', 2);
plot(time2, y2, 'b', 'LineWidth', 2);
plot(time3, y3, 'g', 'LineWidth', 2);

l1=legends{1};
l2=legends{2};
l3=legends{3};
legend(l1, l2, l3, 'Location', 'northwest');

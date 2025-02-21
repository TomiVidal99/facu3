% Grafica la salida de la simulación de simulink
close all;

syst=out;
y=get(syst, "y").Data; % salida
u=get(syst, "u").Data; % accion de control
e=get(syst, "e").Data; % error
r=get(syst, "r").Data; % referencia
time=get(syst, "y").Time; % tiempo

fig = figure();
hold on; grid on;
xlabel('Tiempo [Segundos]');
ylabel('Amplitud');
set(fig,'Position',[400 200 1200 600]);
title('PID para plantas con retardo dominante');

plot(time, y, 'k', 'LineWidth', 3);
plot(time, u, 'b', 'LineWidth', 2);
plot(time, r, '--r', 'LineWidth', 1);
plot(time, e, '--m', 'LineWidth', 1);

legend('Salida', 'Acción de control', 'Referencia', 'Error', 'Location', 'northwest');
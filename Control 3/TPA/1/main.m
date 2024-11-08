% Trabajo de Aplicación 1
% Control Automático 3
% Grupo 10

clear all; close all;

%% Load file data
data = open('prot_sim_data.dat');


%% Code
%disp(dataFile.data);
%size(data.data)

time = data.data(:,1);
y6 = data.data(:,7);

figure();
plot(time, y6, 'r', 'linewidth', 4);
hold on;
grid on;

lineal_time = [0:1e-3:10];
lineal_y6 = zeros(length(lineal_time));
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
cl6ear all;
clc;
ww = logspace(-3,4,1000);

s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);

figure
for delta=-1:0.1:1
    bodemag(g0*(1+delta*wm),'r');hold on;
end
bodemag(g0,'k');
ylim([-10 50])
grid on 
grid minor
%%
close all;
clc;
s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);

figure
k=1;
L0=k*g0
T=L0/(1+L0);

ww = logspace(-2,2,1000);
wd_resp=freqresp(wm,ww);wd_resp=reshape(wd_resp,size(ww));
L0_resp=freqresp(L0,ww);L0_resp=reshape(L0_resp,size(ww));

semilogx(ww,20*log10(1./(1+abs(wd_resp))),'r'); hold on
semilogx(ww,20*log10(abs(L0_resp)),'k'); hold on

fill([ww(floor(end/2):end) ww(end) ww(floor(end/2))], [20*log10(1./(1+abs(wd_resp(floor(end/2):end)))) 0 0], [1 0.7 0.7])

%fill([ww ww(end) ww(1)],[20*log10(1./(1+abs(wd_resp))) 0 0],[1 0.7 0.7])
bodemag(s/s,'b--')

annotation(gcf,'textbox',...
    [0.45285714285714 0.73809523809525 0.47571428571429 0.140476190476194],...
    'string','$L={0(jw)}=K_{(jw)}g_{0(jw)}$',...
    'Interpreter','latex',...
    'FontSize',16,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.60285714285714 0.553809523809525 0.47571428571429 0.140476190476194],...
    'string','Estabilidad robusta',...
    'Interpreter','latex',...
    'FontSize',10,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.640285714285714 0.423809523809525 0.227571428571429 0.140476190476194],...
    'string','$\frac{1-|w_{d(jw)}|}{1+|w_{m(jw)}|}$',...
    'Interpreter','latex',...
    'FontSize',18,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.62 0.3023809523809525 0.22571428571429 0.140476190476194],...
    'string','$|w_{m(jw)}|>>1$',...
    'Interpreter','latex',...
    'FontSize',12,...
    'FitBoxToText','off',...
    'EdgeColor','none');

bodemag(wm,'r--');

grid on
grid minor
ylim([-20 10])
xlim([0.01 100])
%%
figure
bodemag(T*wm,ww,'k')
title('estabilidad robusta $|T_{(j\omega)} wm{(j\omega)}| < 0$ dB','Interpreter','latex')
ylim([-50 0])
grid on
grid minor
%%
close all;
clc
s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);
wd=10;

figure
k=0.5;
L0=k*g0
T=L0/(1+L0);
S=1/(1+L0);

ww = logspace(-2,2,1000);
wd_resp=freqresp(wm,ww);wd_resp=reshape(wd_resp,size(ww));
L0_resp=freqresp(L0,ww);L0_resp=reshape(L0_resp,size(ww));

semilogx(ww,20*log10(abs(L0_resp)),'k'); hold on

fill([ww(floor(end/2):end) ww(end) ww(floor(end/2))], [20*log10(1./(1+abs(wd_resp(floor(end/2):end)))) 0 0], [1 0.7 0.7])
%fill([ww ww(end) ww(1)],[20*log10(1./(1+abs(wd_resp))) 0 0],[1 0.7 0.7])
%fill([ww(floor(end/2):end) ww(end) ww(floor(end/2))],[20*log10(1./(1+abs(wd_resp(floor(end/2):end)))) 0 0],[1 0.7 0.7])
bodemag(s/s,'b--')

annotation(gcf,'textbox',...
    [0.15 0.3 0.227571428571429 0.140476190476194],...
    'string','$\frac{1+|w_{d(jw)}|}{1-|w_{m(jw)}|}$',...
    'Interpreter','latex',...
    'FontSize',18,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.15 0.1 0.22 0.14],...
    'string','$|w_{m(jw)}|>>1$',...
    'Interpreter','latex',...
    'FontSize',12,...
    'FitBoxToText','off',...
    'EdgeColor','none');
grid on
grid minor
ylim([-20 60])
xlim([0.01 100])
%%
figure
s_wd=abs(1./(1+(L0_resp)).*wd);
s_wd_dB=20*log10(1./(1+(L0_resp)).*wd.*(ww<0.1));
semilogx(ww,s_wd_dB,'k'); hold on
semilogx([0.1 0.101],[20*log10(s_wd(find(ww>0.1,1))) -50],'k');
title('perfomance nominal$|S_{(j\omega)} w+{(j\omega)}| < 0$ dB','Interpreter','latex')
ylabel('magnitud (dB)'); xlabel('frecuency {rad/s}')
ylim([-20 20])
grid on 
grid minor
xlim([0.01 100])
%%
close all;
clc
s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);
%controlador
figure
k=1.2;
k=1.8/(s/0.1+1);
k=1.8*(s/0.3+1)/(s/0.1+1)

L0=k*g0
T=feedback(L0,1);

ww = logspace(-2,2,1000);
wd_resp=10.*ones(size(ww)); wd_resp=wd_resp.*(ww<0.1)+ 0.001*(ww>=0.1);
wm_resp=freqresp(wm,ww);wm_resp=reshape(wm_resp,size(ww));
wd_cond_resp=wd_resp.*(abs(wm_resp)>1)+ 0.0001*(abs(wm_resp)<=1);
L0_resp=freqresp(L0,ww);L0_resp=reshape(L0_resp,size(ww));

semilogx(ww,20*log10(abs(L0_resp)),'k'); hold on

fill([ww ww(end) ww(1)],[20*log10(1./(1+abs(wd_resp))) 0 0],[1 0.7 0.7])
%fill([ww ww(end) ww(1)],[20*log10(1./(1+abs(wd_resp))) 0 0],[1 0.7 0.7])  %%???

bodemag(s/s,'b--')
grid on 
grid minor
ylim([-30 37])
xlim([0.01 100])

annotation(gcf,'textbox',...
    [0.45285714285714 0.73809523809525 0.47571428571429 0.140476190476194],...
    'string','$L={0(jw)}=K_{(jw)}g_{0(jw)}$',...
    'Interpreter','latex',...
    'FontSize',16,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.60285714285714 0.553809523809525 0.47571428571429 0.140476190476194],...
    'string','Estabilidad robusta',...
    'Interpreter','latex',...
    'FontSize',10,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.640285714285714 0.423809523809525 0.227571428571429 0.140476190476194],...
    'string','$\frac{1-|w_{d(jw)}|}{1+|w_{m(jw)}|}$',...
    'Interpreter','latex',...
    'FontSize',18,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.62 0.3023809523809525 0.22571428571429 0.140476190476194],...
    'string','$|w_{m(jw)}|>>1$',...
    'Interpreter','latex',...
    'FontSize',12,...
    'FitBoxToText','off',...
    'EdgeColor','none');

    annotation(gcf,'textbox',...
    [0.15 0.3 0.227571428571429 0.140476190476194],...
    'string','$\frac{1+|w_{d(jw)}|}{1-|w_{m(jw)}|}$',...
    'Interpreter','latex',...
    'FontSize',18,...
    'FitBoxToText','off',...
    'EdgeColor','none');
annotation(gcf,'textbox',...
    [0.15 0.1 0.22 0.14],...
    'string','$|w_{m(jw)}|>>1$',...
    'Interpreter','latex',...
    'FontSize',12,...
    'FitBoxToText','off',...
    'EdgeColor','none');

figure
T=L0_resp./(1+L0_resp);
semilogx(ww,20*log10(abs(T.*wm_resp)+abs((1-T).*wd_resp)),'k'); hold on
bodemag(s/s,ww,'b--')
grid on 
grid minor
ylim([-20 5])
%%
clc; clear; close all
s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);
k=1.8*(s/0.3+1)/(s/0.1+1)

figure
for delta=-1:0.5:1
L=k*g0*(1+delta*wm);
sys_y=feedback(L,1);
sys_e=feedback(1,L);
%CALCULO DE SOLUCION TEMPORAL
[y time]=step(sys_y,40);
[e time]=step(sys_e,40);

%respuesta a diferentes familias de plantas
plot(time,e,'k--','Linewidth',1); hold on
end
L0=k*g0
sys_y=feedback(L,1);
sys_e=feedback(1,L);
[y time]=step(sys_y,40);
[e time]=step(sys_e,40);
plot(time,e,'k--','Linewidth',2);
xlabel('tiempo[s]','Interpreter','latex');
ylabel('error','Interpreter','latex');
grid on 
grid minor
ylim([-2.5 2.5])
xlim([0 40])

%%
clc; clear; close all
s = tf('s');
g0= 1/(s*(s+1));
wm=100*(s+0.1)/(s+100);
k=1.8*(s/0.3+1)/(s/0.1+1);
figure
t=linspace(0,10000,5000);
r=sin(0.01*t);

for delta=-1:0.5:1
L=k*g0*(1+delta*wm);
sys_y=feedback(L,1);
sys_e=feedback(1,L);
%CALCULO DE SOLUCION TEMPORAL
resp_e= lsim(sys_e,r,t);
resp_y= lsim(sys_y,r,t);
%respuesta a diferentes familias de plantas
plot(t,resp_e,'k--','Linewidth',1); hold on;
end
L0=k*g0
sys_y=feedback(L,1);
sys_e=feedback(1,L);
resp_e= lsim(sys_e,r,t);
resp_y= lsim(sys_y,r,t);
plot(t,r,'r')
hold on;
plot(t,resp_e,'k','Linewidth',2);
xlabel('tiempo[s]','Interpreter','latex');
ylabel('error','Interpreter','latex');
grid on 
grid minor
ylim([-2 2.])
xlim([200 10000])
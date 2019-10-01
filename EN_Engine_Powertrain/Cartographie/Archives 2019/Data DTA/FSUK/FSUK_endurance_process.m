%%
clear all

load('C:\Users\Thomas\Desktop\Dynamix v2\Controle moteur\Donnees DTA\FSUK\FSUK-endurance.mat')
set(0,'defaultlinelinewidth',2);
set(0,'defaultaxesfontsize',12);
set(0,'DefaultAxesXGrid','on','DefaultAxesYGrid','on')
scrsz = get(groot,'ScreenSize');

%
TIME = 0:0.1:2920;
TIME = TIME';
plot(TIME,LUSP,TIME, WATER,TIME,5*(SESSION-1335));
grid on

% Découpage endu

endu{1} = [11340:21050];
endu{2} = [21050:29200];


%%
for i=1:2
    figure('OuterPosition',[1 scrsz(4)/2 scrsz(3)/1.5 scrsz(4)/2.4])
    plot(TIME(endu{i}),LUSP(endu{i}),'b');
    hold on
%     plot(TIME(endu{i}),LDSP(endu{i}),'r');
%     hold on
%     plot(TIME(endu{i}),max(min(SLIP(endu{i}),120),-20),'m');
%     hold on
    plot(TIME(endu{i}),TRAC(endu{i}),'k');
    title(strcat('endu run', num2str(i),' : Vitesses et glissement'),'Color','r','FontSize',14)
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 120],'ytick',0:10:120,'xtick',1100:60:3000,'xlim',0.1*[endu{i}(1) endu{i}(end)]);
    % leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé','Coupure traction control','Location','northwest');
    set(gcf,'Color','w');
    % set(leg,'FontSize',9);
end


%%
figure
for i=1:2
    subplot(2,2,i)
    [gAx,gLine1,gLine2] = plotyy([TIME(endu{i}),TIME(endu{i})],[LUSP(endu{i}),THROT(endu{i})],[TIME(endu{i}),TIME(endu{i})],[0.001*RPM(endu{i}),10*LAMB(endu{i})]);    title(strcat('endu run', num2str(i),' : Ouverture papillon et Régime moteur'))
    set(gAx(1),'ylim',[0 115],'ytick',0:10:110,'xtick',0:15:1560,'xlim',0.1*[endu{i}(1) endu{i}(end)]);
    ylabel(gAx(1), {'Vitesse roue avant droite (km/h)' 'Ouverture papillon (%)'});
    set(gAx(2),'ylim',[4 15.5],'ytick',0:1:15,'xtick',0:15:1560,'xlim',0.1*[endu{i}(1) endu{i}(end)]);
    ylabel(gAx(2),{'Régime moteur (x1000 tr/min)' 'Lambda x10'});
    leg = legend('Vitesse roues avant droite','Ouverture papillon','Régime moteur','Lambda','Location','northeast');
    set(gcf,'Color','w');
    set(leg,'FontSize',9);
end

%%
for i=1:2
    figure('OuterPosition',[1 scrsz(4)/3 scrsz(3)/1.3 scrsz(4)/2.08])
    [gAx,gLine1,gLine2] = plotyy([TIME(endu{i}),TIME(endu{i})],[100*LAMB(endu{i}),THROT(endu{i})],TIME(endu{i}),0.001*RPM(endu{i}));
    title(strcat('endu run', num2str(i),' : Ouverture papillon, Régime moteur et Lambda'),'Color','r','FontSize',14)
    set(gAx(1),'ylim',[30 150],'ytick',0:10:150,'xtick',500:10:1560,'xlim',0.1*[endu{i}(1) endu{i}(end)]);
    xlabel('Time (s)');
    ylabel(gAx(1), {'Lambda (x100)' 'Ouverture papillon'});
    set(gAx(2),'ylim',[3 15],'ytick',0:1:15,'xtick',500:10:1560,'xlim',0.1*[endu{i}(1) endu{i}(end)]);
    ylabel(gAx(2),'Régime moteur (x1000 tr/min)');
    % legend('Lambda x100','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
end

%%
figure
for i=1:2
    subplot(1,2,i)
    plot(TIME(endu{i}),0.01*RPM(endu{i}),'b');
    hold on
    plot(TIME(endu{i}),AIR(endu{i}),'r');
    hold on
    plot(TIME(endu{i}),WATER(endu{i}),'g');
    hold on
end

%%
Air_endu = [];
Water_endu = [];
Air_endu_mean = [];
Water_endu_mean = [];

for i=1:2
    Air_endu = [Air_endu, AIR(endu{i})'];
    Water_endu = [Water_endu, WATER(endu{i})'];
    Air_endu_mean = [Air_endu_mean,mean(AIR(endu{i})')];
    Water_endu_mean = [Water_endu_mean, mean(WATER(endu{i})')];
end
Air_endu_mean_tot = mean(Air_endu);
Water_endu_mean_tot = mean(Water_endu);

%%
figure
for i=1:2
    subplot(1,2,i)
    scatter(RPM(endu{i}),THROT(endu{i}),'r','.');
    title(strcat('endu run', num2str(i),' : Point Régime/charge'))
    xlabel('Régime moteur (tr/min)');
    ylabel('Ouverture papillon (%)');
    set(gca,'ylim',[0 110],'ytick',0:10:100);
    set(gca,'FontSize',10);
    set(gcf,'Color','w');
end

%%
figure
scatter(RPM(endu{1}),THROT(endu{1}),'o','filled');
hold on
scatter(RPM(endu{2}),THROT(endu{2}),'o','filled');
title(strcat('endu run', num2str(i),' : Point de fonctionnement moteur'))
xlabel('Régime moteur (tr/min)');
ylabel('Ouverture papillon (%)');
set(gca,'ylim',[0 110],'ytick',0:10:100);
set(gca,'FontSize',10);
set(gcf,'Color','w');

%%
figure
for i=1:2
    subplot(2,2,i)
    plot(TIME(endu{i}),THROT(endu{i}),TIME(endu{i}),MAP(endu{i}));
end

%%
for i=2
    figure
    plot(TIME(endu{i}),THROT(endu{i}));
    figure
    plot(TIME(endu{i}),MAP(endu{i}));
end
%%
for i=2
    figure
    plot(TIME(endu{i}),THROT(endu{i}),TIME(endu{i}),1.6*MAP(endu{i})-60);
end

%%
scatter3(RPM,THROT,MAP,'filled');

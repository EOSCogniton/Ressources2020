%%
clear all

load('C:\Users\Thomas\Desktop\Dynamix v2\Controle moteur\Donnees DTA\FSUK\FSUK-sprint.mat')
set(0,'defaultlinelinewidth',2);
set(0,'defaultaxesfontsize',12);
set(0,'DefaultAxesXGrid','on','DefaultAxesYGrid','on')
scrsz = get(groot,'ScreenSize');

TIME = [0:0.1:1560.9]';

%
plot(TIME,LUSP,TIME, RPM/100,TIME,5*(SESSION-1335));
grid on

% Découpage sprint

sprint{1} = [5100:6550];
sprint{2} = [7850:9400];
sprint{3} = [11630:13100];
sprint{4} = [14360:15600];

% Injector duty cycle
for i=1:length(INJ)
    INJ1(i) = 100*INJ(i)/(2*60000/RPM(i));
end

%%
for i=1:4
    figure('OuterPosition',[1 scrsz(4)/2 scrsz(3)/1.5 scrsz(4)/2.4])
    plot(TIME(sprint{i}),LUSP(sprint{i}),'b');
    hold on
    plot(TIME(sprint{i}),LDSP(sprint{i}),'r');
    hold on
    plot(TIME(sprint{i}),max(min(SLIP(sprint{i}),120),-20),'m');
    hold on
    plot(TIME(sprint{i}),TRAC(sprint{i}),'k');
    title(strcat('sprint run', num2str(i),' : Vitesses et glissement'),'Color','r','FontSize',14)
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 120],'ytick',0:10:120,'xtick',500:10:1560,'xlim',0.1*[sprint{i}(1) sprint{i}(end)]);
    % leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé','Coupure traction control','Location','northwest');
    set(gcf,'Color','w');
    % set(leg,'FontSize',9);
end


%%
figure
for i=1:4
    subplot(2,2,i)
    [gAx,gLine1,gLine2] = plotyy([TIME(sprint{i}),TIME(sprint{i})],[LUSP(sprint{i}),THROT(sprint{i})],[TIME(sprint{i}),TIME(sprint{i})],[0.001*RPM(sprint{i}),10*LAMB(sprint{i})]);    title(strcat('Sprint run', num2str(i),' : Ouverture papillon et Régime moteur'))
    set(gAx(1),'ylim',[0 115],'ytick',0:10:110,'xtick',0:15:1560,'xlim',0.1*[sprint{i}(1) sprint{i}(end)]);
    ylabel(gAx(1), {'Vitesse roue avant droite (km/h)' 'Ouverture papillon (%)'});
    set(gAx(2),'ylim',[4 15.5],'ytick',0:1:15,'xtick',0:15:1560,'xlim',0.1*[sprint{i}(1) sprint{i}(end)]);
    ylabel(gAx(2),{'Régime moteur (x1000 tr/min)' 'Lambda x10'});
    leg = legend('Vitesse roues avant droite','Ouverture papillon','Régime moteur','Lambda','Location','northeast');
    set(gcf,'Color','w');
    set(leg,'FontSize',9);
end

%%
for i=1:4
    figure('OuterPosition',[1 scrsz(4)/3 scrsz(3)/1.3 scrsz(4)/2.08])
    [gAx,gLine1,gLine2] = plotyy([TIME(sprint{i}),TIME(sprint{i})],[100*LAMB(sprint{i}),THROT(sprint{i})],TIME(sprint{i}),0.001*RPM(sprint{i}));
    title(strcat('Sprint run', num2str(i),' : Ouverture papillon, Régime moteur et Lambda'),'Color','r','FontSize',14)
    set(gAx(1),'ylim',[30 150],'ytick',0:10:150,'xtick',500:10:1560,'xlim',0.1*[sprint{i}(1) sprint{i}(end)]);
    xlabel('Time (s)');
    ylabel(gAx(1), {'Lambda (x100)' 'Ouverture papillon'});
    set(gAx(2),'ylim',[3 15],'ytick',0:1:15,'xtick',500:10:1560,'xlim',0.1*[sprint{i}(1) sprint{i}(end)]);
    ylabel(gAx(2),'Régime moteur (x1000 tr/min)');
    % legend('Lambda x100','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
end

%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(sprint{i}),0.01*RPM(sprint{i}),'b');
    hold on
    plot(TIME(sprint{i}),AIR(sprint{i}),'r');
    hold on
    plot(TIME(sprint{i}),WATER(sprint{i}),'g');
    hold on
end

%%
Air_sprint = [];
Water_sprint = [];
Air_sprint_mean = [];
Water_sprint_mean = [];

for i=1:4
    Air_sprint = [Air_sprint, AIR(sprint{i})'];
    Water_sprint = [Water_sprint, WATER(sprint{i})'];
    Air_sprint_mean = [Air_sprint_mean,mean(AIR(sprint{i})')];
    Water_sprint_mean = [Water_sprint_mean, mean(WATER(sprint{i})')];
end
Air_sprint_mean_tot = mean(Air_sprint);
Water_sprint_mean_tot = mean(Water_sprint);

%%
figure
for i=1:4
    subplot(2,2,i)
    scatter(RPM(sprint{i}),THROT(sprint{i}),'r','.');
    title(strcat('Sprint run', num2str(i),' : Point Régime/charge'))
    xlabel('Régime moteur (tr/min)');
    ylabel('Ouverture papillon (%)');
    set(gca,'ylim',[0 110],'ytick',0:10:100);
    set(gca,'FontSize',10);
    set(gcf,'Color','w');
end

%%
figure
scatter(RPM(sprint{1}),THROT(sprint{1}),'o','filled');
hold on
scatter(RPM(sprint{2}),THROT(sprint{2}),'o','filled');
title(strcat('Sprint run', num2str(i),' : Point de fonctionnement moteur'))
xlabel('Régime moteur (tr/min)');
ylabel('Ouverture papillon (%)');
set(gca,'ylim',[0 110],'ytick',0:10:100);
set(gca,'FontSize',10);
set(gcf,'Color','w');

%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(sprint{i}),THROT(sprint{i}),TIME(sprint{i}),MAP(sprint{i}));
end

%%
for i=2
    figure
    plot(TIME(sprint{i}),THROT(sprint{i}));
    figure
    plot(TIME(sprint{i}),MAP(sprint{i}));
end
%%
for i=2
    figure
    plot(TIME(sprint{i}),THROT(sprint{i}),TIME(sprint{i}),1.6*MAP(sprint{i})-60);
end

%%
scatter3(RPM,THROT,MAP,'filled');

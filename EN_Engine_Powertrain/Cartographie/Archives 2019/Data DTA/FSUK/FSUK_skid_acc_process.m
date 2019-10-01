% 
clear all

load('C:\Users\Thomas\Desktop\Dynamix v2\Controle moteur\Donnees DTA\FSUK\FSUK-skidacc.mat')
set(0,'defaultlinelinewidth',2);
set(0,'defaultaxesfontsize',11);
set(0,'DefaultAxesXGrid','on','DefaultAxesYGrid','on')
scrsz = get(groot,'ScreenSize');

TIME = [0:0.1:1033.3]';

%
plot(TIME,LUSP,TIME, RPM/100,TIME,5*(SESSION-1335));
grid on

% Découpage skid-pad

skid{1} = [250:555];
skid{2} = [863:1147];
skid{3} = [1642:1914];
skid{4} = [2197:2448];

for i=1:4
    figure
    plot(TIME(skid{i}),LUSP(skid{i}),TIME(skid{i}),smooth(LUSP(skid{i}),10),'r');
end

% Découpage accel

acc{1} = [6378:6452];
acc{2} = [6880:6966];
acc{3} = [9408:9501];
acc{4} = [10130:10220];

for i=1:4
    figure
    plot(TIME(acc{i}),LUSP(acc{i}),TIME(acc{i}),smooth(LUSP(acc{i}),5),'r');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Data Skid
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(skid{i}),LUSP(skid{i}),'b');
    hold on
    plot(TIME(skid{i}),LDSP(skid{i}),'r');
    hold on
    plot(TIME(skid{i}),max(min(SLIP(skid{i}),60),-20),'g');
    hold on
    plot(TIME(skid{i}),TRAC(skid{i}),'k');
    title(strcat('Skid-pad run', num2str(i),' : vitesses et traction control'))
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 60],'ytick',0:5:60);
    leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé', 'Coupure traction control');
    set(gca,'FontSize',10);
    set(leg,'FontSize',9);
end

%%
for i=1:1
    figure('OuterPosition',[1 scrsz(4)/2 scrsz(3)/1.5 scrsz(4)/2.4])
    plot(TIME(skid{i}),LUSP(skid{i}),'b');
    hold on
    plot(TIME(skid{i}),LDSP(skid{i}),'r');
    hold on
    plot(TIME(skid{i}),max(min(SLIP(skid{i}),50),-20),'m');
    hold on
    plot(TIME(skid{i}),TRAC(skid{i}),'k');
    title(strcat('Skid-pad run', num2str(i),' : vitesses et traction control'),'Color','r','FontSize',14)
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 50],'ytick',0:5:60,'xtick',0:2:400,'xlim',0.1*[skid{i}(1) skid{i}(end)]);
    leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé', 'Coupure traction control','Location','northwest');
    set(gcf,'Color','w');
    % set(leg,'FontSize',9);
end



%%
figure
for i=1:4
    subplot(2,2,i)
    [gAx,gLine1,gLine2] = plotyy([TIME(skid{i}),TIME(skid{i})],[smooth(LDSP(skid{i}),5),THROT(skid{i})],TIME(skid{i}),RPM(skid{i}));
    title(strcat('Skid-pad run', num2str(i),' : Ouverture papillon et Régime moteur'))
    set(gAx(1),'ylim',[0 100],'ytick',0:10:100,'xtick',0:3:400);
    ylabel(gAx(1), {'Vitesse roue arrière (km/h)' 'Ouverture papillon (%)'});
    set(gAx(2),'ylim',[1000 11000],'ytick',0:1000:12000,'xtick',0:3:400);
    ylabel(gAx(2),'Régime moteur (tr/min)');
    leg = legend('Vitesse roues arrière','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
    set(leg,'FontSize',9);
end

%%
for i=1:4
    figure('OuterPosition',[1 scrsz(4)/3 scrsz(3)/1.3 scrsz(4)/2.08])
    [gAx,gLine1,gLine2] = plotyy([TIME(skid{i}),TIME(skid{i})],[smooth(LDSP(skid{i}),5),THROT(skid{i})],TIME(skid{i}),0.001*RPM(skid{i}));
    title(strcat('Skid-pad run', num2str(i),' : Ouverture papillon et Régime moteur'),'Color','r','FontSize',14)
    set(gAx(1),'ylim',[0 100],'ytick',0:10:100,'xtick',0:2:400,'xlim',0.1*[skid{i}(1) skid{i}(end)]);
    xlabel('Time (s)');
    ylabel(gAx(1), {'Vitesse roues arrière (km/h)' 'Ouverture papillon (%)'});
    set(gAx(2),'ylim',[1 11],'ytick',0:1:12,'xtick',0:2:400,'xlim',0.1*[skid{i}(1) skid{i}(end)]);
    ylabel(gAx(2),'Régime moteur (x1000 tr/min)');
    % legend('Vitesse roues arrière','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
end



%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(skid{i}),0.01*RPM(skid{i}),'b');
    hold on
    plot(TIME(skid{i}),AIR(skid{i}),'r');
    hold on
    plot(TIME(skid{i}),WATER(skid{i}),'g');
    hold on
end
%%
for i=1:4
    subplot(2,2,i)
    plot(TIME(skid{i}),0.01*RPM(skid{i}),'b');
    hold on
    plot(TIME(skid{i}),THROT(skid{i}),'r');
    hold on
    plot(TIME(skid{i}),100*LAMB(skid{i}),'g');
    hold on
end

%%
for i=1:1
    figure('OuterPosition',[1 scrsz(4)/3 scrsz(3)/1.3 scrsz(4)/2.08])
    [gAx,gLine1,gLine2] = plotyy([TIME(skid{i}),TIME(skid{i})],[100*LAMB(skid{i}),THROT(skid{i})],TIME(skid{i}),0.001*RPM(skid{i}));
    title(strcat('Skid-pad run', num2str(i),' : Ouverture papillon, Régime moteur et Lambda'),'Color','r','FontSize',14)
    set(gAx(1),'ylim',[0 110],'ytick',0:10:150,'xtick',0:2:400,'xlim',0.1*[skid{i}(1) skid{i}(end)]);
    xlabel('Time (s)');
    ylabel(gAx(1), {'Lambda (x100)' 'Ouverture papillon'});
    set(gAx(2),'ylim',[2 13],'ytick',0:1:15,'xtick',0:2:400,'xlim',0.1*[skid{i}(1) skid{i}(end)]);
    ylabel(gAx(2),'Régime moteur (x1000 tr/min)');
    legend('Lambda x100','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
end


end
%%
for i=1:4
    subplot(2,2,i)
    plot(TIME(skid{i}),THROT(skid{i}),'r');
    hold on
    plot(TIME(skid{i}),MAP(skid{i}),'g');
    hold on
end


%%
Air_skid = [];
Water_skid = [];

for i=1:4
    Air_skid = [Air_skid, AIR(skid{i})'];
    Water_skid = [Water_skid, WATER(skid{i})'];
end
Air_skid_mean = mean(Air_skid);
Water_skid_mean = mean(Water_skid);





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Data Accel
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(acc{i}),LUSP(acc{i}),'b');
    hold on
    plot(TIME(acc{i}),LDSP(acc{i}),'r');
    hold on
    plot(TIME(acc{i}),max(min(SLIP(acc{i}),110),-20),'g');
    title(strcat('Accélération run', num2str(i),' : Vitesses et glissement'))
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 110],'ytick',0:10:150);
    leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé','Location','southeast');
    set(gca,'FontSize',10);
    set(leg,'FontSize',9);
end

%%
for i=1:4
    figure('OuterPosition',[1 scrsz(4)/2 scrsz(3)/1.5 scrsz(4)/2.4])
    plot(TIME(acc{i}),LUSP(acc{i}),'b');
    hold on
    plot(TIME(acc{i}),LDSP(acc{i}),'r');
    hold on
    plot(TIME(acc{i}),max(min(SLIP(acc{i}),120),-20),'m');
    hold on
    plot(TIME(acc{i}),TRAC(acc{i}),'k');
    title(strcat('Accelération run', num2str(i),' : Vitesses et glissement'),'Color','r','FontSize',14)
    xlabel('Time (s)');
    ylabel('Vitesse (km/h) ou %');
    set(gca,'ylim',[0 120],'ytick',0:10:120,'xtick',600:1:1200,'xlim',0.1*[acc{i}(1) acc{i}(end)]);
    % leg = legend('Vitesse roue avant droite','Vitesse roues arrière','Glissement calculé','Coupure traction control','Location','northwest');
    set(gcf,'Color','w');
    % set(leg,'FontSize',9);
end

%%
figure
for i=1:4
    subplot(2,2,i)
    [gAx,gLine1,gLine2] = plotyy([TIME(acc{i}),TIME(acc{i})],[LUSP(acc{i}),THROT(acc{i})],[TIME(acc{i}),TIME(acc{i})],[0.001*RPM(acc{i}),10*LAMB(acc{i})]);
    title(strcat('Acceleration run', num2str(i),' : Ouverture papillon et Régime moteur'))
    set(gAx(1),'ylim',[0 115],'ytick',0:10:110,'xtick',0:2:1100,'xlim',0.1*[acc{i}(1) acc{i}(end)]);
    ylabel(gAx(1), {'Vitesse roue avant droite (km/h)' 'Ouverture papillon (%)'});
    set(gAx(2),'ylim',[4 15.5],'ytick',0:1:15,'xtick',600:2:1100,'xlim',0.1*[acc{i}(1) acc{i}(end)]);
    ylabel(gAx(2),{'Régime moteur (x1000 tr/min)' 'Lambda x10'});
    % leg = legend('Vitesse roues avant droite','Ouverture papillon','Régime moteur','Lambda','Location','southeast');
    set(gcf,'Color','w');
    % set(leg,'FontSize',9);
end

%%
for i=1:1
    figure('OuterPosition',[1 scrsz(4)/3 scrsz(3)/1.3 scrsz(4)/2.08])
    [gAx,gLine1,gLine2] = plotyy([TIME(acc{i}),TIME(acc{i})],[100*LAMB(acc{i}),THROT(acc{i})],TIME(acc{i}),0.001*RPM(acc{i}));
    title(strcat('Accelération run', num2str(i),' : Ouverture papillon, Régime moteur et Lambda'),'Color','r','FontSize',14)
    set(gAx(1),'ylim',[30 150],'ytick',0:10:150,'xtick',600:1:1200,'xlim',0.1*[acc{i}(1) acc{i}(end)]);
    xlabel('Time (s)');
    ylabel(gAx(1), {'Lambda (x100)' 'Ouverture papillon'});
    set(gAx(2),'ylim',[3 15],'ytick',0:1:15,'xtick',600:1:1200,'xlim',0.1*[acc{i}(1) acc{i}(end)]);
    ylabel(gAx(2),'Régime moteur (x1000 tr/min)');
    legend('Lambda x100','Ouverture papillon','Régime moteur');
    set(gcf,'Color','w');
end
end
%%
figure
for i=1:4
    subplot(2,2,i)
    plot(TIME(acc{i}),0.01*RPM(acc{i}),'b');
    hold on
    plot(TIME(acc{i}),AIR(acc{i}),'r');
    hold on
    plot(TIME(acc{i}),WATER(acc{i}),'g');
    hold on
end
%%
for i=1:4
    subplot(2,2,i)
    plot(TIME(acc{i}),0.01*RPM(acc{i}),'b');
    hold on
    plot(TIME(acc{i}),THROT(acc{i}),'r');
    hold on
    plot(TIME(acc{i}),100*LAMB(acc{i}),'g');
    hold on
end
%%
for i=1:4
    subplot(2,2,i)
    plot(TIME(acc{i}),THROT(acc{i}),'r');
    hold on
    plot(TIME(acc{i}),MAP(acc{i}),'g');
    hold on
end

%%
Air_acc = [];
Water_acc = [];

for i=1:4
    Air_acc = [Air_acc, AIR(acc{i})'];
    Water_acc = [Water_acc, WATER(acc{i})'];
end
Air_acc_mean = mean(Air_acc);
Water_acc_mean = mean(Water_acc);









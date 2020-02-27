function plotGGV(GGV)

Gxmax = GGV(:,1);
Gxmin = GGV(:,2);
Gy = GGV(:,3);
V = GGV(:,4);
P = [];
g=9.81;
for i=1:length(V)
    th=0:0.1:pi;
    X = Gy(i)*cos(th)/g;
    Y1 = Gxmax(i)*sin(th)/g;
    Y2 = Gxmin(i)*sin(th)/g;
    P = [P;X' Y1' X'*0+V(i)*3.6;-X' Y2' X'*0+V(i)*3.6];
end

z = zeros(size(P(:,1)'));
col = P(:,3)';  % This is the color, vary with x in this case.
surface([P(:,1)';P(:,1)'],[P(:,2)';P(:,2)'],[z;z],[col;col],'facecol','no','edgecol','interp','linew',2);
colorbar
title('GGV diagramme')
xlabel('Lateral accereration(g)')
ylabel('Longitudinale accereration(g)')
zlabel('Speed (kmph)')
end
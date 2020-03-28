function [V,Gx,Gy,t,D,GGV] = LapTime(track_file,param_file)
%----TRACK processing----
load(track_file,'track')
% Get curvature and smooth
curvature=LineCurvature2D(track); 
windowWidth = 25; %smooth parameter
polynomialOrder = 2; %smooth parameter
smoothcurvature = sgolayfilt(curvature, polynomialOrder, windowWidth);
%section of the track
idx_Section = extrema(smoothcurvature);
%Turn radius of th track
R = 1./smoothcurvature;
R(isnan(R)) = 150; %on enlève les NaN
R = min(150, max(-150, R)); %on sature
Rabs = abs(R);%Le rayon calculé l'a été au niveau du COG or ils noufaut le rayon intérieur
%Compute distance between track point
dtrack = diff(track);
D = sqrt(dtrack(:,1).^2+dtrack(:,2).^2); % vecteur des distances entre chaque point du circuit
D = [0;D];

%---GGV Diagramme---
V_vector = (1:10:140)/3.6; %compute GGV diagramme for velocity (m/s) between 0 and 140 km/h
GGV = makeGGV(param_file,V_vector);

%---Init---
V = 0;
t = 0;
Gy = 0;
Gx = findGxmax(Gy,V,GGV);

%---Loop---
for section=1:length(idx_Section)-1
    %---Initial data of the section---
    V_start = V(end); %Initial speed of the section
    Gx_start = Gx(end);
    Gy_start = Gy(end);
    
    %---Maximale finale speed and Gy of the section---
    r_end = Rabs(idx_Section(section+1));
    if r_end < 150
        [Gy_end,V_end] = findGymax_GGV(r_end,GGV);%finale speed of the section in turn
    else %if the radius is saturated we take the maximale speed of the GGV diagramme
        V_end = max(GGV(:,4));
        Gy_end = 0;
    end
    
    %---Simulation---
    %Forward
    [V_f,Gx_f,Gy_f,t_f] = Forward(V_start,Gx_start,Gy_start,Rabs(idx_Section(section):idx_Section(section+1)),D(idx_Section(section):idx_Section(section+1)),GGV); % calcul de la vitesse si on accélère à fond depuis le point initial
    %Backward
    [V_b,Gx_b,Gy_b,t_b] = Backward(V_end,Gy_end,Rabs(idx_Section(section):idx_Section(section+1)),D(idx_Section(section):idx_Section(section+1)),GGV); % calcul de la vitesse si on freine à fond depuis le point final
    
    %---mix---
    %We keep only the data from the lower velocity at each point of the section
    id_f = (V_f<V_b);
    V = [V; V_f(id_f); V_b(~id_f)];
    Gy = [Gy; Gy_f(id_f); Gy_b(~id_f)];
    Gx = [Gx; Gx_f(id_f); Gx_b(~id_f)];
    %Time management
    t_f = t_f(id_f);
    if sum(id_f)>0
        t_b = t_b(~id_f)-t_b(sum(id_f))+t_f(end);
    else
        t_b = t_b(~id_f);
    end
    t = [t; t_f+t(end); t_b+t(end)];
    
end

%---Post processing ---
for i=2:length(D)
    D(i)=D(i)+D(i-1); %D devient la distance cumulé pour les plots
end
Gy = Gy.*R./abs(R); % on signe Gy selon le signe de R;
end


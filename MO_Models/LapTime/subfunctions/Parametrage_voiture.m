clear all

%% Parameters 
% ___physical___
g = 9.81; %gravity constant
rho = 1.18; %air density

%___Vehicle geometry___
W = 1.575; % wheelbase (m)
D_wheel = 0.45; % Wheel diameter (m)
Tf= 1.236 ; % rear track width of the car (m)
Tr= 1.165 ; % front track width of the car (m)

%___Masses and inertias___
m_aero = 0; %Mass of the aerodynamic features (kg)
h_aero= 0.4 ; %Heigh of the center of gravity of the aerodynaic features (m)
m_p = 70; % Mass of the pilot (kg)
h_p = 0.42; % %Heigh of the center of gravity of the pilote (m)
m_v = 205; % Mass of the vehicle (kg)
h_v = 0.29; % %Heigh of the center of gravity of the du vehicle (m)
m_t = m_v + m_p + m_aero; %Mass Total (kg)
h= (m_v*h_v + h_p*m_p + m_aero*h_aero)/m_t ; %Global CoG 

rep = 0.5; % Mass distribution on the rear axle (%)
xf = W*(1-rep);   % distance entre le train avant et le C.G.
xr = 1- xf;

Jjp = 0.250; %Inertie de la roue et du pneu (CATIA)(à touver pour du 10 pouce)
Jm = 0.005; %Inertie du moyeu et du freinage (CATIA)
Ja = 0.00005; %inertie d'un arbre de transmission  (CATIA)
Jd = 0.03; %Inertie du différentiel (CATIA)
Jc = 0.005; % Inertie de la couronne (CATIA)
Jmot = 0.1; % Estimation de l'inertie moteur+ chaine
J_rot = 2*(Jjp+Jm+Ja)+Jd+Jc+Jmot; % Inertie equivalente des masses en rotation (kg.m²)

%___Tyres ___

%Longi
Long_tire_grip_brake = 1.4;
Long_tire_grip = 1.4;
coeff_roul = 0.01; % Coefficient de resistance au roulement du pneu
%Lateral
%Donnees extraites des modeles de GTE
%Le coefficient q est un coeff donné par les testeurs de pneus: ils estiment
% qu'une vraie piste adhère q fois moins que leur banc d'essai (il valait 2/3 au début)
q=0.7;%0.483 ; %pourquoi avoir mit cette valeur sortie du chapeau ? d'autant que 2/3 permet d'obtenir un temps correct au skidpad


FZ = [0,667.233,444.822,1112.055,222.411,1556.877] ; %Force vertical (N)

% Pneus 13" pour un slip angle de -1.6°
%FY= [0,923.995,714.693,1111.856,420.092,1114.576]*2/3 ;

% Pneus 13" pour un slip angle optimal
FY= [0,1783.995,1233.106,2692.902,676.343,3363.065]*q ;


%Y_poly = polyfit(FZ,FY_13,3) ;
%clear q %FZ FY FY_13

%___Engine__

% Mesure Optimus à Chambéry le 01/05/19
rmot = 1.0e+04 *[ 0     0.5035    0.5127    0.5214   0.5289    0.5332    0.5419    0.5490    0.5581    0.5630    0.5679    0.5721    0.5798    0.5884    0.5961    0.6010    0.6053    0.6129    0.6204    0.6263    0.6315    0.6393    0.6463    0.6531    0.6618    0.6686    0.6760    0.6846    0.6931    0.7037    0.7107    0.7193    0.7280    0.7367    0.7452    0.7535    0.7627    0.7714    0.7800    0.7890    0.7976    0.8061   0.8147    0.8234    0.8321    0.8407    0.8494    0.8581    0.8668    0.8754    0.8841    0.8928    0.9014    0.9101    0.9188    0.9275    0.9362    0.9448    0.9535    0.9622    0.9708    0.9795    0.9882    0.9971    1.0055    1.0142    1.0229    1.0316    1.0402    1.0489    1.0576    1.0661    1.0749    1.0836    1.0923    1.1009    1.1128    1.1214    1.1301    1.1388    1.1475    1.1561    1.1648    1.1735    1.1822    1.1908    1.1996    1.2082    1.2168    1.2252    1.2342    1.2429    1.2515    1.2602    1.2689    1.2776    1.2862    1.2908    1.2981    1.3052    1.3130    1.3217    1.3290    1.3320    1.3331    1.3342    1.3357    1.3365    1.3371];
cmot = [ 0   37.9900   38.3560   38.3050   37.4170   36.4590   34.5720   33.6110   34.7320   35.8130   37.6300   38.8490   40.3260   40.2320   38.9600   37.5130   36.5340   36.0290   36.9180   38.2830   39.8300   41.5740   42.8700   43.3370   43.4340   43.0560   42.4760   42.3820   42.7300   43.4430   44.3720   45.0850   45.9490   46.9480   48.1500   49.3090   50.5060   51.7650   52.9480   54.0880   54.8770   55.4050   55.8510   55.9940   55.9970   56.0160   55.8710   55.7240   55.5230   55.5740   55.5740   55.4100   55.3710   55.1590   54.8720   54.3970   53.9530   53.4010   53.0100   52.6990   52.2970   51.9030   51.4540   50.9450   50.6640   50.3260   50.1570  49.9690   49.7020   49.4710   49.1030   48.7480   48.4320   48.0840   47.8420   47.6320   47.3330   47.1060   46.7610   46.4220  45.9800   45.4400   44.9980   44.5220   43.9320   43.5800   43.1550   42.6800   42.1590   41.5490   40.8960   40.3820   39.7020   39.0400   38.0610   37.0200   36.0120   35.7370   34.9790   33.7500   32.5560   31.6840   30.1040   28.1310   26.9020   25.0590   23.2250   21.5160   20.2080];

r_pat = 9000; % Regime de patinage de l'embrayage (tr/min)
r_rupteur = 13500; % Regime de rupteur (tr/min)
t_pas = 0.1; % Temps de passage de rapport (s)

%___Transmission___
k_p = 36/76; % Rapport primaire

% Etagement origine
K(1) = 12/32; % Rapport de 1ere
K(2) = 16/31; % Rapport de 2eme
K(3) = 18/29; % Rapport de 3eme
K(4) = 22/31; % Rapport de 4eme
K(5) = 23/29; % Rapport de 5eme
K(6) = 24/28; % Rapport de 6eme

k_f = 1/3.2; % Rapport final
pertes = 0.9; % Coefficient de pertes de couple dans la transmission

k_max = 6; % vitesse maximale autorisée
fun12 = @(X) Coupleij(rmot,cmot,k_p,k_f,K,1,2,X);
fun23 = @(X) Coupleij(rmot,cmot,k_p,k_f,K,2,3,X);
fun34 = @(X) Coupleij(rmot,cmot,k_p,k_f,K,3,4,X);
fun45 = @(X) Coupleij(rmot,cmot,k_p,k_f,K,4,5,X);
fun56 = @(X) Coupleij(rmot,cmot,k_p,k_f,K,5,6,X);

shift_RPM = [fsolve(fun12,500)/k_p/K(1)/k_f, fsolve(fun23,1000)/k_p/K(2)/k_f, fsolve(fun34,1200)/k_p/K(3)/k_f, fsolve(fun45,1200)/k_p/K(4)/k_f, fsolve(fun56,1500)/k_p/K(5)/k_f ];
shift_Speed = zeros(1,length(shift_RPM));
for i=1:length(shift_RPM)
    shift_Speed(i) = shift_RPM(i)*k_p*K(i)*k_f*2*pi/60*D_wheel/2*3.6;
end

%___Aero___

S= 1.14 ; %surface effective pour la déportance en m²
Cz = 2.23; %coefficient de déportance
Cx = 1.26; %coefficient de trainé
Cz_rep = 0.47; %répartition de la déportance sur l'essieu arrière
%% Save of the workspace

save('test_aero')

%% Functions
function dC = Coupleij(rmot,cmot,k_p,k_f,K,i,j,W)
        rmot1 = W/k_p/K(i)/k_f;
        rmot2 = W/k_p/K(j)/k_f;
        dC = interp1(rmot,cmot,rmot1)/k_p/K(i)/k_f-interp1(rmot,cmot,rmot2)/k_p/K(j)/k_f;
end

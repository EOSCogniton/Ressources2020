% SCRIPT tes pour la fonction findGymax.s

%import parameters :
param_file = "C:\Users\mik75\Documents\FSAEinvictus\Ressources2020\MO_Models\LapTime\test_aeroTire.mat";
load(param_file,'xr','W','xf','m_t','Tf','Tr','h','Cz','rho','S','Cz_rep','p_Cy1', 'p_Dy1', 'p_Ky1')

% rayon du virage
R_turn = 15; %m

% sqp type algorithm
options = optimoptions('fmincon','Algorithm','sqp',...
    'StepTolerance',1e-6,...
    'MaxFunctionEvaluations',2e3,...
    'Display','iter');


fun = @objective;

% needed for linear constraints (empty if not needed)
A = [];
b = [];
Aeq = [];
beq = [];

% x =  [a_y, SA_f, SA_r]
% boundaries (lower) (uper)
lb = [1, 0, 0];
ub = [2000, 0.3, 0.3];


% fcn for the non linear constraints
nonlcon = @constraints;

% starting point (only 1 component)
x0 =  [1, 0, 0];
% function call
x = fmincon(fun,x0,A,b,Aeq,beq,lb,ub,nonlcon,options)
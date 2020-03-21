function [a_y, v_turn] = findGymax(R_turn, param_file)
%FIND Gy max : optimisation multi paramètre et multi contrainte pour un
%modèle de virage statique. 
%   R_turn (m) rayon du virage
%   param_file (str) position absolue du fichier des parmètres (.mat)

R_turn = abs(R_turn);

%import parameters 
load(param_file,'xr','W','xf','m_t','Tf','Tr','h','Cz','rho','S','Cz_rep', 'p_Cy1', 'p_Dy1','p_Ey1', 'p_Ey3', 'p_Ky1', 'p_Hy1', 'p_Vy1', 'q')

% sqp type algorithm
options = optimoptions('fmincon','Algorithm','sqp',...
    'StepTolerance',1e-6,... %précision de la résolution des contraintes
    'MaxFunctionEvaluations',2e3,... % nombre max d'iterations
    'Display','off'); % affichiage des itéraions dans le calcule

% la fonction à minimiser c'est tout simplement la valeur de l'acceleration
fun = @objective;

% needed for linear constraints (empty if not needed)
A = [];
b = [];
Aeq = [];
beq = [];

% x =  [a_y, SA_f, SA_r]
% boundaries (lower) (uper)
lb = [1, 0, 0];
ub = [30, 0.3, 0.3];


% fcn for the non linear constraints
nonlcon = @(x) constraints(x, R_turn, xr, xf, W, m_t, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q);

% starting point (only 1 component)
x0 =  [1, 0, 0];
% function call
x = fmincon(fun,x0,A,b,Aeq,beq,lb,ub,nonlcon,options);

% renvoy des variables de la fonction
a_y = x(1);
v_turn = sqrt(a_y*R_turn);
end

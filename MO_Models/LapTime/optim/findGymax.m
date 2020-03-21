function [a_y, v_turn] = findGymax(R_turn, param_file)
%CONSTRAINT pfd moment
%   Detailed explanation goes here

R_turn = abs(R_turn);

%import parameters 
load(param_file,'xr','W','xf','m_t','Tf','Tr','h','Cz','rho','S','Cz_rep','p_Cy1', 'p_Dy1', 'p_Ky1', 'q')

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
ub = [30, 0.3, 0.3];


% fcn for the non linear constraints
nonlcon = @(x) constraints(x, R_turn, xr, xf, W, m_t, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1, p_Ky1, q);

% starting point (only 1 component)
x0 =  [1, 0, 0];
% function call
x = fmincon(fun,x0,A,b,Aeq,beq,lb,ub,nonlcon,options);

a_y = x(1);
v_turn = sqrt(a_y*R_turn);
end

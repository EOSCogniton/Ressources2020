% SCRIPT tes pour la fonction findGymax.s

%% 0 import parameters :
clear all; close all; clc

param_file = "C:\Users\mik75\Documents\FSAEinvictus\Ressources2020\MO_Models\LapTime\test_aeroTire.mat";
load(param_file,'xr','W','xf','m_t','Tf','Tr','h','Cz','rho','S','Cz_rep', 'p_Cy1', 'p_Dy1','p_Ey1', 'p_Ey3', 'p_Ky1', 'p_Hy1', 'p_Vy1', 'q', 'Zo')

%% 1 test optimization
% rayon du virage
R_turn = 15; %m

% sqp type algorithm
options = optimoptions('fmincon','Algorithm','sqp',...
    'StepTolerance',1e-3,...
    'MaxFunctionEvaluations',7e3,...
    'Display','iter');


fun = @objective;

% needed for linear constraints (empty if not needed)
A = [];
b = [];
Aeq = [];
beq = [];

% x =  [a_y (m/s^2), SA_f (rad), SA_r (rad)]
% boundaries (lower) (uper)
lb = [1, 0, 0];
ub = [30, 1, 1];


% fcn for the non linear constraints
nonlcon = @(x) constraints(x, R_turn, xr, xf, W, m_t, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo);

% starting point (only 1 component)
x0 =  [1, 0, 0];
% function call
x = fmincon(fun,x0,A,b,Aeq,beq,lb,ub,nonlcon,options);

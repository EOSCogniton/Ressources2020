function a_y = findGymax(R_turn)
%CONSTRAINT pfd moment
%   Detailed explanation goes here

% load parameters from workspace
m = evalin('base','m_t');
xf = evalin('base','xf');
xr = evalin('base','xr');

pfd = @(a) (1+xf/xr)*reactionsSum(a, R_turn)-m*a;

% find max lateral acceleration
options = optimset('Algorithm','Levenberg-Marquardt','Display','iter');
a_y = fsolve(pfd,50,options);

end

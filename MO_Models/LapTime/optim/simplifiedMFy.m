function [Y] = simplifiedMFy(Z,SA, p_Cy1, p_Dy1, p_Ky1, q)
%UNTITLED3 schramm Hiller Baldini chapter . section
%   Z N
%   SA rad

eps = 1e-3;

C_y = p_Cy1;

mu_y = p_Dy1;
D_y = mu_y*Z;

K_y = p_Ky1*Z;

B_y = K_y/(C_y*D_y +eps);

Y= q *D_y*sin(C_y*atan(B_y*SA));

end


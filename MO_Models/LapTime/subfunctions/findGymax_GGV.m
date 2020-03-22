function [amax,V_turn] = findGymax_GGV(R_turn,GGV)

V_turn = interp1(GGV(:,5),GGV(:,4),R_turn,'linear','extrap');
amax = V_turn^2/R_turn;

end


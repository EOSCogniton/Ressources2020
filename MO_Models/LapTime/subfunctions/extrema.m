function [idx] = extrema(x)
% This function return the indices of the local extrema value in the list x sorted.
idxmin = find(islocalmin(x,'FlatSelection', 'first')==1); % en cas de plateau seul le premier point est pris en compte.
idxmax = find(islocalmax(x,'FlatSelection', 'first')==1);

idx = [1 ;idxmin; idxmax; length(x)];

idx = sort(idx);
end
    

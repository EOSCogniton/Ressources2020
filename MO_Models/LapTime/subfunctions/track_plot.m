function [] = track_plot(X, Y, speed)
% X et Y sont des coordonnées venant de lat_longi2X_Y
% speed est en km/h

z = zeros(size(X'));
col = speed';  % This is the color, vary with x in this case.
surface([X';X'],[Y';Y'],[z;z],[col;col],'facecol','no','edgecol','interp','linew',2);
c = colorbar;
xlabel('X (m)')
ylabel('Y (m)')
c.Label.String = 'Vitesse Km/h';
axis equal
end

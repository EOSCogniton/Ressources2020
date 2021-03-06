clear all;
close all;

T_1 = readtable('SE-20-002-E02_1_carto_base.txt');

rpm_1 = table2array(T_1(1:end,2));
ch_brut_1 = str2double(strrep(table2array(T_1(1:end,3)),',','.'));
ch_roue_1 = str2double(strrep(table2array(T_1(1:end,4)),',','.'));
ch_roue_corrige_1 = str2double(strrep(table2array(T_1(1:end,5)),',','.'));
couple_roue_corrige_1 = str2double(strrep(table2array(T_1(1:end,6)),',','.'));
ch_moteur_corrige_1 = str2double(strrep(table2array(T_1(1:end,7)),',','.'));
couple_moteur_corrige_1 = str2double(strrep(table2array(T_1(1:end,8)),',','.'));

T_2 = readtable('SE-20-002-E09_1.txt');

rpm_2 = table2array(T_2(1:end,2));
ch_brut_2 = str2double(strrep(table2array(T_2(1:end,3)),',','.'));
ch_roue_2 = str2double(strrep(table2array(T_2(1:end,4)),',','.'));
ch_roue_corrige_2 = str2double(strrep(table2array(T_2(1:end,5)),',','.'));
couple_roue_corrige_2 = str2double(strrep(table2array(T_2(1:end,6)),',','.'));
ch_moteur_corrige_2 = str2double(strrep(table2array(T_2(1:end,7)),',','.'));
couple_moteur_corrige_2 = str2double(strrep(table2array(T_2(1:end,8)),',','.'));


figure(1)
%  T_1
plot(rpm_1,ch_moteur_corrige_1,'b')
hold on
grid on
plot(rpm_1,couple_moteur_corrige_1,'r')
% T_2
plot(rpm_2,ch_moteur_corrige_2,'--b')
plot(rpm_2,couple_moteur_corrige_2,'--r')
title('Puissance et Couple corrigé au moteur E09-E01')
legend('Ch-carto-base','Couple-carto-base','Ch-carto-fin','Couple-carto-fin')






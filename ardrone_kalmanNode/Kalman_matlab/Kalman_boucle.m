function [ Xk,Pk,Prediction ] = Kalman_boucle(Cmesure, R, Xprec1, Pprec1, Zprec1 )
%KALMAN_boucle Summary of this function goes here
%   Detailed explanation goes here
% Boucle de filtre de Kalman
    
%Initialisations
    %Temps d'�chantillonnage
    Te = 1;
    %Process noise
    incertitude_modele = 1;
    Q = incertitude_modele * eye(2);
    M = 1;
    
    Xk=zeros(2,1);  %6 si on prend en compte l'acc�l�ration
    Prediction=zeros(2,1);  %6 si on prend en compte l'acc�l�ration
    Pk=eye(2);     %6 si on prend en compte l'acc�l�ration
    Zk=zeros(8,1); %10 si on prend en compte l'acc�l�ration
    In=zeros(8,1); %10
    Xprec=zeros(2,1);
    Xprec=Xprec1;
    C=zeros(8,2);
    C=Cmesure; 
    
    Pprec=zeros(2,2);
    Zprec=zeros(8,1);
    Pprec=Pprec1;
    Zprec=Zprec1;
    
    % Matrice d'�tat
    A = [1  0       %position, vitesse sur X
         0  1];      %position, vitesse sur Y 
         

    % Matrice des mesures
%     C=[ 1 0      %position X     GPS
%         0 1      %position Y     GPS
%         1 0      %position X     ODOM
%         0 1      %position Y     ODOM
%         1 0      %position X     TAG
%         0 1      %position Y     TAG
%         1 0      %position X     XTUM
%         0 1];    %position Y     YTUM


    
    
    
    %Prediction
    Xk=A*Xprec;
    Pk=A*Pprec+(M*Q*M');
        
    %Innovation
    In=Zprec-(C*Xk);
    Kk=Pk*C'*inv((C*Pk*C')+R);
    
    %Mise a jour
    Xk=Xk+Kk*In;
    Pk=(eye(2)-Kk*C)*Pk;
    
    %Incrementation
    Prediction(1)=Xk(1); %X
    Prediction(2)=Xk(2); %Y
    
    
end


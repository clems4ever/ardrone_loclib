function [ Xk,Pk,Prediction ] = Kalman_boucle2( R, Xprec, Pprec, Zprec )
%KALMAN_boucle Summary of this function goes here
%   Detailed explanation goes here
% Boucle de filtre de Kalman
    
%Initialisations
    %Temps d'échantillonnage
    Te = 1;
    %Process noise
    incertitude_modele = 1;
    Q = incertitude_modele * eye(2);
    M = 1;
    
    Xk=zeros(2,1);  %6 si on prend en compte l'accélération
    Prediction=zeros(2,1);  %6 si on prend en compte l'accélération
    Pk=eye(2);     %6 si on prend en compte l'accélération
    Zk=zeros(8,1); %10 si on prend en compte l'accélération
    In=zeros(8,1); %10
     
    
    % Matrice d'état
    A = [1  0       %position, vitesse sur X
         0  1];      %position, vitesse sur Y 
         

    % Matrice des mesures
    C=[ 1 0      %position X     GPS
        0 1      %position Y     GPS
        1 0      %position X     ODOM
        0 1      %position Y     ODOM
        1 0      %position X     TAG
        0 1      %position Y     TAG
        0 0      %position X     XTUM
        0 0];    %position Y     YTUM


    
    
    
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


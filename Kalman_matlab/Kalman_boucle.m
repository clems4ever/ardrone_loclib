function [ Xk,Pk,Prediction ] = Kalman_boucle( R, Xprec, Pprec, Zprec )
%KALMAN_boucle Summary of this function goes here
%   Detailed explanation goes here
% Boucle de filtre de Kalman
    
%Initialisations
    %Temps d'échantillonnage
    Te = 1;
    %Process noise
    incertitude_modele = 1;
    Q = incertitude_modele * eye(4);
    M = 1;
    
    Xk=zeros(4,1);  %6 si on prend en compte l'accélération
    Prediction=zeros(4,1);  %6 si on prend en compte l'accélération
    Pk=eye(4);     %6 si on prend en compte l'accélération
    Zk=zeros(8,1); %10 si on prend en compte l'accélération
    In=zeros(8,1); %10
     
    
    % Matrice d'état
    A = [1  0   Te   0;      %position, vitesse sur X
         0  1   0   Te;     %position, vitesse sur X 
         0  0   1   0;      %vitesse sur X
         0  0   0   1];     %vitesse sur Y

    % Matrice des mesures
    C=[ 1 0 0 0      %position X     GPS
        0 1 0 0      %position Y     GPS
        1 0 0 0      %position X     ODOM
        0 1 0 0      %position Y     ODOM
        1 0 0 0      %position X     TAG
        0 1 0 0      %position Y     TAG
        0 0 1 0      %vitesse X      VIMU
        0 0 0 1];    %vitesse Y      VIMU

% /!\ ne fonctionne pas lorsque l'on génére le code matlab en C
%     %Maj de C en fonction de la présence où non des mesures /!\
%      %GPS
%      if ( Zprec(1) > 2000000 || Zprec(2) > 2000000 )
%         C(1,:) = [0 0 0 0];
%         C(2,:) = [0 0 0 0];     
%      else
%          C(1,:) = [1 0 0 0];
%          C(2,:) = [0 1 0 0];
%      end
%      
%      %ODOM
%      if ( Zprec(3) > 2000000 || Zprec(4) > 2000000 )
%         C(3,:) = [0 0 0 0];
%         C(4,:) = [0 0 0 0];     
%      else
%          C(3,:) = [1 0 0 0];
%          C(4,:) = [0 1 0 0];
%      end
%      
%      %TAG
%      if ( Zprec(5) > 2000000 || Zprec(6) > 2000000 )
%         C(5,:) = [0 0 0 0];
%         C(6,:) = [0 0 0 0];      
%      else
%          C(5,:) = [1 0 0 0];
%          C(6,:) = [0 1 0 0];
%      end   
%      
%      %IMU
%      if ( Zprec(7) > 2000000 || Zprec(8) > 2000000 )
%         C(7,:) = [0 0 0 0];
%         C(8,:) = [0 0 0 0];      
%      else
%          C(7,:) = [0 0 1 0];
%          C(8,:) = [0 0 0 1];
%      end   
    
    
    
    
    %Prediction
    Xk=A*Xprec;
    Pk=A*Pprec+(M*Q*M');
        
    %Innovation
    In=Zprec-(C*Xk);
    Kk=Pk*C'*inv((C*Pk*C')+R);
    
    %Mise a jour
    Xk=Xk+Kk*In;
    Pk=(eye(4)-Kk*C)*Pk;
    
    %Incrementation
    Prediction(1)=Xk(1); %X
    Prediction(2)=Xk(2); %Y
    Prediction(3)=Xk(3); %VX
    Prediction(4)=Xk(4); %VY
    
end


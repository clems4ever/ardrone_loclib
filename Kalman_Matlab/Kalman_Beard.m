% Script filtre de Kalman
close all

% GÃ©nÃ©ration des donnï¿½es de position et de mesure
%DataGeneration_clean;
DataGeneration_SensorError;





%--Init
% Positions initiales
Ximu0=0;
Xgps0=0;
Xodom0=0;

% Temps d'Ã©chantillonnage
Te=1; % 1 seconde

X0=zeros(4,1);  %6 si on prend en compte l'accï¿½lï¿½ration
P0=eye(4);     %6 si on prend en compte l'accï¿½lï¿½ration
Z0=zeros(8,1); %10 si on prend en compte l'accï¿½lï¿½ration

%on ne prend pas en compte l'accélération
A=[1    0  Te   0;      %position, vitesse sur X
   0    1   0   Te;     %position, vitesse sur X 
   0    0   1   0;      %vitesse sur X
   0    0   0   1];     %vitesse sur Y
   

%on prend en compte l'accélération
% A=[1    0  Te   0   Te*Te*0.5   0;          %position, vitesse sur X
%    0    1   0   Te  0           Te*Te*0.5 ; %position, vitesse sur X 
%    0    0   1   0   Te          0;          %vitesse, accélération sur X
%    0    0   0   1   0           Te;         %vitesse, accélération sur Y
%    0    0   0   0   1           0;          %accélération sur X
%    0    0   0   0   0           1 ];        %accélération sur Y

C=[1 0 0 0      %position X     GPS
   0 1 0 0      %position Y     GPS
   1 0 0 0      %position X     ODOM
   0 1 0 0      %position Y     ODOM
   1 0 0 0      %position X     TAG
   0 1 0 0      %position Y     TAG
   0 0 1 0      %vitesse X      VIMU
   0 0 0 1];     %vitesse Y      VIMU

% C=[1 0 0 0 0 0;     %position X     GPS
%    0 1 0 0 0 0;     %position Y     GPS
%    1 0 0 0 0 0;     %position X     ODOM
%    0 1 0 0 0 0;     %position Y     ODOM
%    1 0 0 0 0 0;     %position X     TAG
%    0 1 0 0 0 0;     %position Y     TAG
%    0 0 1 0 0 0;     %vitesse X      VIMU
%    0 0 0 1 0 0;     %vitesse Y      VIMU
%    0 0 0 0 1 0;     %accélération X AIMU
%    0 0 0 0 0 1];    %accélération Y AIMU


%Process noise
Q=1*eye(4);

%Incertitudes = Variance = EcartType²
Rgps = ErreurGPS*ErreurGPS;
Rodom = ErreurODOM*ErreurODOM;
Rtag = ErreurTAG*ErreurTAG;
RVimu = ErreurV*ErreurV;
%RAimu = ErreurA*ErreurA;

%sans accélération
R=[Rgps     0       0       0       0       0       0       0; 
   0        Rgps    0       0       0       0       0       0;
   0        0       Rodom   0       0       0       0       0;
   0        0       0       Rodom   0       0       0       0;
   0        0       0       0       Rtag    0       0       0;
   0        0       0       0       0       Rtag    0       0;
   0        0       0       0       0       0       RVimu   0;
   0        0       0       0       0       0       0       RVimu];
   

%avec accélération
% R=[Rgps     0       0       0       0       0       0       0       0       0; 
%    0        Rgps    0       0       0       0       0       0       0       0;
%    0        0       Rodom   0       0       0       0       0       0       0;
%    0        0       0       Rodom   0       0       0       0       0       0;
%    0        0       0       0       Rtag    0       0       0       0       0;
%    0        0       0       0       0       Rtag    0       0       0       0;
%    0        0       0       0       0       0       RVimu   0       0       0;
%    0        0       0       0       0       0       0       RVimu   0       0;
%    0        0       0       0       0       0       0       0       RAimu   0;
%    0        0       0       0       0       0       0       0       0       RAimu];

%Generation des valeurs
k=1;
t=0;

Mesure = zeros(N, 8);
while k<N+1
    Mesure(k,1)=X_GPS(k,1);   %GPSx
    Mesure(k,2)=Y_GPS(k,1);   %GPSy
    Mesure(k,3)=X_ODOM(k,1);  %OdomX
    Mesure(k,4)=Y_ODOM(k,1);  %OdomY
    Mesure(k,5)=X_TAG(k,1);   %TagX
    Mesure(k,6)=Y_TAG(k,1);   %TagY  
    Mesure(k,7)=VX_IMU(k,1);  %IMUVx
    Mesure(k,8)=VY_IMU(k,1);  %IMUVy 
    %Mesure(k,9)=AX_IMU(k,1);  %IMUAx
    %Mesure(k,10)=AY_IMU(k,1); %IMUAy 
    
    k=k+1;    
end



% Generation du bruit blanc
Moyenne_bruit=0;
Ecart_type=0.1;
constante=0.05;
Bruit = constante+Moyenne_bruit+(Ecart_type*Ecart_type)*randn(1,50);

%Creation du modèle
M=1;
    
 Xprec=X0;
 Pprec=P0;
 Zprec=Z0;
    
 %Mise en place du filtre
 k=0;
 while k<N
     %Maj de C en fonction de la présence où non des mesures /!\
     %GPS
     if ( k<3 || Zprec(1,1) == 0 || Zprec(2,1) == 0 )
        C(1,:) = [0 0 0 0];
        C(2,:) = [0 0 0 0];     
     else
         C(1,:) = [1 0 0 0];
         C(2,:) = [0 1 0 0];
     end
     
     %ODOM
     if ( k<3 || Zprec(3,1) == 0 || Zprec(4,1) == 0 )
        C(3,:) = [0 0 0 0];
        C(4,:) = [0 0 0 0];     
     else
         C(3,:) = [1 0 0 0];
         C(4,:) = [0 1 0 0];
     end
     
     %TAG
     if ( k<3 || Zprec(5,1) == 0 || Zprec(6,1) == 0 )
        C(5,:) = [0 0 0 0];
        C(6,:) = [0 0 0 0];      
     else
         C(5,:) = [1 0 0 0];
         C(6,:) = [0 1 0 0];
     end
     
     
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
     k=k+1;
     Pred(k,1)=Xk(1); %X
     Pred(k,2)=Xk(2); %Y
     Pred(k,3)=Xk(3); %VX
     Pred(k,4)=Xk(4); %VY
     
     Xprec=Xk;
     Pprec=Pk;
     Zprec=Mesure(k,:)'; 
 end
 
 figure(5)
 
 %PositionX 
 subplot(4,1,1);
 plot(X(:,1),'k') % Position réelle X
 xlabel('Temps');
 ylabel('Position X');
 hold on
 plot(Pred(:,1), 'r') % Prédiction X
 
 %PositionY
 subplot(4,1,2);
 plot(Y(:,1),'k') % Position réelle Y
 xlabel('Temps');
 ylabel('Position Y');
 hold on
 plot(Pred(:,2), 'r') % Prédiction Y

 %VitesseX
 subplot(4,1,3);
 plot(VX(:,1),'k') % Vitesse réelle VX
 xlabel('Temps');
 ylabel('Vitesse X');
 hold on
 plot(Pred(:,3), 'r') % Prédiction VX
 
 %VitesseY
 subplot(4,1,4);
 plot(VY(:,1),'k') % Vitesse réelle VY
 xlabel('Temps');
 ylabel('Vitesse Y');
 hold on
 plot(Pred(:,4), 'r') % Prédiction VY
 legend('reel','estimation')

 %AccelerationX
%  subplot(6,1,5);
%  plot(AX(:,1),'k') % Acceleration réelle AX
%  hold on
%  plot(Pred(:,5), 'r') % Prédiction AX
 
 %AccelerationY
%  subplot(6,1,6);
%  plot(AY(:,1),'k') % Acceleration réelle AY
%  hold on
%  plot(Pred(:,6), 'r') % Prédiction AY
%  
 figure(6) 
 plot (X, Y,'k');
 xlabel('Position X');
 ylabel('Position Y');
 hold on
 plot (Pred(:,1), Pred(:,2), 'r');
 legend('reel','estimation')
 
 
 
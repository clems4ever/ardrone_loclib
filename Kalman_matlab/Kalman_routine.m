% Script routine faisant appel à la fonction Kalman_boucle
close all

% Génération des données de position et de mesure
%DataGeneration_clean;
DataGeneration_SensorError;



%--Init
X0=zeros(4,1);  
P0=eye(4);     
Z0=zeros(8,1); 
Pred=zeros(N,4); 
Mesure=zeros(8,N); 



%Incertitudes = Variance = EcartType²
Rgps = ErreurGPS*ErreurGPS;
Rodom = ErreurODOM*ErreurODOM;
Rtag = ErreurTAG*ErreurTAG;
RAimu = ErreurA*ErreurA;
RVimu = ErreurV*ErreurV;

%sans accélération
R=[Rgps     0       0       0       0       0       0       0; 
   0        Rgps    0       0       0       0       0       0;
   0        0       Rodom   0       0       0       0       0;
   0        0       0       Rodom   0       0       0       0;
   0        0       0       0       Rtag    0       0       0;
   0        0       0       0       0       Rtag    0       0;
   0        0       0       0       0       0       RVimu   0;
   0        0       0       0       0       0       0       RVimu];
   

%Generation des valeurs, récupération des mesures
k=1;


while k<N+1
    Mesure(1,k)=X_GPS(k,1);   %GPSx
    Mesure(2,k)=Y_GPS(k,1);   %GPSy
    Mesure(3,k)=X_ODOM(k,1);  %OdomX
    Mesure(4,k)=Y_ODOM(k,1);  %OdomY
    Mesure(5,k)=X_TAG(k,1);   %TagX
    Mesure(6,k)=Y_TAG(k,1);   %TagY  
    Mesure(7,k)=VX_IMU(k,1);  %IMUVx
    Mesure(8,k)=VY_IMU(k,1);  %IMUVy 
        
    k=k+1;    
end




% Création du modèle    
 Xprev=X0;
 Pprev=P0;
 Zprev=Z0;
 Xprec=X0;
 Pprec=P0;
 Zprec=Z0;
    
 % Mise en place du filtre
 k=1;
 while k<N+1
      
      if (k>20 && k<60)
          Rgps = 5000;
          Rodom = 5000;
      end
      if (Mesure(7,k)==0 || Mesure(8,k)==0)
          Rtag = 5000;
      else 
          Rtag = ErreurTAG*ErreurTAG;
      end
     
     
     [ Xprec,Pprec,Pred(k,:)] = Kalman_boucle(R, Xprev, Pprev, Zprev);   
      Xprev=Xprec;
      Pprev=Pprec;
      Zprev=Zprec;
      Zprec=Mesure(:,k); 
      k=k+1;
 end
 
 %Courbes
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


 figure(6) 
 plot (X, Y,'k');
 xlabel('Position X');
 ylabel('Position Y');
 hold on
 plot (Pred(:,1), Pred(:,2), 'r');
 legend('reel','estimation')
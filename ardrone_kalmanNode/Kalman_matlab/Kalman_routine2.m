% Script routine2 faisant appel à la fonction Kalman_boucle2
close all

% Génération des données de position et de mesure
DataGenerationKalmanTUM;



%--Init
X0=zeros(2,1);  
P0=eye(2);     
Z0=zeros(8,1); 
Pred=zeros(N,2); 
Mesure=zeros(8,N); 



%Incertitudes = Variance = EcartType²
Rgps = ErreurGPS*ErreurGPS;
Rodom = ErreurODOM*ErreurODOM;
Rtag = ErreurTAG*ErreurTAG;
Rtum = ErreurTUM*ErreurTUM;


%sans accélération
R=[Rgps     0       0       0       0       0       0       0; 
   0        Rgps    0       0       0       0       0       0;
   0        0       Rodom   0       0       0       0       0;
   0        0       0       Rodom   0       0       0       0;
   0        0       0       0       Rtag    0       0       0;
   0        0       0       0       0       Rtag    0       0;
   0        0       0       0       0       0       Rtum    0;
   0        0       0       0       0       0       0       Rtum];
   

%Generation des valeurs, récupération des mesures
k=1;


while k<N+1
    Mesure(1,k)=X_GPS(k,1);   %GPSx
    Mesure(2,k)=Y_GPS(k,1);   %GPSy
    Mesure(3,k)=X_ODOM(k,1);  %OdomX
    Mesure(4,k)=Y_ODOM(k,1);  %OdomY
%     Mesure(5,k)=X_TAG(k,1);   %TagX
%     Mesure(6,k)=Y_TAG(k,1);   %TagY  
    Mesure(5,k)=X_TUM(k,1);   %TagX
    Mesure(6,k)=Y_TUM(k,1);   %TagY 
    Mesure(7,k)=X_TUM(k,1);   %TUMx
    Mesure(8,k)=Y_TUM(k,1);   %TUMy 
        
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
     
     
     [ Xprec,Pprec,Pred(k,:)] = Kalman_boucle2(R, Xprev, Pprev, Zprev);   
      Xprev=Xprec;
      Pprev=Pprec;
      Zprev=Zprec;
      Zprec=Mesure(:,k); 
      k=k+1;
      
      if (  Zprev(5)==0 || Zprev(6)==0)
          Rtag = 5000
%       else 
%           Rtag = ErreurTAG*ErreurTAG
      end
     
       R(5,5)=Rtag;
       R(5,6)=Rtag;

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

 


 figure(6) 
 plot (X, Y,'k');
 xlabel('Position X');
 ylabel('Position Y');
 hold on
 plot (Pred(:,1), Pred(:,2), 'r');
 legend('reel','estimation')
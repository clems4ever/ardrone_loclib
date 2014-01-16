clear all
close all

% Génération de donnée pour le filtre de Kalman
% Initialisation

% nb de step
N = 100 ;

% données à générer :
% X en m, position réelle
X = zeros(N,1);
% VX en m/s, vitesse réelle
VX = zeros(N,1);
% AX en m/s², accélération réelle
AX = zeros(N,1);
% X_GPS en m
X_GPS = zeros(N,1);
% X_TAG en m
X_TAG = zeros(N,1);
% X_ODOM en m
X_ODOM = zeros(N,1);
% VX_IMU en m/s
VX_IMU = zeros(N,1);
% AX_IMU en m/s²
AX_IMU = zeros(N,1);


% Y en m, position réelle
Y = zeros(N,1);
% VY en m/s, vitesse réelle
VY = zeros(N,1);
% AY en m/s², accélération réelle
AY = zeros(N,1);
% Y_GPS en m
Y_GPS = zeros(N,1);
% Y_TAG en m
Y_TAG = zeros(N,1);
% Y_ODOM en m
Y_ODOM = zeros(N,1);
% VY_IMU en m/s
VY_IMU = zeros(N,1);
% AY_IMU en m/s²
AY_IMU = zeros(N,1);


% Utilisation de la fonction randn() pour simuler les erreurs de mesure.
% Generate values from a normal distribution with mean 1 and standard
%        deviation 2.
%           r = 1 + 2.*randn(100,1);

% données à générer :
% X en m
% X_GPS en m
% X_TAG en m
% X_ODOM en m
% V_IMU en m/s
% A_IMU en m/s²
% de même pour Y

%génération de l'accélération réelle
for j = 1 : N/5
    AX(j,1) = 2.5/(N/5) ; 
    AY(j,1) = -2.5/(N/5) ; 
end

for j = 1 + N/5  : N-(N/5)
    AX(j,1) = 0 ;
    AY(j,1) = 0 ;
end

for j = 40 : 50
    AY(j,1) = -2.5/(N/5) ; 
end

for j = 1 + N-(N/5)  : N
    AX(j,1) = -2.5/(N/5) ;
    AY(j,1) = +2.5/(N/5) ;
end

%génération de la vitesse et de la position réelle
for j = 2 : N
    VX(j,1) = VX(j-1,1)+AX(j,1);  
    VY(j,1) = VY(j-1,1)+AY(j,1);  
    X(j,1) = X(j-1,1)+VX(j,1);
    Y(j,1) = Y(j-1,1)+VY(j,1);
end

%génération des bruits de mesure
ErreurGPS = 20; 
ErreurTAG = 0.1;
ErreurODOM = 5;
ErreurV = 1;
ErreurA = 0.1;

X_GPS = X + ErreurGPS*randn(N,1);
Y_GPS = Y + ErreurGPS*randn(N,1);
% absence réception signal GPS
for j = 30 : 50
    X_GPS(j,1) = -10000;
    Y_GPS(j,1) = -10000;
end

X_ODOM = X + ErreurODOM*rand(N,1);
Y_ODOM = Y + ErreurODOM*rand(N,1);
for j = 40 : 50
    X_ODOM(j,1) = -10000;
    Y_ODOM(j,1) = -10000;
end

VX_IMU = VX + ErreurV*rand(N,1);
AX_IMU = AX + ErreurA*rand(N,1);

VY_IMU = VY + ErreurV*rand(N,1);
AY_IMU = AY + ErreurA*rand(N,1);


% On simule la detection d'un TAG tout les 10m

X_TAG(:,1) = -10000
Y_TAG(:,1) = -10000;

for j = 1 : 30 : N
    X_TAG(j,1) = X(j,1) + ErreurTAG*randn(1,1);
    Y_TAG(j,1) = Y(j,1) + ErreurTAG*randn(1,1);
end


%plot
figure(1)
subplot (2,1,1), plot(X,'b')
hold on
subplot (2,1,1), plot(X_GPS, 'r')
hold on
subplot (2,1,1), plot(X_TAG, 'c')
hold on
subplot (2,1,1), plot(X_ODOM, 'g')
subplot (2,1,2), plot(VX,'k')
hold on
subplot (2,1,2), plot(VX_IMU,'y')
hold on
subplot (2,1,2), plot(AX,'r')
hold on
subplot (2,1,2), plot(AX_IMU,'m')
% 
% 
% figure(2)
subplot (2,1,1), plot(Y,'b')
hold on
subplot (2,1,1), plot(Y_GPS, 'r')
hold on
subplot (2,1,1), plot(Y_TAG, 'c')
hold on
subplot (2,1,1), plot(Y_ODOM, 'g')
subplot (2,1,2), plot(VY,'k')
hold on
subplot (2,1,2), plot(VY_IMU,'y')
hold on
subplot (2,1,2), plot(AY,'r')
hold on
subplot (2,1,2), plot(AY_IMU,'m')


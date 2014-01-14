%% Initialisation
% on simule un vol de 20s o� le drone va se d�placer sur X selon le mod�le
% suivant :
% t :    0  1   2   3   4   5   6   7   8   9   10
% Xpos : 0  2   6   10  14  18  22  26  30  34  36
% Xvit : 0  2   4   4   4   4   4   4   4   2   0
% Xacc : 2  2   0   0   0   0   0   0   0   -2  -2

V_IMU = [0  2   4   4   4   4   4   4   4   2   0];
A_IMU = [2  2   0   0   0   0   0   0   0   -2  -2];
X_GPS = [0  3   5   8   16  20  23  25.5 33 35  38];
X_ODOM =[0  2.5 6.8 9.5 12.9 18.4 23.5 25.8 30.4 33.2 36.5];
X_TAG = [0  2.1 5.9 10.2 13.9 18.1 22.2 25.8 29.9 34.2 36.1];

i = 1;
Te = 1;
epsilonA = 1; %m�tre
epsilonB = 1; %m/s
epsilonC = 1; %m/s�
sigma1 = 0.5; %m/s
sigma2 = 0.5; %m/s�
sigma3 = 10; %m
sigma4 = 2; %m
sigma5 = 1; %m

% initialisation de l'�tat : position, vitesse et acc�leration nulle.
X = [ 0 ;
      0 ;
      0 ];


%% D�finition des matrices du filtres

% (1) Xk+1 = A.Xk + B.uk + G.vk
% (2) Zk = Hk.Xk + D.wk

% Xk vecteur d'�tat
% uk entr�e de commande connue
% vk incertitude de l'�volution de l'�tat
% A matrice d'�tat
% B matrice d'entr�e
% G matrice de bruit

% Zk vecteur d'observation
% wk vecteur d'incertitude d'observation
% H matrice d'observation
% D matrice du bruit d'observation

% (1) Xk+1 = A.Xk + B.uk + G.vk

% A = [ 1  Te  Te�/2 ;     Xk = [ position
%       0  1   Te    ;            vitesse
%       0  0   1     ]            acc�l�ration ]

A = [ 1  Te  (Te^2)/2   ;    
      0  1   Te         ;            
      0  0   1          ];
  
% B = [ 1 0 0 ];     uk = [ pos ;  consigne de position uniquement
%                           0   ; 
%                           0   ]
B = [ 1 0 0 ];

% G = [ epsilonA    0           0           ; epsilonA : 1m de pr�cision
%       0           epsilonB    0           ; epsilonB : ?
%       0           0           epsilonC    ];epsilonC : ?
G = [ epsilonA    0           0           ;
      0           epsilonB    0           ;
      0           0           epsilonC    ];

% (2) Zk = Hk.Xk + D.wk
% Les donn�es dont on dispose pour notre positionnement :
% vitesse imu   acc�l�ration imu    position GPS    position V_odom     position TAG 
% 3 donn�es de position
% 1 vitesse
% 1 acc�l�ration

% Zk = [ V_IMU  ;
%        A_IMU  ;
%        X_GPS  ;
%        X_ODOM ;
%        X_TAG  ];
Z = zeros(5,1);
Z = [ V_IMU(i)  ;
       A_IMU(i)  ;
       X_GPS(i)  ;
       X_ODOM(i) ;
       X_TAG(i)  ];

% H = [ 0   1   0 ;     Xk = [ position     
%       0   0   1 ;            vitesse
%       1   0   0 ;            acc�l�ration ]
%       1   0   0 ;
%       1   0   0 ];
H = [ 0   1   0 ;     
      0   0   1 ;
      1   0   0 ;
      1   0   0 ;
      1   0   0 ];

% D.wk = [ sigma1� ; �cart type bruit V_IMU
%          sigma2� ; �cart type bruit A_IMU
%          sigma3� ; �cart type bruit X_GPS
%          sigma4� ; �cart type bruit X_ODOM
%          sigma5� ];�cart type bruit X_TAG 
D.wk = [ sigma1^2 ;
         sigma2^2 ;
         sigma3^2 ;
         sigma4^2 ;
         sigma5^2 ];

     
%% Kalman
% Prediction
% Xk+ = A.Xk
% Pk+ = A.Pk.At + Q

Xnext = A*X;
Pnext = 



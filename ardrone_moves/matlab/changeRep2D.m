function [X,Y] = changeRep2D(X1,Y1,phi)
%phi en radians, angle entre X et X1
%i.e. positif si rotation de X(nouveau rep) vers X1(ancien rep) dans le sens trigonométrique

X=X1*cos(phi)+Y1*sin(phi);
Y=-X1*sin(phi)+Y1*cos(phi);

%=the output vector is a rotation of -phi of the input vector

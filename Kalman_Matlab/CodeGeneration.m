 arg1=[double(0); double(0); double(0); double(0); double(0); double(0); double(0); double(0)];
 arg2 = eye(8);
 arg3 = [double(0); double(0); double(0); double(0)];
 arg4 = eye(4);
 arg5=[double(0); double(0); double(0); double(0); double(0); double(0); double(0); double(0)];
 
 
 codegen Kalman_boucle -config:lib -args { zeros(8,1), zeros(8,8), zeros(4,1), zeros(4,4), zeros(8,1) }
 
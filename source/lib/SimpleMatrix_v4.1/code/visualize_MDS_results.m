% Run this code in MATLAB after running demo_matrix.exe

clear;clc;close all;
load swissroll.mat;
X1=load('swissX1.txt');
X2=load('swissX2.txt');
X3=load('swissX3.txt');
X4=load('swissX4.txt');
figure;
subplot(2,3,1);
trisurf(swiss.TRIV,swiss.X,swiss.Y,swiss.Z);
title('Swiss roll surface');
subplot(2,3,2);
trisurf(swiss.TRIV,X1(:,1),X1(:,2),X1(:,3));
title('flattened surface (UCF without initialization)');
subplot(2,3,3);
trisurf(swiss.TRIV,X2(:,1),X2(:,2),X2(:,3));
title('flattened surface (SMACOF without initialization)');
subplot(2,3,4);
trisurf(swiss.TRIV,X3(:,1),X3(:,2),X3(:,3));
title('flattened surface (UCF with initialization)');
subplot(2,3,5);
trisurf(swiss.TRIV,X4(:,1),X4(:,2),X4(:,3));
title('flattened surface (SMACOF with initialization)');
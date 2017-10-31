%Created by Fanlin Wang

xyz = dlmread('cv_planar_points.txt')
%total = 441;
x = xyz(:,1);
y = xyz(:,2);
z = xyz(:,3);

% lab3 1.2
% linear regression methods Ax = b 
% here B is 441 * 1 matrix filled with 1
%b = ones(total,1);
AtA = transpose(xyz) * xyz;
% solve for plane-parameters  (A, B, C) 
plane_parameter = inv(AtA) * (transpose(xyz) * b)



P=[mean(x),mean(y),mean(z)];
xyzsub = bsxfun(@minus,xyz,P);
[U,S,V] = svd(xyzsub,0);
N=-1/V(end,end)*V(:,end);

%Call svd on the mean subtracted data. 
%The singular vector (in V) corresponding to the smallest singular value 
%contains the coefficients a,b,c.
% ˆn is chosen as the normalized eigenvector corresponding to min(A).
abc = V(:,3);
%Recover the constant d.
d = -dot(P,abc);
%The magnitude of the singular values will be a measure of how well
%the data fits a plane. So look at diag(S)
diag(S);

[X,Y]=meshgrid(linspace(min(x),max(x),20),linspace(min(y),max(y),20));

n_1=N(1); n_2=N(2); n_3=-P*N;
Z=(n_1*X)+(n_2*Y)+n_3;

plot3(x,y,z,'r.'); hold on; grid on;
surf(X,Y,Z,'FaceColor','g'); alpha(0.5);
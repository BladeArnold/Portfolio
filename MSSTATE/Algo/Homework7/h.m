A = randn(8,4);
A(:,5:6) = A(:,1:2)+A(:,3:4);
[Q,R] = qr(randn(6));
A = A*Q;
[U, S, V] = svd(A);
format short e
SingularValues = diag(S)
r = rank(A, 1e-14)
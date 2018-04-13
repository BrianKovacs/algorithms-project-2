function generateSVD()
[U,S,V] = svd(A,'econ');
W = transpose(V);
save('brain_SVD.txt','U','S','W','-ascii');
end
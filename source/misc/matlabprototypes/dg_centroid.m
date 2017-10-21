function [Xc, Yc] = dg_centroid(X, Y)
if length(X) == 2
    Xc = mean(X(1:end));
    Yc = mean(Y(1:end));
elseif length(X) > 1
    Xc = mean(X(1:end-1));
    Yc = mean(Y(1:end-1));
else
    Xc = X(1);
    Yc = Y(1);
end
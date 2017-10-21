function [Xb, Yb] = dg_boundingbox(X, Y, pad)
xmax = max(X);
xmin = min(X);
ymax = max(Y);
ymin = min(Y);

Xb = [xmin - pad, xmin - pad, xmax + pad, xmax + pad, xmin - pad];
Yb = [ymin - pad, ymax + pad, ymax + pad, ymin - pad, ymin - pad];

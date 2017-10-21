function d = dg_upperbounddiameter(X, Y)
xmax = max(X);
xmin = min(X);
ymax = max(Y);
ymin = min(Y);
height = ymax - ymin;
width = xmax - xmin;
d = sqrt(height * height + width * width);
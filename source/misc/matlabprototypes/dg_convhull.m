function [X, Y] = dg_convhull(X_in, Y_in)
%epsilon = 0.00001;
L = length(X_in);
if (L == 1)
    % single point, we leave it
    X = X_in;
    Y = Y_in;
elseif (L == 2)
    % line, we leave it
    if (X_in(2) == X_in(1) && Y_in(2) == Y_in(1))
        % coincident points --> single point
        X = X_in(1);
        Y = Y_in(1);
    else
        X = X_in;
        Y = Y_in;
    end
%    minx = min(X_in);
%    maxx = max(X_in);
%    miny = min(Y_in);
%    maxy = max(Y_in);
%    X = [minx-epsilon minx-epsilon maxx+epsilon maxx+epsilon minx-epsilon];
%    Y = [miny-epsilon maxy+epsilon maxy+epsilon miny-epsilon miny-epsilon];
else
    K = convhull(X_in, Y_in);
    [X, Y] = POLY2CW(X_in(K), Y_in(K));
end
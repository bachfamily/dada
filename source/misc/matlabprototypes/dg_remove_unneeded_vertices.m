function [Xout, Yout] = dg_remove_unneeded_vertices(Xin, Yin, Xpt, Ypt)

X = Xin;
Y = Yin;

% Now the refinement part. First we see if any of the points is useless
if 1 == 1
    i = 2;
    while i <= length(X)
        Xwk = [X X(2)];
        Ywk = [Y Y(2)];
        X_tri = [Xwk(i-1) Xwk(i) Xwk(i+1) Xwk(i-1)];
        Y_tri = [Ywk(i-1) Ywk(i) Ywk(i+1) Ywk(i-1)];
        
        Xtest = [Xpt];
        Ytest = [Ypt];
        Xtest = [Xtest Xwk(1:i-2) Xwk(i+2:end)];
        Ytest = [Ytest Ywk(1:i-2) Ywk(i+2:end)];
        
        if sum(inpolygon(Xtest, Ytest, X_tri, Y_tri)) == 0
            % there are no points inside the triangle. We prune.
            this_idx = i;
            if (this_idx == length(X))
                X = [X(2:end) X(2)];
                Y = [Y(2:end) Y(2)];
            else
                X = [X(1:this_idx-1) X(this_idx+1:end)];
                Y = [Y(1:this_idx-1) Y(this_idx+1:end)];
            end
        else
            i = i+1;
        end
    end
end

Xout = X;
Yout = Y;
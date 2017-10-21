function [Xout, Yout] = dg_add_space_around_points(Xin, Yin, Xpt, Ypt, refine_thresh)

X = Xin;
Y = Yin;


N = length(Xpt);
if 1 == 1
    for i = 1:N
        d = p_poly_dist(Xpt(i), Ypt(i), X, Y);
        if abs(d) < refine_thresh
            % build square around point i
            Lh = refine_thresh;
            good = 0;
            
            while Lh > 0.001
                Xsq = [Xpt(i)-Lh, Xpt(i)-Lh Xpt(i)+Lh, Xpt(i)+Lh, Xpt(i)-Lh];
                Ysq = [Ypt(i)-Lh, Ypt(i)+Lh Ypt(i)+Lh, Ypt(i)-Lh, Ypt(i)-Lh];
                
                [Xm, Ym] = polybool('subtraction', Xsq, Ysq, X, Y);
                [Xn, Yn] = polybool('intersection', Xsq, Ysq, X, Y);

                if sum(inpolygon(Xpt, Ypt, Xsq, Ysq)) ~= 1
                    Lh = Lh * 0.75;
                elseif (sum(isnan(Xm)) > 0 || sum(isnan(Xn)) > 0)
                    Lh = Lh * 0.75;
                else
                    good = 1;
                    break;
                end
                break;
            end
            
            if good

                plot(Xsq, Ysq, 'k:');
                hold on;
                if d>0
                    [Xm, Ym] = polybool('subtraction', X, Y, Xsq, Ysq);
                else
                    [Xm, Ym] = polybool('union', X, Y, Xsq, Ysq);
                end
                X = Xm;
                Y = Ym;
            end
        end
    end
end

Xout = X;
Yout = Y;
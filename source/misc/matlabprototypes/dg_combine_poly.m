function [Xout, Yout] = dg_combine_poly(X, Y, Xh, Yh, type, X_blue, Y_blue, X_red, Y_red)
    plot_verbose = 0;
    Xpt = [X_blue X_red];
    Ypt = [Y_blue Y_red];
    Xe = [X X(2:end)];
    Ye = [Y Y(2:end)];
    Xhe = [Xh Xh(2:end)];
    Yhe = [Yh Yh(2:end)];
    N = length(X)-1;
    M = length(Xh)-1;
    
    min_angle_thresh = 0.01;

     if (plot_verbose)
         if (type == 0) % remove
             plot(Xh, Yh, 'r-');
             hold on;
         else % add
             plot(Xh, Yh, 'b-');
             hold on;
         end
     end

     L = length(Xh) - 1;
     [Xc, Yc] = dg_centroid(Xh, Yh);
     C = [Xc, Yc];
     ubd = dg_upperbounddiameter(X, Y);
     

     Xh
     Yh
     Xc
     
     if (plot_verbose)
         plot(Xc, Yc, 'k*');
         hold on;
     end
             
     num_div = 4;
     good = 0;
     
     while (~good)
        alpha_step = 2 * pi / num_div;
        alpha = 2 * pi .* [0:num_div-1]./num_div;
        Xp = Xc + ubd * cos(alpha);
        Yp = Yc + ubd * sin(alpha);
        
        % Find first intersection with X Y and with Xh Yh
        Xq = zeros(1, num_div);
        Yq = zeros(1, num_div);
        Xr = zeros(1, num_div);
        Yr = zeros(1, num_div);
        Iq = zeros(1, num_div);
        Jr = zeros(1, num_div);
        dist = zeros(1, num_div);
        for i=1:num_div
            [Q, I] = dg_first_intersection(C, [Xp(i), Yp(i)], C, X, Y);
            [R, J] = dg_first_intersection(C, [Xp(i), Yp(i)], C, Xh, Yh);
            Xq(i) = Q(1); Yq(i) = Q(2); Xr(i) = R(1); Yr(i) = R(2);
            Iq(i) = I; Jr(i) = J;
            dist(i) = pdist([Q; R], 'euclidean');
        end
        
        % Find minimum
        [sort_dist, sort_i] = sort(dist);
        
        for j=1:num_div
            i = sort_i(j);

            % Extending it
            Q_middle = [Xq(i) Yq(i)];
            R_middle = [Xr(i) Yr(i)];
            Q_ccw = Q_middle;
            R_ccw = R_middle;
            Q_cw = Q_middle;
            R_cw = R_middle;
            this_alpha = alpha(i);
            
            % extending ccw
            delta_alpha_ccw = alpha_step/2.;
            while (delta_alpha_ccw > min_angle_thresh)
                alpha_ccw = this_alpha + delta_alpha_ccw;
                P_ccw = C + ubd * [cos(alpha_ccw) sin(alpha_ccw)];
                [Q_ccw, I_ccw] = dg_first_intersection(C, P_ccw, C, X, Y);
                [R_ccw, J_ccw] = dg_first_intersection(C, P_ccw, C, Xh, Yh);
                Iqi = Iq(i); Jri = Jr(i);
                I_ccw_orig = I_ccw; J_ccw_orig = J_ccw;
                
                if (Iqi < I_ccw)
                    Iqi = Iqi + N;
                end
                if (Jri < J_ccw)
                    Jri = Jri + M;
                end
                
%                I_ccw
%                Iqi
%                J_ccw
%                Jri
%                plot(X(Iqi), Y(Iqi), 'go');
                

                X_poly_ccw = [R_middle(1) Xhe(Jri:-1:J_ccw+1) R_ccw(1) Q_ccw(1) Xe(I_ccw+1:Iqi) Q_middle(1) R_middle(1)];
                Y_poly_ccw = [R_middle(2) Yhe(Jri:-1:J_ccw+1) R_ccw(2) Q_ccw(2) Ye(I_ccw+1:Iqi) Q_middle(2) R_middle(2)];
                
                if (plot_verbose && type == 1)
                    plot(X_poly_ccw, Y_poly_ccw, 'k');
                end

                if (sum(inpolygon(Xpt, Ypt, X_poly_ccw, Y_poly_ccw)) == 0)
                    break;
                end

                delta_alpha_ccw = delta_alpha_ccw /2.;
            end
            
            if (plot_verbose)
                fill(X_poly_ccw, Y_poly_ccw, 'k');
            end
            
            

            % extending cw
            delta_alpha_cw = alpha_step/2.;
            while (delta_alpha_cw > min_angle_thresh)
                alpha_cw = this_alpha - delta_alpha_cw;
                P_cw = C + ubd * [cos(alpha_cw) sin(alpha_cw)];
                [Q_cw, I_cw] = dg_first_intersection(C, P_cw, C, X, Y);
                [R_cw, J_cw] = dg_first_intersection(C, P_cw, C, Xh, Yh);
                Iqi = Iq(i); Jri = Jr(i);
                I_cw_orig = I_cw; J_cw_orig = J_cw;
                
                if (I_cw < Iqi)
                    I_cw = I_cw + N;
                end
                if (J_cw < Jri)
                    J_cw = J_cw + M;
                end
                
                X_poly_cw = [R_middle(1) Q_middle(1) Xe(Iqi+1:I_cw) Q_cw(1) R_cw(1) Xhe(J_cw:-1:Jri+1) R_middle(1)];
                Y_poly_cw = [R_middle(2) Q_middle(2) Ye(Iqi+1:I_cw) Q_cw(2) R_cw(2) Yhe(J_cw:-1:Jri+1) R_middle(2)];
                
                if (plot_verbose && type == 1)
                    plot(X_poly_cw, Y_poly_cw, 'k');
                end

                if (sum(inpolygon(Xpt, Ypt, X_poly_cw, Y_poly_cw)) == 0)
                    break;
                end
                
                delta_alpha_cw = delta_alpha_cw /2.;

            end
            
            if (plot_verbose)
                fill(X_poly_cw, Y_poly_cw, 'k');
            end

            if (delta_alpha_ccw < min_angle_thresh && delta_alpha_cw < min_angle_thresh)
                continue;
            end
            
            
            good = 1;
            
            if (plot_verbose && type == 1)
                plot(X, Y, 'bs');
                plot(Xh, Yh, 'rs');
                
                h = patch(X, Y, 'b');
                set(h,'facealpha',.1)
                set(h,'edgealpha',.5)
                hold on;
                
                I_cw_orig
                I_ccw_orig
                
                plot(R_cw(1), R_cw(2), 'b*');
                plot(Q_cw(1), Q_cw(2), 'r*');
                plot(R_ccw(1), R_ccw(2), 'bo');
                plot(Q_ccw(1), Q_ccw(2), 'ro');
                
                plot(Xe(I_cw_orig), Ye(I_cw_orig), 'g*');
                plot(Xe(I_ccw_orig), Ye(I_ccw_orig), 'go');
                
                plot(Xhe(J_cw_orig), Yhe(J_cw_orig), 'g*');
                plot(Xhe(J_ccw_orig), Yhe(J_ccw_orig), 'go');
            end
            
           
            
            I_ccw = I_ccw_orig; J_ccw = J_ccw_orig;
            I_cw = I_cw_orig; J_cw = J_cw_orig;

            
            if (type == 0)
                if (I_ccw <= I_cw)
                    I_ccw = I_ccw + N;
                end
                if (J_ccw <= J_cw)
                    J_ccw = J_ccw + M;
                end
                
%                 Xh
%                 Yh
%                 J_ccw_orig
%                 J_cw_orig
%                 J_ccw
%                 J_cw
%                 I_ccw
%                 I_cw
                 X = [Q_cw(1) Xe(I_cw+1:I_ccw) Q_ccw(1) R_ccw(1) Xhe(J_ccw:-1:J_cw+1) R_cw(1) Q_cw(1)];
                 Y = [Q_cw(2) Ye(I_cw+1:I_ccw) Q_ccw(2) R_ccw(2) Yhe(J_ccw:-1:J_cw+1) R_cw(2) Q_cw(2)];
%                plot(X, Y, 'b*-', 'LineWidth', 2);
             else
                 % TO DO!!!
                 if (I_cw <= I_ccw)
                     I_cw = I_cw + N;
                 end
                 if (J_ccw <= J_cw)
                     J_ccw = J_ccw + M;
                 end
                 
                 J_cw
                 J_ccw
                
                 X = [Q_ccw(1) Xe(I_ccw+1:I_cw) Q_cw(1) R_cw(1) Xhe(J_cw+1:J_ccw) R_ccw(1) Q_ccw(1)];
                 Y = [Q_ccw(2) Ye(I_ccw+1:I_cw) Q_cw(2) R_cw(2) Yhe(J_cw+1:J_ccw) R_ccw(2) Q_ccw(2)];
%                plot(X, Y, 'k*-', 'LineWidth', 2);
             end


            

            break;
        end
        
        
        if (~good)
            num_div = num_div * 2;
            min_angle_thresh = min_angle_thresh / 2.;
        end
     end
     
    
%    if (plot_verbose)
%        if (type == 0)
%            plot(X, Y, 'b:','LineWidth',2);
%        else
%            plot(X, Y, 'k:','LineWidth',2);
%        end
%        hold on;
%    end
    
    Xout = X;
    Yout = Y;
    
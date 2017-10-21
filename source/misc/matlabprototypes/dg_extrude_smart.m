function [X_out, Y_out] = dg_extrude_smart(X_poly, Y_poly, start_amount, X_unwanted, Y_unwanted, type, X_set, Y_set)
N = length(X_poly);
amount_used = start_amount;

if (type == 1)
    X_poly
    Y_poly
    X_set
    Y_set
    [X_int0, Y_int0] = polybool('subtraction', X_poly, X_poly, X_set, Y_set);
elseif (type == 2)
    [X_int0, Y_int0] = polybool('intersection', X_poly, X_poly, X_set, Y_set);
else
    X_int0 = [];
    Y_int0 = [];
end

while amount_used > 0.000001
    
    X_out = X_poly;
    Y_out = Y_poly;
    
    [Xc, Yc] = dg_centroid(X_poly, Y_poly);
%    if (N >= 3)
%    GEOM = polygeom(X_poly', Y_poly');
%    Xc = GEOM(2);
%    Yc = GEOM(3);
%    else 
%    end
    
    C = [Xc Yc];
%    if (type == 1)
%        plot(Xc, Yc, 'rx', 'LineWidth',1);
%    else
%        plot(Xc, Yc, 'bx', 'LineWidth',1);
%    end
%    hold on;
    
    if N == 1
        I_before = zeros(1, length(X_unwanted));
    elseif N == 2
        I_before = zeros(1, length(X_unwanted)); %BUT THIS IS WRONG... IF COLLINEAR!!! = inline()
    else
        I_before = inpolygon(X_unwanted,Y_unwanted,X_poly,Y_poly);
    end
%    I_before
        
    %find expansion factor
    maxnorm = 0;
    if (N >= 2)
        for i = 1:N
            P = [X_poly(i) Y_poly(i)];
            thisnorm = norm(P - C);
            if thisnorm > maxnorm
                maxnorm = thisnorm;
            end
        end
        factor = (maxnorm + amount_used)/maxnorm;
    end
    
    % actually expand
    if N == 1
        % build square around single point
        X_out = [X_poly(1)-amount_used   X_poly(1)-amount_used  X_poly(1)+amount_used   X_poly(1)+amount_used  X_poly(1)-amount_used];
        Y_out = [Y_poly(1)-amount_used   Y_poly(1)+amount_used  Y_poly(1)+amount_used   Y_poly(1)-amount_used  Y_poly(1)-amount_used];
    elseif N == 2
        % extrude segment to rectangle
%        plot(C(1), C(2), 'k.', 'LineWidth',2);
        
        PT_A = C + ([X_poly(1) Y_poly(1)] - C).* factor;
        PT_B = C + ([X_poly(2) Y_poly(2)] - C).* factor;
        P = PT_B - PT_A;
        V = [-P(2) P(1)];
        V = V.*(amount_used/norm(V));
        
        X_out(1) = PT_A(1)-V(1);
        Y_out(1) = PT_A(2)-V(2);
        X_out(2) = PT_A(1)+V(1);
        Y_out(2) = PT_A(2)+V(2);
        X_out(3) = PT_B(1)+V(1);
        Y_out(3) = PT_B(2)+V(2);
        X_out(4) = PT_B(1)-V(1);
        Y_out(4) = PT_B(2)-V(2);
        X_out(5) = X_out(1);
        Y_out(5) = Y_out(1);

%        if (1 == 1)
 %           plot(X_out, Y_out, 'g:', 'LineWidth',2);
  %          hold on;
   %     end

    else
        for i = 1:N
            P = [X_poly(i) Y_poly(i)];
            %        Pextr = P - amount_used * (C - P)/norm(C - P);
            Pextr = C + (P - C)*factor;
            X_out(i) = Pextr(1);
            Y_out(i) = Pextr(2);
        end
    end


    

    
    I_after = inpolygon(X_unwanted,Y_unwanted,X_out,Y_out);
%    I_after
    
    if (type == 1)
        [X_int, Y_int] = polybool('subtraction', X_out, Y_out, X_set, Y_set);
    elseif (type == 2)
        [X_int, Y_int] = polybool('intersection', X_out, Y_out, X_set, Y_set);
    else 
        X_int = [];
    end
        
%    X_int
%    isempty(X_int0)
    
    if (isequal(I_before, I_after) && (isempty(X_int) || (~isempty(X_int0))))
        return;
    end
    
%    if (type == 1)
%        plot(X_out, Y_out, 'r:', 'LineWidth',1);
%    else
%        plot(X_out, Y_out, 'b:', 'LineWidth',1);
%    end
%    hold on;

    
%    amount_used = amount_used * 0.5;
    amount_used = amount_used * 0.8;
    
end



        

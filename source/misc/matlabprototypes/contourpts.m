function contourpts(N_blue, N_red)


%  X_blue = [7.0605    0.3183    2.7692    0.4617    0.9713    8.2346    6.9483    3.1710    9.5022    0.3445 4 3.8 4 7];
%  Y_blue = [4.3874    3.8156    7.6552    7.9520    1.8687    4.8976    4.4559    6.4631    7.0936    7.5469 4 4 3.7 0.5];
%  X_red = [ 4.1889    2.5545    2.5972    3.0300    5.3629    3.0171 7.7];
%  Y_red = [ 5.2571    2.9741    5.7171    3.3999    2.7864    3.0043 0.2];
%  
    X_blue = random('Uniform', 0, 10, 1, N_blue);
    Y_blue = random('Uniform', 0, 10, 1, N_blue);
    X_red = random('Uniform', 0, 10, 1, N_red);
    Y_red = random('Uniform', 0, 10, 1, N_red);
 

%%
plot_verbose = 1;
clf;
plot(X_blue, Y_blue, 'b.');
hold on;
plot(X_red, Y_red, 'r.');

extrude_amount = 2;
refine_thresh = 0.4;

% compute convex hull of blue stuff
[X, Y] = dg_convhull(X_blue, Y_blue);
[X, Y] = dg_extrude_smart(X, Y, extrude_amount, X_red, Y_red, 0, [], []);
%[X, Y] = dg_extrude_smart(X, Y, extrude_amount, [], [], 0, [], []);

if (plot_verbose)
    plot(X, Y, 'b:', 'LineWidth',1);
    hold on;
end


while 1
    
    %%%%%% STEP 1: DELETE RED ELEMENTS
    % compute how many red points are left inside the convex hull
    I = inpolygon(X_red,Y_red,X,Y);
    
    if sum(I) == 0
        break % no more red points in the polygon, we're done
    end
    
    X_remove = X_red(I == 1);
    Y_remove = Y_red(I == 1);

    % compute convex hull of red stuff
    [Xh, Yh] = dg_convhull(X_remove, Y_remove);
    [Xh, Yh] = dg_extrude_smart(Xh, Yh, extrude_amount, X_blue, Y_blue, 1, X, Y);
    
    % NOW WE NEED TO REMOVE Xh Yh from X Y
    [X, Y] = dg_combine_poly(X, Y, Xh, Yh, 0, X_blue, Y_blue, X_red, Y_red);
    
    if (plot_verbose)
        plot(X, Y, 'r:', 'LineWidth',1);
        hold on;
    end
    
    %%%%%% STEP 2: RE-INSERT BLUE ELEMENTS
    % compute how many blue points are left OUTSIDE the convex hull
    I = 1 - inpolygon(X_blue,Y_blue,X,Y);
    
    if sum(I) == 0
        break % no more blue points in the polygon, we're done
    end

    X_add = X_blue(I == 1);
    Y_add = Y_blue(I == 1);
    
    % compute convex hull of blue stuff
    [Xh, Yh] = dg_convhull(X_add, Y_add);
    [Xh, Yh] = dg_extrude_smart(Xh, Yh, extrude_amount, X_red, Y_red, 2, X, Y);

        
    [X, Y] = dg_combine_poly(X, Y, Xh, Yh, 1, X_blue, Y_blue, X_red, Y_red);

    if (plot_verbose)
        plot(X, Y, 'b:', 'LineWidth',1);
        hold on;
    end
    
end

Xpt = [X_blue X_red];
Ypt = [Y_blue Y_red];


[X, Y] = dg_remove_unneeded_vertices(X, Y, Xpt, Ypt);
[X, Y] = dg_add_space_around_points(X, Y, Xpt, Ypt, refine_thresh);

%plot(X, Y, 'b*-', 'LineWidth',2);
hold on;


%X
%Y
[X, Y] = dg_refine_contour_to_bezier(X, Y, X_blue, Y_blue, X_red, Y_red, 0.5, 0.5);

dg_plot_bezier_contour(X, Y);
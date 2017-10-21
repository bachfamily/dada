function [Pi, Ii] = dg_first_intersection(P1, P2, Center, Xpoly, Ypoly)

Xc = Center(1);
Yc = Center(2);

[thisx,thisy,thisidx] = POLYXPOLY([P1(1) P2(1)], [P1(2) P2(2)], Xpoly, Ypoly);

% among the thisx, we must choose the one NEAREST TO Xc Yc
if (isempty(thisx))
    Xi = NaN;
    Yi = NaN;
    Ii = 0;
else
    %we choose the
%    thisx
%    thisy
    P = [thisx' ; thisy']';
    mindist = -1;
    chosenidx  = 1;
    for j = 1:length(thisx)
        thisdist = pdist([Xc Yc; P(j,:)], 'euclidean');
        if (thisdist < mindist || mindist < 0)
            chosenidx = j;
            mindist = thisdist;
        end
    end
%    P
%    thisx
%    thisy
%    thisidx
%    chosenidx
    
    Xi = thisx(chosenidx);
    Yi = thisy(chosenidx);
    Ii = thisidx(chosenidx, 2);
end

Pi = [Xi, Yi];
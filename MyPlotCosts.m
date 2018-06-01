function MyPlotCosts(A)

    X=A(:,1);
    Y=A(:,2);
    
    plot(X,Y,'r*','MarkerSize',8);
    xlabel('1st Objective');
    ylabel('2nd Objective');
    %zlabel('3rd Objective');
    grid on;

end
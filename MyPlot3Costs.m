function MyPlot3Costs(A)

    X=A(:,1);
    Y=A(:,2);
    Z=A(:,3);
    
    plot3(X,Y, Z,'r*','MarkerSize',8);
    xlabel('1st Objective');
    ylabel('2nd Objective');
    zlabel('3rd Objective');
    grid on;

end
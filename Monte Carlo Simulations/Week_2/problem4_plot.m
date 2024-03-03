load problem4.csv
figure();
h = histogram(problem4,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(2.0,6.0,1000);
syms f(x)
f(x) = piecewise(2<x<3, (x-2)/2, 3<x<6, (2-(x/3))/2);

plot(X,f(X),'r');
legend('Histogram of simulated values','Probability density function')
hold off;
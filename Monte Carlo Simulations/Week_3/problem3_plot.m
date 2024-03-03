load problem3.csv;
figure();
h = histogram(problem3,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(0.0,1.0,1000);
f = @(x)(30*(x.*x-2*x.^3+x.^4));
plot(X,f(X),'r');
legend('Histogram of simulated values','theoretical distribution')
hold off;
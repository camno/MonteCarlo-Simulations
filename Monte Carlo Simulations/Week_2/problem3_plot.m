load problem3.csv;
figure();
h = histogram(problem3,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(0.001,5.0,1000);
f = @(x)(2.*x.*exp(-x.^2));
plot(X,f(X),'r');
legend('Histogram of simulated values','Weibull distribution')
hold off;
load problem2.csv;
figure();
h = histogram(problem2,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(0.0,10.0,1000);
f = @(x)(0.5*(1+x).*exp(-x));
plot(X,f(X),'r');
axis([0,11,0,0.55])
legend('Histogram of simulated values','theoretical distribution')
hold off;
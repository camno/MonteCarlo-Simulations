load problem2a.csv;
figure();
subplot(1,2,1)
h = histogram(problem2a,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(0.001,10.0,1000);
f = @(x)(exp(-x));
plot(X,f(X),'r');
legend('Histogram of simulated values','Exponential distribution with parameter 1')
title("50 strata, 10 samples per strata")
hold off;

load problem2b.csv
subplot(122)
h = histogram(problem2b,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(0.001,10.0,1000);
f = @(x)(exp(-x));
plot(X,f(X),'r');
legend('Histogram of simulated values','Exponential distribution with parameter 1')
title("100 strata, 5 samples per strata")
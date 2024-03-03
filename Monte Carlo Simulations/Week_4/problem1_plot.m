load problem1a.csv;
load problem1b.csv
figure();
subplot(211);
h = histogram(problem1a,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(-4.0,4.0,1000);
norm = normpdf(X,0,1);
plot(X,norm,'r');
legend('Histogram of Box-Muller values','theoretical distribution')
hold off;
title("Box-Muller method")

subplot(212)
h = histogram(problem1b,'Normalization','pdf');%plot histogram, with normalization to pdf
hold on;
X=linspace(-4.0,4.0,1000);
norm = normpdf(X,0,1);
plot(X,norm,'r');
legend('Histogram of approximate values','theoretical distribution')
hold off;
title("Approximate method")
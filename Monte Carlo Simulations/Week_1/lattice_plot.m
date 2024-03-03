load points_b.csv
ui=points_b(1:10);
uj=points_b(2:11);
subplot(1,2,1);
plot(ui,uj,'r.');
xlabel('u_i');
ylabel('u_{i+1}');

load points.csv
ui=points(1:1000000);
uj=points(2:1000001);
subplot(1,2,2);
plot(ui,uj,'r.');
xlim([0 0.001])
xlabel('u_i');
ylabel('u_{i+1}');

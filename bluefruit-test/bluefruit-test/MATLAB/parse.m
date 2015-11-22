close all; clear; clc
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse in a 3 column hex file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Format: 'xxxxxxxx xxxxxxxx xxxxxxxx\r\n' (28)

fid = fopen('data.txt', 'r');

[data, count] = fscanf(fid,'%c');

N = 28;
for i=1:(count/N)
   X(i,:) = data((N*(i-1))+1+00:(N*i)-20);
   Y(i,:) = data((N*(i-1))+1+09:(N*i)-11);
   Z(i,:) = data((N*(i-1))+1+18:(N*i)-02);
end

x = hexsingle2num(X);
y = hexsingle2num(Y);
z = hexsingle2num(Z);

figure(1)
subplot(311)
plot(1:length(x),x);
title('iPhone Accelerometer Data, X');
xlabel('time'); ylabel('amplitude');
% ylim([-7 7]);

subplot(312)
plot(1:length(y),y);
% plot thresholds
hold on
plot(1:length(y),repmat(.1,1,length(y)), 'k:');
plot(1:length(y),repmat(.3,1,length(y)), 'r:');
plot(1:length(y),repmat(.55,1,length(y)),'g:');
plot(1:length(y),repmat(.8,1,length(y)), 'b:');
title('iPhone Accelerometer Data, Y');
xlabel('time'); ylabel('amplitude');
% ylim([-7 7]);

subplot(313)
plot(1:length(z),z);
title('iPhone Accelerometer Data, Z');
xlabel('time'); ylabel('amplitude');
% ylim([-7 7]);

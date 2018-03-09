Fs = 44000;
f = 20000;
Ts = 0.001;
n = Fs*Ts;
y = [];

file = fopen('test.txt', 'r');
data = fgetl(file);
while ~feof(file)
    data = strcat(data, fgetl(file));
end
fclose(file);

[~,sizeN] = size(data);
info = [];

for k=1:sizeN
    m = data(k);
    newi = dec2bin(m, 8);
    info = [info newi];
end

[~,infoSize] = size(info);
dlmwrite('input.txt', info, ' ');
for i = 1:2:infoSize
    tmpim = getImpulse(Ts, f, n);
    z = [];
    if i == infoSize
        if info(i) == '0'
            z = zeros(1,400);
        elseif info(i) == '1'
            z = zeros(1,1200);
        end
    elseif info(i) == '0' && info(i+1) == '0'
        z = zeros(1,400);
    elseif info(i) == '0' && info(i+1) == '1'
        z = zeros(1,800);
    elseif info(i) == '1' && info(i+1) == '0'
        z = zeros(1,1200);
    elseif info(i) == '1' && info(i+1) == '1'
        z = zeros(1,1600);
    end
    y = [y tmpim];
    y = [y z];
end
figure(1);
plot(y);
audiowrite('test.wav', y, Fs);

function y = getImpulse(Ts, f, n)
y = sin(2*pi*f*Ts*linspace(0,1,n+1));
end

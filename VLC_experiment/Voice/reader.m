[data, fs] = audioread('Test5.m4a');
data = data(:,1);
figure(1);
plot(data);
%data = fir_hpf(data, 44000, 40, 25000, 20000);
data = highp(data, 21000, 18000, 0.1, 30, 44000);
figure(2);
plot(data);
f = 23000;

tap = 0.4;
tap2 = 0.5*(10^(-4));
tap3 = 0.5*(10^(-4));
tap4 = 0.3*(10^(-4));
tap5 = 2.6*(10^(-5));
[n,~] = size(data);
[pks, state] = findpeaks(data, 'minpeakheight', tap5);
state = better(state);
info = [];
for i = 1:(length(state) - 1)
    info(i) = state(i+1) - state(i);
end
result = [];
result = decode(info);
charResult = [];
dlmwrite('result.txt', result);
input = textread('input.txt');
if length(result) < length(input)
    input(length(result) + 1:length(input)) = [];
elseif length(result) > length(input)
    result(length(input) + 1:length(result)) = [];
end
[num, ratio] = biterr(result, input);
charResult = read(result);
fid = fopen('result.txt', 'w');
fprintf(fid, '%s\n', charResult);
fclose(fid);
    

function y = highp(x, f1, f3, rp, rs, Fs)
wp = 2*pi*f1/Fs;
ws = 2*pi*f3/Fs;

[n,wn]=cheb1ord(wp/pi,ws/pi,rp,rs);
[bz1,az1]=cheby1(n,rp,wp/pi,'high');
[h,w]=freqz(bz1,az1,256,Fs);
y=filter(bz1,az1,x);
end
    

%{
function [y] = fir_hpf(x, Fs, As, fp, fs)
b = fp - fs;
M0 = round((As - 7.95)/(14.36*6/Fs))+2;
M = M0 + mod(M0 + 1,2);
wp = 2*fp/(Fs*pi);
ws = 2*fs/(Fs*pi);
wc = (wp + ws)/2;
if As > 50
    beta = 0.1102*(As - 8.7);
    elseif As >= 21&&As<=50
        beta = 0.5842*(As-21)^0.4+0.07886*(As-21);
    else
        beta = 0;
end

N = M - 1;
hd = fir1(N, wc, 'high', kaiser(M, beta));
x = x - mean(x);
y = filter(hd, 1, x);
end
%}

function [result] = decode(info)
p = length(info);
presentState = 1;
for i = 1:p
    flag = check(info(i), 400);
    if flag == 1
        result(presentState) = 0;
        result(presentState + 1) = 0;
        presentState = presentState + 2;
        continue;
    end
    flag = check(info(i), 800);
    if flag == 1
        result(presentState) = 0;
        result(presentState + 1) = 1;
        presentState = presentState + 2;
        continue;
    end
    flag = check(info(i), 1200);
    if flag == 1
        result(presentState) = 1;
        result(presentState + 1) = 0;
        presentState = presentState + 2;
        continue;
    end
    flag = check(info(i), 1600);
    if flag == 1
        result(presentState) = 1;
        result(presentState + 1) = 1;
        presentState = presentState + 2;
        continue;
    end
    %{
    if flag ~= 1
        result(presentState) = 1;
        result(presentState + 1) = 1;
        presentState = presentState + 2;
        continue;
    end
    %}
end
end
    

function flag = check(num, x)
if(x>=(num - 200) && x<=(num + 200))
    flag = 1;
else
    flag = -1;
end
end


function [state] = better(result)
flag = result(1);
i = 2;
while(true)
    if result(i) <= (flag + 300)
        result(i) = []
    else
        flag = result(i);
        i = i + 1;
    end
    if i > length(result)
        break;
    end
end
state = result;
end

function [y] = read(result)
num = 1;
i = 1;
while(1)
    if(i+7 > length(result))
        m = i + 7 - length(result);
        n = 8 - m;
        result(i+n:i+7) = zeros(1, m);
    end
    tem = bin2dec(num2str(result(1,i:i+7)));
    y(num)  = char(tem);
    num = num + 1;
    i = i + 8;
    if i >= length(result)
        break;
    end
end
end
    
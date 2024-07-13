%{ 
[y,fs]=audioread('sample.wav'); 
ft = y(:,1);   
sigLength = length(ft); %length
 t=(0:sigLength-1)/fs;   
figure;  
plot(t(1:200), ft(1:200)),grid;  
xlabel('Time(s)');  
ylabel('Amplitude');
title('Sinal Origal - sample.wav')
%}

figure(1)
subplot(3,1,1);
[x,fs]=audioread('sample.wav');
info = audioinfo( 'sample.wav');
N=length(x);
T=2.9520;
t=linspace(0,T,N);
plot(t,x);
xlabel('Sample time(s)')
ylabel('x(t)')
title('Original sound signal')
y=abs(fftshift(fft(x)));
F=linspace(-fs/2,fs/2,N);
subplot(3,1,2);
plot(F,y);

%------------------------------------
figure(2)
subplot(3,1,1);
[x1,fs1]=audioread('wav_quant_out.wav');
info1 = audioinfo( 'wav_quant_out.wav');
N1=length(x1);
T1=2.9520;
t1=linspace(0,T1,N1);
plot(t1,x1);
xlabel('Sample time(s)')
ylabel('x(t)')
title('Quantization Signal')
y1=abs(fftshift(fft(x1)));
F1=linspace(-fs1/2,fs1/2,N1);
subplot(3,1,2);
plot(F1,y1);

%{
xlabel('frequency')
ylabel('x(f)')
Xmax=max(x);
Xmin=min(x);
xd = Xmax - Xmin ;
L=4;
Delta =(xd/L);
q=(Xmin-Delta/2):Delta:(Xmax+Delta/2);
q=q(2:end-1);
DTV=zeros(1,L-1);
for i=1:(L-1)
    DTV(i)=(q(i+1)+q(i))/2;
end
[i,Xq]=quantiz(x,DTV,q);
subplot(3,1,3);
plot(t,Xq);
%}
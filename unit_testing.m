clc;
clear all;
close all;

data = randi([1, 1], 1, 1);
data = nrCRCEncode(data, '11');
data = [1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]';
encData = nrPolarEncode(data, 94, 9, false);
encData2 = nrRateMatchPolar(encData, 72, 94, false);
xx = [0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
xx = xx';
xx2 = [0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,0,1,0,1];
xx2 = xx2';

sum(bitxor(encData, xx))
sum(bitxor(encData2, xx2))

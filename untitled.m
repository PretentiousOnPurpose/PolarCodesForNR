data = [0,1,0,1,1,0,1,1,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,1,1,0,1,0,0,0,1]';
crcData = nrCRCEncode(data, '11');
enc_data = nrPolarEncode(crcData, 144, 10, false);
% modIn = nrRateMatchPolar(enc_data, 72, 144, false);

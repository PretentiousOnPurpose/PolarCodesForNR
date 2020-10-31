% enc_data = [10, 10, 0, 0, 0, 10, 10, 10]';
% 
% LLR = zeros(8, 3);
% 
% for iter_step = 3:-1:2
%     for iter_group = 0: 2^(3 - iter_step)-1
%         for iter_bits = 0: 2^(iter_step-1)-1
%             
%             a1 = enc_data(iter_bits + iter_group * 2^iter_step + 1);
%             a2 = enc_data(iter_bits + iter_group * 2^iter_step + 1 + 2^(iter_step-1));
%             
%             LLR(iter_bits + 1, iter_step) = (1 + a1 * a2)/(a1 + a2);  
%         end
%     end
%     enc_data = LLR(:, iter_step);
% end

x = [1;1;1;1;0;0;0;0];
y = qammod(x, 2, 'InputType', 'bit', 'UnitAveragePower', 1);
z = qamdemod(y, 2, 'OutputType', 'approxllr', 'UnitAveragePower', 1);
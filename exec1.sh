gcc ./mainSystem.c ./nr_crc_encoder.c ./nr_crc_decoder.c ./nr_pc_encoder.c ./nr_pc_decoder.c ./nr_interleaver.c ./nr_rate_match.c ./pc_utils.c -lm -O2 -mavx2
# ./a.out
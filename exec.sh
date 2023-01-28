clear
gcc -o ./build/pc_system.exe ./mainSystem.c ./src/nr_crc_encoder.c ./src/nr_crc_decoder.c ./src/nr_pc_encoder.c ./src/nr_pc_decoder.c ./src/nr_interleaver.c ./src/nr_rate_match.c ./src/pc_utils.c -lm -g 
./build/pc_system.exe


# clear
# gcc -o ./build/pc_block_system.exe ./block_enc_system.c ./src/nr_crc_encoder.c ./src/nr_crc_decoder.c ./src/nr_pc_encoder.c ./src/nr_pc_decoder.c ./src/nr_interleaver.c ./src/nr_rate_match.c ./src/pc_utils.c -lm -g 
# ./build/pc_block_system.exe
#ifndef PRINTFUNCTIONS_H
#define PRINTFUNCTIONS_H

void print_state(uint32_t A, uint32_t B, uint32_t C, uint32_t D, int step);
void print_bin_char( char c);
void print_bin_str(char * str);
void print_bits(uint32_t *array, size_t length);
void print_md5(uint8_t *md5);

#endif
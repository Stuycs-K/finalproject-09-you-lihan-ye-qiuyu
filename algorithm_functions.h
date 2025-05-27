#ifndef ALGORITHMFUNCTIONS_H
#define ALGORITHMFUNCTIONS_H

uint32_t * pad(char * input, int *padded_len);
uint32_t F(uint32_t b, uint32_t c, uint32_t d, int i);
uint32_t rotate(uint32_t x, uint32_t n);
int containsSpecialCharacter(const char *str);

#endif
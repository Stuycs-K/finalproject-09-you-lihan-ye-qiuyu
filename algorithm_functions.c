#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h> 


int containsSpecialCharacter(const char *str) {
    while (*str) {
        if (!isalnum((unsigned char)*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}

uint32_t * pad(char * input, int *padded_len){
    size_t len = strlen(input);
    uint64_t bit_len = (uint64_t)len * 8;

    // +1 for 0x80, then pad until length ≡ 56 mod 64
    size_t new_len = len + 1;
    while ((new_len % 64) != 56) {
        new_len++;
    }
    new_len += 8; // space for 64-bit length

    uint8_t *padded_bytes = calloc(new_len, 1);
    if (!padded_bytes) return NULL;

    // copy original message and add 0x80 byte
    memcpy(padded_bytes, input, len);
    padded_bytes[len] = 0x80;

    // append original length in bits (little-endian)
    for (int i = 0; i < 8; i++) {
        padded_bytes[new_len - 8 + i] = (uint8_t)(bit_len >> (8 * i));
    }

    *padded_len = new_len / 64; // 32-bit word count

    // print_bits((uint32_t *)padded_bytes, 16);
    // printf("\n");
    return (uint32_t *)padded_bytes;
}

uint32_t F(uint32_t b, uint32_t c, uint32_t d, int i){
    if (i < 16){
        return (b & c) | ((~b) & d);
    }
    else if 
    (i < 32) {
        return (d & b) | ((~d) & c);
    }
    else if (i < 48) {
        return b ^ c ^ d;
    }
    else {
        return c ^ (b | (~d));
    }
}

uint32_t rotate(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}
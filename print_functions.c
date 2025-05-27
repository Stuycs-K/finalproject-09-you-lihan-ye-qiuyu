#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void print_state(uint32_t A, uint32_t B, uint32_t C, uint32_t D, int step) {
    printf("Step %2d: A=%08x B=%08x C=%08x D=%08x\n", step, A, B, C, D);
}

//prints char in binary
void print_bin_char(char c){
    for(int i = 7; i >= 0; i--) {
        printf( "%d", ( c >> i ) & 1 ? 1 : 0 );
    }
}

//prints str in binary using print_bin_char
void print_bin_str(char * str){
    // for (int i = 0; i < strlen(str); i++){
    for (int i = 0; str[i] != '\0'; i++){
        print_bin_char(str[i]);
        //ternary op. basically if else
        (i == strlen(str) - 1) ? printf("") : printf(" ");
    }
}

void print_bits(uint32_t *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        for (int j = 31; j >= 0; j--) {
        printf("%d", (array[i] >> j) & 1);
        if (j % 8 == 0 && j != 0) {
            printf(" ");
        }
        }
        printf(" ");
    }
}

void print_md5(uint8_t *md5) {
    for (int i = 0; i < 16; i++) printf("%02x", md5[i]);
    printf("\n");
}

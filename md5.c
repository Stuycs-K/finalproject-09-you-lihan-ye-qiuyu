#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h> 
#include "print_functions.h"
#include "algorithm_functions.h"

int main(int argc, char *argv[]){
    char* str;
    int start = 0;
    if (argc < 2) {
        printf("You need to input a string to encode!\n");
        exit(1);
    } else {
        if (containsSpecialCharacter(argv[1])) {
            printf("Your string can only contain alphanumeric characters (a-z A-Z 0-9)\n");
            exit(1);
        } else { 
            start = 1;
            str = argv[1];
        }
    }

    if (start) {
        // constants are the integer part of the sines of integers (in radians) * 2^32.
        const uint32_t K[64] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
        };

        // r specifies the per-round shift amounts
        const uint32_t r[] = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
            5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
        };

        int blocks = 1;
        uint32_t * padded = pad(str, &blocks);
        //printf("num blocks: %d\n", blocks);
        uint32_t a1 = 0x67452301;
        uint32_t b1 = 0xEFCDAB89;
        uint32_t c1 = 0x98BADCFE;
        uint32_t d1 = 0x10325476;
        for (int j = 0; j < blocks; j++){
            uint32_t a = a1;
            uint32_t b = b1;
            uint32_t c = c1;
            uint32_t d = d1;

            uint32_t M[16];
            for (int m = 0; m < 16; m++) {
                int byte_index = j * 64 + m * 4;
                M[m] = ((uint8_t*)padded)[byte_index] |
                ((uint8_t*)padded)[byte_index + 1] << 8 |
                ((uint8_t*)padded)[byte_index + 2] << 16 |
                ((uint8_t*)padded)[byte_index + 3] << 24;
            }
            int i = 0;
            while(i < 64){
                //print_state(a, b, c, d, i);
                int k = find_index_original(i);

                uint32_t temp = b + rotate((a + F(b, c, d, i) + K[i] + M[k]), r[i]);
                //printf("%d\n", k + j * 64);
                // printf("%08x\n", b + F(b, c, d, i) + K[i] + padded[k]);
                a = d;
                d = c;
                c = b;
                b = temp;

                i++;
            }
            // print_state(a, b, c, d, 63);
            a1 += a;
            b1 += b;
            c1 += c;
            d1 += d;
        }
        // print_state(a, b, c, d, 100);
        uint8_t md5_hash[16];

        md5_hash[0] = (a1 >> 0) & 0xFF;
        md5_hash[1] = (a1 >> 8) & 0xFF;
        md5_hash[2] = (a1 >> 16) & 0xFF;
        md5_hash[3] = (a1 >> 24) & 0xFF;

        md5_hash[4] = (b1 >> 0) & 0xFF;
        md5_hash[5] = (b1 >> 8) & 0xFF;
        md5_hash[6] = (b1 >> 16) & 0xFF;
        md5_hash[7] = (b1 >> 24) & 0xFF;

        md5_hash[8] = (c1 >> 0) & 0xFF;
        md5_hash[9] = (c1 >> 8) & 0xFF;
        md5_hash[10] = (c1 >> 16) & 0xFF;
        md5_hash[11] = (c1 >> 24) & 0xFF;

        md5_hash[12] = (d1 >> 0) & 0xFF;
        md5_hash[13] = (d1 >> 8) & 0xFF;
        md5_hash[14] = (d1 >> 16) & 0xFF;
        md5_hash[15] = (d1 >> 24) & 0xFF;

        print_md5(md5_hash);

        free(padded);
    }
}

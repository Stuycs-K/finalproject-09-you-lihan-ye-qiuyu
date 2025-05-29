#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "print_functions.h"
#include "algorithm_functions.h"

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
  } else if (i < 32) {
    return (d & b) | ((~d) & c);
  } else if (i < 48) {
    return b ^ c ^ d;
  } else {
    return c ^ (b | (~d));
  }
}

int find_index_original(int i) {
  if (i < 16) {
    return i;
  } else if (i < 32) {
    return (5 * i + 1) % 16;
  } else if (i < 48) {
    return(3 * i + 5) % 16;
  } else {
    return (7 * i) % 16;
  }
}

uint32_t rotate(uint32_t x, uint32_t n) {
  return (x << n) | (x >> (32 - n));
}


uint8_t * hash(char * str){
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
  uint8_t *md5_hash = malloc(16 * sizeof(uint8_t));

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

  // printf("Your hash is : ");
  // print_md5(md5_hash);
  free(padded);
  return md5_hash;
}

int main(int argc, char *argv[]){
  char* passwdList = "";
  char* crack = "";
  if (argc == 1){
    printf("please enter a hash or a hash and a password list\n");
  }
  else if (argc == 2) {
    printf("using rockyou.txt\n");
    passwdList = "rockyou.txt";
    crack = argv[1];
  }
  else{
    crack = argv[1];
    passwdList = argv[2];

  }
  pid_t p = fork();
  if (p == 0){
    const char *base = "starting";
    int i = 0;
    while (1) {
      printf("\r%s", base);
      for (int j = 0; j < i; j++) {
        printf(".");
      }
      printf("   ");
      fflush(stdout);
      usleep(500000);
      i = (i + 1) % 4;
    }
  }
  else{

    FILE* file = fopen(passwdList, "r");
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        count++;
      }
    }
    rewind(file);

    kill(p, SIGTERM);
    printf("\n");
    int c = 0;
    for (int i = 0; i < count; i++){
      if (!(i % (count/100)) && (i != 0)){
        c++;
        // printf("%d%% done\n", c);
        // printf("%d passwords tested\n", i);
        printf("\rprogress: %3d%%", c);
        fflush(stdout);
      }
      char line[128];
      fgets(line, sizeof(line), file);
      line[strcspn(line, "\n")] = '\0';

      // char* str = strcpy(line);
      uint8_t* md5 = hash(line);
      char buffer[129];
      buffer[0] = 'a';
      for (int i = 0; i < 16; i++){
        sprintf(&buffer[i*2], "%02x", md5[i]);
        // printf("%02x", md5[i]);
        // printf("%s\n", buffer);
      }
      buffer[128] = '\0';
      // printf("\n");
      // printf("%s\n", buffer);
      if (!strcmp(buffer, crack)){
        printf("\n");
        printf("password found!\n");
        printf("hash: %s\n", buffer);
        printf("passwd: %s\n", line);
        printf("number of passwords checked: %d\n", i);
        exit(0);
      }
    }
    printf("\n");
    printf("no password found\n");
  }
}
// }

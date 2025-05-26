#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void print_state(uint32_t A, uint32_t B, uint32_t C, uint32_t D, int step) {
  printf("Step %2d: A=%08x B=%08x C=%08x D=%08x\n",
    step, A, B, C, D);
  }

  //prints char in binary
  void print_bin_char( char c){
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

  uint32_t * pad(char * input){
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

    // *padded_len = new_len / 4; // 32-bit word count

    // print_bits((uint32_t *)padded_bytes, 16);
    // printf("\n");
    return (uint32_t *)padded_bytes;
  }

  uint32_t F(uint32_t b, uint32_t c, uint32_t d, int i){
    if (i < 16){
      return (b & c) | ((~b) & d);
    }
    else if (i < 32) {
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

  void print_md5(uint8_t *md5) {
    for (int i = 0; i < 16; i++) printf("%02x", md5[i]);
    printf("\n");
  }


  int main(){
    
  }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
        // Print each bit from MSB to LSB
        for (int j = 31; j >= 0; j--) {
            printf("%d", (array[i] >> j) & 1);
            // Add space every 8 bits
            if (j % 8 == 0 && j != 0) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

uint32_t * pad(char * str){
  // unsigned char c = 'a';
  // print_bin_char(c);
  // printf("\n");
  // char * str = "md5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_test";
  print_bin_str(str);
  printf("\n");
  //if password has null character, wont work correctly
  uint64_t bits = strlen(str) * 8;
  printf("%d\n", bits);
  int temp = ((448 - (bits % 512)) + 512) % 512;
  printf("%d\n", temp);
  // int size = (bits - (bits % 512) + 512)/32;
  int size = bits + temp + 64;
  uint32_t *output = (uint32_t *)malloc(bits + temp + 64);
  printf("%d\n", bits + temp + 64);
  for (int i = 0; i < bits/32; i++){
    output[i] = str[i] << 24 | str[i + 1] << 16 | str[i + 2] << 8 | str[i + 3];
  }
  if (bits % 32){
    printf("%d\n", bits % 32);
    output[bits/32] = 0b0;
  }
  int n = 0;
  for (int i = 0; i < (bits % 32)/8; i++){
    output[bits/32] = output[bits/32] | str[bits/32 + i] << (24 - i * 8);
    n = i + 1;
  }
  output[bits/32] = output[bits/32] | 1 << (7 + (24 - 8 * n));
  for (int i = bits/32 + 1; i < (size / 32 - 2); i++) {
    // printf("%d\n", i);
    output[i] = 0b0;
  }
  printf("%d\n", bits);
  output[size/32 - 2] = bits >> 32;
  output[size/32 - 1] = (uint32_t)bits;
  print_bits(output, size/32);
  return output;
}
int main(){
  // unsigned char c = 'a';
  // print_bin_char(c);
  // printf("\n");
  char * str = "md5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_testm";
  uint32_t a = 0x67452301;
  uint32_t b = 0xEFCDAB89;
  uint32_t c = 0x98BADCFE;
  uint32_t d = 0x10325476;

  uint32_t tempC = b;
  uint32_t tempD = c;
  uint32_t tempA = d;


  pad(str);


}

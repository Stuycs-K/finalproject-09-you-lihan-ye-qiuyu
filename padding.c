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

int main(){
  unsigned char c = 'a';
  // print_bin_char(c);
  // printf("\n");
  char * str = "md5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_testmd5_testm";
  print_bin_str(str);
  printf("\n");
  //if password has null character, wont work correctly
  int bits = strlen(str) * 8;
  printf("%d\n", bits);
  int temp = ((448 - (bits % 512)) + 512) % 512;
  printf("%d\n", temp);
  // int size = (bits - (bits % 512) + 512)/32;
  int size = bits + temp + 64;
  uint32_t *output = (uint32_t *)malloc(bits + temp + 64);
  printf("%d\n", bits + temp + 64);
  for (int i = 0; i < size / 8; i++) {
    // printf("%d\n", i);
    output[i] = 0b0;
  }
  print_bits(output, size/32);

}

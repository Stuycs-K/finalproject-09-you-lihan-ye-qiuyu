#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//prints char in binary
void print_bin_char(unsigned char c){
  for(int i = 7; i >= 0; i--) {
      printf( "%d", ( c >> i ) & 1 ? 1 : 0 );
  }
}

//prints str in binary using print_bin_char
void print_bin_str(unsigned char * str){
  // for (int i = 0; i < strlen(str); i++){
  for (int i = 0; str[i] != '\0'; i++){
    print_bin_char(str[i]);
    //ternary basically if else
    (i == strlen(str) - 1) ? printf("") : printf(" ");
  }
}

int main(){
  unsigned char c = 'a';
  // print_bin_char(c);
  // printf("\n");
  char * str = "md5_test";
  print_bin_str(str);
  printf("\n");
  //if password has null character, wont work correctly
  uint32_t bits = strlen(str) * 8;
  uint32_t pad = bits % 512 - 1;
  size_t len = ((strlen(str) + pad + 1) + 8);
  
  uint32_t *output = (uint32_t *)malloc(size * 32);
  for (int i = 0; i < size; i++) {
    output[i] = 0b0;
  }

}

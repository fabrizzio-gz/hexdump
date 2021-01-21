#include <stdio.h>

/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  unsigned char c;
  int count = 0, limit = 0;
  
  if (argc != 2) {
    printf("Usage: hexdump <file>\n");
    return 1;
  }

  fp = fopen(argv[1], "r");

  int i = 0;
  while ((c = getc(fp)) != EOF && i++ < 40) {
    if (count % 16 == 0) 
      printf("\n%08x  ", count);
    printf("%02x ", c);
    count++;
  }

  fclose(fp);
  printf("\n");
  return 0;
}

#include <stdio.h>

void print_line_chars(char *chars);
int is_printable(unsigned char c);

/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  unsigned char c;
  char chars[17];
  chars[17] = '\0';
  int count = 0, limit = 0;
  
  if (argc != 2) {
    printf("Usage: hexdump <file>\n");
    return 1;
  }

  fp = fopen(argv[1], "r");

  int i = 0;
  while ((c = getc(fp)) != EOF && i++ < 40) {
    if (count % 16 == 0) {
      if (count != 0) print_line_chars(chars);
      printf("%08x  ", count);
    }
    
    printf("%02x ", c);
    chars[count % 16] = is_printable(c) ? c : '.';
    count++;
  }

  fclose(fp);
  printf("\n");
  return 0;
}


void print_line_chars(char *chars) {
  
  printf(" ");
  printf("|%s|\n", chars);
}


int is_printable(unsigned char c) {
  /* Check if c is between printable ASCII chars */
  return c >= 32 && c <= 126;
}

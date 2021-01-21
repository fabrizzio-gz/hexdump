#include <stdio.h>
#include <stdlib.h>

void print_line_chars(char *chars);
int is_printable(unsigned char c);

/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  unsigned char c;
  char chars[17];  // 16 chars each line + '\0'
  int count = 0, is_limited = 0, limit;
  
  if (argc < 2 || argc > 3) {
    printf("Usage: hexdump <file> [<count>]\n");
    return 1;
  }

  if (argc == 3) {
    is_limited = 1;
    limit = atoi(argv[2]);
    if (limit == 0) {
      printf("Invalid byte-count: %s\n", argv[2]);
      return 2;
    }
  }

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Invalid file or path: %s\n", argv[1]);
    return 3;
  }

  int apply_limit = !is_limited;
  while ((c = getc(fp)) != EOF && (apply_limit || count < limit)) {
    if (count % 16 == 0) {
      if (count != 0) print_line_chars(chars);
      printf("%08x  ", count);
    }
    
    printf("%02x ", c);
    chars[count % 16] = is_printable(c) ? c : '.';
    chars[count % 16 + 1] = '\0';
    count++;
  }

  
  /* Finish current line */
  int old_count = count;
  while (count++ % 16) {
    printf("   ");
    if (count % 16 == 0) {
      print_line_chars(chars);
      printf("%08x  ", old_count);
    }
      
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

#include <stdio.h>
#include <stdlib.h>


void print_line_chars(char *chars);
int is_printable(char c);


/* Prints the hex characters of a file */
int main(int argc, char *argv[]) {
  FILE *fp;
  int read_char;
  char c;
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

  /* `char_read` is set to int as a workaround when read char is 255 (0xff).
   * In contrast, -1 = 0xffffffff but a char type can't tell the difference.
   * apply_limit is used as a short-circuit. If it is set to 1, 
   * count < limit won't be evaluated.
   * */
  int apply_limit = !is_limited;
  while ((read_char = getc(fp)) != EOF && (apply_limit || count < limit)) {
    c = read_char;
    if (count % 16 == 0) {
      if (count != 0) print_line_chars(chars);
      printf("%08x  ", count);
    }
    /* c is casted to unsigned char to avoid issue with negative values 
     * conditional string that follows is used to add an extra space every byte
     */
    printf("%02x %s", (unsigned char) c, count % 8 == 7 ?  " " : ""); // Add extra space every byte
    chars[count % 16] = is_printable(c) ? c : '.';
    chars[count % 16 + 1] = '\0';
    count++;
  }

  
  /* Finish current line */
  int old_count = count;
  while (count++ % 16) 
    printf("   %s", count % 8 == 7 ?  " " : ""); // Adds one extra space every byte
      
  if (1) {
    print_line_chars(chars);
    printf("%08x  ", old_count);
  }

  printf("\n");
  fclose(fp);
  
  return 0;
}


void print_line_chars(char *chars) {
  printf("|%s|\n", chars);
}


int is_printable(char c) {
  /* Check if c is between printable ASCII chars */
  return c >= 32 && c <= 126;
}


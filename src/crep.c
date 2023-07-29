#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv);
int crep(char* re, char* filename);
bool match_re(char* re, char* s);
bool match_star(char* re, char* s, char c);
bool match_char(char* re, char* s);
bool is_empty(char* re);
bool is_star(char* re);
bool is_eol_anchor(char* re);
void trim_trailing_newline(char* s);

#define DIE(...) \
  do { \
    fprintf(stderr, __VA_ARGS__); \
    exit(EXIT_FAILURE); \
  } while (0)

//-----------------------

int main(int argc, char** argv) {
  if (argc != 3) DIE("usage: crep <pattern> <file>");
  return crep(argv[1], argv[2]);  
}

int crep(char* re, char* filename) {
  static const size_t MAX_LINE_LENGTH = 1024;
  FILE* f = fopen(filename, "r");
  if (!f) DIE("Error: Cannot open file '%s'\n", filename);
  char line[MAX_LINE_LENGTH];
  int matches = 0;
  while (fgets(line, sizeof(line), f)) {
    trim_trailing_newline(line);
    if (match_re(re, line)) {
      printf("%s\n", line);
      matches++;
    }
  }
  fclose(f);
  return !matches;
}

bool match_re(char* re, char* s) {
  if (is_empty(re)) return true;
  if (is_star(re)) return match_star(re + 2, s, re[0]);
  if (is_eol_anchor(re)) return is_empty(s);
  if (match_char(re, s)) return match_re(re + 1, s + 1);
  return false;
}

bool match_star(char* re, char* s, char c) {
  do {
    if (match_re(re, s)) return true;
  } while (!is_empty(s) && (c == *s++ || c == '.'));
  return false;
}

bool match_char(char* re, char* s) {
  return !is_empty(s) && (re[0] == '.' || re[0] == s[0]);
}

bool is_empty(char* re) {
  return re[0] == '\0';
}

bool is_star(char* re) {
  return re[1] == '*';
}

bool is_eol_anchor(char* re) {
  return re[0] == '$' && is_empty(re + 1);
}

void trim_trailing_newline(char* s) {
  int n = strlen(s);
  if (n > 0 && s[n - 1] == '\n') {
    s[n - 1] = '\0';
  }
}

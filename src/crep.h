#include <stdio.h>
#include <stdbool.h>

bool crex_search(char* pattern, char* filename);
bool crex_search_file(char* pattern, char* filename);
bool crex_search_line(char* pattern, size_t lineno);

typedef struct {
  char* _data;
  int len;
} String;

typedef struct {
  int x;
} Machine;

typedef struct {
  char* regex;
  int machine;
} crex_regex_t;


#include <stdio.h>
#include <stdlib.h>
#include "crep.h"

void die(char* msg) {
  fprintf(stderr, "Error: %s\n", msg);
  exit(EXIT_FAILURE);
}

char* usage() {
  static char* usage = "usage: crex <pattern> <file>";
  return usage;
}

bool check_file_exists(char* filename) {
  return true;
}

void check_argv(int argc, char** argv) {
  if (argc != 3) { die(usage()); }
  if (!check_file_exists(argv[2])) { die("Invalid file."); }
}

int main(int argc, char** argv) {
  check_argv(argc, argv);
  crep_search(argv[1], argv[2]);  
}

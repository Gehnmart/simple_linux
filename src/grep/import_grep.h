#ifndef IMPORT_GREP_H
#define IMPORT_GREP_H

#define MAX_BUFF_SIZE 4096

typedef struct {
  int opt_e;
  int opt_i;
  int opt_v;
  int opt_c;
  int opt_l;
  int opt_n;
  int opt_h;
  int opt_s;
  int opt_f;
  int opt_o;

  int active;
} option_t;

typedef struct {
  int pattern_count;
  char** pattern;
} pattern_t;

#endif /*IMPORT_GREP_H*/
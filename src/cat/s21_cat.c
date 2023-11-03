#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static struct option longopts[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                   {"number", no_argument, NULL, 'n'},
                                   {"squeeze-blank", no_argument, NULL, 's'}};

typedef struct {
  int opt_b;
  int opt_e;
  int opt_n;
  int opt_s;
  int opt_t;
  int opt_v;
} option_t;

void cat_cook(FILE* file, option_t* option_storage);
void scan_files(option_t* option_storage, char** argv, int argc, int cooked);

int main(int argc, char** argv) {
  int res;
  int error = 0;
  int idx = 0;

  option_t option_storage = {0};

  int breakflag = 0;

  while ((res = getopt_long(argc, argv, "beEnstTv", longopts, &idx)) != -1){
    switch (res) {
      case 'b':
        option_storage.opt_b = 1;
        option_storage.opt_n = 1;
        break;
      case 'e':
        option_storage.opt_e = 1;
        option_storage.opt_v = 1;
        break;
      case 'E':
        option_storage.opt_e = 1;
        break;
      case 'n':
        option_storage.opt_n = 1;
        break;
      case 's':
        option_storage.opt_s = 1;
        break;
      case 't':
        option_storage.opt_t = 1;
        option_storage.opt_v = 1;
        break;
      case 'T':
        option_storage.opt_t = 1;
        break;
      case 'v':
        option_storage.opt_v = 1;
        break;
      case '?':
        error = 1;
        breakflag = 1;
        break;
      default:
        error = 1;
        breakflag = 1;
        break;
    }
    if(breakflag == 1) break;
  }
  argv += optind;

  if (error) {
    fprintf(stderr, "usage: cat [-benstv] [file ...]\n");
  }
  else if (option_storage.opt_b || option_storage.opt_e || option_storage.opt_n ||
      option_storage.opt_s || option_storage.opt_t || option_storage.opt_v) {
    scan_files(&option_storage, argv, argc, 0);
  } else {
    scan_files(&option_storage, argv, argc, 1);
  }

  return 0;
}

void scan_files(option_t* option_storage, char** argv, int argc, int cooked) {
  char* path;

  for (int i = 0; ((path = argv[i]) != NULL || i == 0) && i < argc; i++) {
    if (path != NULL) {
      FILE* file = fopen(path, "r");
      if (file == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", path);
      } else {
        if (cooked == 1) {
          char ch = EOF;
          while ((ch = getc(file)) != EOF) {
            putchar(ch);
          }
        } else if (cooked == 0) {
          file = fopen(path, "r");
          cat_cook(file, option_storage);
        }
        if(file != NULL){
          fclose(file);
        }
      }
    } else break;
  }
}

void cat_cook(FILE* file, option_t* option_storage) {
  int ch, prev;
  int line = 0;
  int gooble = 0;
  FILE* fp = file;

  for (prev = '\n'; (ch = fgetc(fp)) != EOF; prev = ch) {
    if (prev == '\n') {
      if (option_storage->opt_s) {
        if (ch == '\n') {
          if (gooble) continue;
          gooble = 1;
        } else {
          gooble = 0;
        }
      }
      if (option_storage->opt_n && (!option_storage->opt_b || ch != '\n'))
        printf("%6d\t", ++line);
    }
    if (ch == '\n') {
      if (option_storage->opt_e && putchar('$') == EOF) break;
    } else if (ch == '\t') {
      if (option_storage->opt_t) {
        if (printf("^I") == EOF) break;
        continue;
      }
    } else if (option_storage->opt_v) {
      if (ch > 127 && ch < 160) printf("M-^");
      if ((ch == 127 || (ch >= 0 && ch <= 31)) && (ch != '\n' && ch != '\t'))
        printf("^");
      if ((ch < 32 || (ch > 126 && ch < 160)) && ch != '\n' && ch != '\t')
        ch = ch > 126 ? ch - 64 : ch + 64;
    }
    putchar(ch);
  }
}
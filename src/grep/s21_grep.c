#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define True 1
#define False 0

typedef char bool;
extern char* optarg;

typedef struct {
bool e_flag;
bool i_flag;
bool v_flag;
bool c_flag;
bool l_flag;
bool n_flag;
bool h_flag;
bool s_flag;
bool f_flag;
bool o_flag;

bool any_flag;
} Tflags;

typedef struct {
  int pattern_count;
  int pattern_length;
  char** pattern;
} Tpatterns;

void regexp_import_from_file(char *path, Tpatterns* patterns);
void parce(Tflags* flags, Tpatterns* patterns, int argc, char** argv);
void scan_files(char** argv, bool cooked, Tpatterns* pattern);
void only_pattern(FILE* file, char* path, Tpatterns* patterns);

int main(int argc, char** argv) {

  Tflags flags = {0};
  Tpatterns patterns;

  parce(&flags, &patterns, argc, argv);

  argv+=optind;

  int cnt = 0;

  if (flags.any_flag) {
    scan_files(argv, True, &patterns);
  }

  return 0;
}

void parce(Tflags* flags, Tpatterns* patterns, int argc, char** argv) {
  bool any_flag = False;
  int res;
  patterns->pattern = malloc(sizeof(char*) * 32);

  for(; (res = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1;){
    switch (res) {
      case 'e':
        flags->e_flag = flags->any_flag = True;
        patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * 4098);
        strcpy(patterns->pattern[patterns->pattern_count++], optarg);
        break;
      case 'f':
        flags->f_flag = flags->any_flag = True;
        regexp_import_from_file(optarg, patterns);
        break;
      case 'i':
        flags->i_flag = flags->any_flag = True;
        break;
      case 'v':
        flags->v_flag = flags->any_flag = True;
        break;
      case 'c':
        flags->c_flag = flags->any_flag = True;
        break;
      case 'l':
        flags->l_flag = flags->any_flag = True;
        break;
      case 'n':
        flags->n_flag = flags->any_flag = True;
        break;
      case 'h':
        flags->h_flag = flags->any_flag = True;
        break;
      case 's':
        flags->s_flag = flags->any_flag = True;
        break;
      case 'o':
        flags->o_flag = flags->any_flag = True;
        break;
      case '?':
        printf("usage: %c [-eivclnhsfo] [file ...]\n", res);
        exit(1);
    }
  }
}

void only_pattern(FILE* file, char* path, Tpatterns* patterns){
  char buf[4096];
  while((fgets(buf, 4096, file)) != NULL){
    for(int j = 0; j < patterns->pattern_count; j++){
      if(strstr(buf, patterns->pattern[j]) != NULL){
        printf("%s", buf);
        break;
      }
    }
  }
}

void scan_files(char** argv, bool cooked, Tpatterns* patterns) {
  char* path;
  FILE* file;

  for (int i = 0; (path = argv[i]) != NULL || i == 0; i++) {
    if (path == NULL) {
      while (True) {
        char buf[4096];
        scanf("%s", buf);
      }
    } else {
      if (cooked) {
          file = fopen(path, "r");
          if (file == NULL) {
            printf("cat: %s: No such file or directory\n", path);
          } else {
            only_pattern(file, path, patterns);
        }
      } else {
        file = fopen(path, "r");
      }
    }
  }
}

void regexp_import_from_file(char *path, Tpatterns* patterns){
  FILE* file;
  char* regexp_import = malloc(sizeof(char) * 4096);

  if (path == NULL) {
    printf("cat: %s: No such file or directory\n", path);
  } else {
    file = fopen(path, "r");
    if (file == NULL) {
      printf("cat: %s: No such file or directory\n", path);
    } else {
      char buf[4096];
      for(int i = 0; (fgets(buf, 4096, file)) != NULL; i++){
        patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * 4098);
        patterns->pattern[patterns->pattern_count++] = buf;
      }
    }
  }
}
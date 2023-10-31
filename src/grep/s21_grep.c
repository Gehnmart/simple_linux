#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>

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
void scan_files(Tflags* flags, char** argv, bool cooked, Tpatterns* pattern);
void only_pattern(FILE* file, Tpatterns* patterns, Tflags* flags, char* path, int file_counter);

int main(int argc, char** argv) {

  Tflags flags = {0};
  Tpatterns patterns;

  parce(&flags, &patterns, argc, argv);

  argv+=optind;

  if (flags.any_flag) {
    scan_files(&flags, argv, True, &patterns);
  } else {
    argv+=1;
    scan_files(&flags, argv, False, &patterns);
  }

  for(int j = 0; j < patterns.pattern_count; j++){
    free(patterns.pattern[j]);
  }
  free(patterns.pattern);

  return 0;
}

void parce(Tflags* flags, Tpatterns* patterns, int argc, char** argv) {
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

void only_pattern(FILE* file, Tpatterns* patterns, Tflags* flags, char* path, int file_counter){
  char buf[4096];

  //bool str_in = False;
  (void)flags;
  (void)path;
  //int str_in_counter = 0;

  while((fgets(buf, 4096, file)) != NULL){
    char* ptrn;
    int i = 0;
    for(; (ptrn = patterns->pattern[i]) != NULL; i++){
      regex_t reegex;
  
      int flag = 0;
  
      flag = regcomp( &reegex, ptrn, 0);
      flag = regexec( &reegex, buf, 0, NULL, 0);

      if(flags->v_flag) flag = !flag;
      if(flag){
        printf("%s", buf);
      }
    }
  }

  if(file_counter > 1) printf("%c", '\n');
}

void scan_files(Tflags* flags, char** argv, bool cooked, Tpatterns* patterns) {
  char* path;
  FILE* file;

  int file_counter = 0;
  int i = 0;

  if((!flags->f_flag && !flags->e_flag) && argv[0] != NULL){
    patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * 4098);
    strcpy(patterns->pattern[patterns->pattern_count++], argv[0]);
    file_counter--;
    i++;
  }

  for (int j = 0; (path = argv[j]) != NULL; file_counter++, j++);

  for (; (path = argv[i]) != NULL || i == 0; i++) {
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
            only_pattern(file, patterns, flags, path, file_counter);
          }
      } else {
          file = fopen(path, "r");
          if (file == NULL) {
            printf("cat: %s: No such file or directory\n", path);
          } else {
            only_pattern(file, patterns, flags, path, file_counter);
          }
      }
    }
  }
}

void regexp_import_from_file(char *path, Tpatterns* patterns){
  FILE* file;

  if (path == NULL) {
    printf("cat: %s: No such file or directory\n", path);
  } else {
    file = fopen(path, "r");
    if (file == NULL) {
      printf("cat: %s: No such file or directory\n", path);
    } else {
      char buf[4096];
      for(int i = 0; (fgets(buf, 4096, file)) != NULL; i++){
        if(buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
        patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * 4098);
        strcpy(patterns->pattern[patterns->pattern_count++], buf);
      }
    }
  }
}
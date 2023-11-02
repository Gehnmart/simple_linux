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

int parce(Tflags* flags, Tpatterns* patterns, int argc, char** argv);
void scan_files(Tflags* flags, char** argv, bool cooked, Tpatterns* pattern);
void pattern_process(FILE* file, Tpatterns* patterns, Tflags* flags, char* path, int file_counter);
void add_pattern(Tpatterns* patterns, char* buf);
int free_patterns(Tpatterns* patterns);
bool add_pattern_from_file(char* path, Tpatterns* patterns, Tflags* flags);
bool re_match(char* pattern, char* string, bool ignore_case);
bool replace_enter(char* str, char c);
bool cnt_str(char *str, char *ptrn, bool ignore_case);

int main(int argc, char** argv) {
  Tflags flags = {0};
  Tpatterns patterns;

  if (!parce(&flags, &patterns, argc, argv)) {
    free_patterns(&patterns);
    return 0;
  }

  argv += optind;

  if (flags.any_flag) {
    scan_files(&flags, argv, True, &patterns);
  } else {
    argv += 1;
    scan_files(&flags, argv, False, &patterns);
  }

  free_patterns(&patterns);

  return 0;
}

int free_patterns(Tpatterns* patterns) {
  if (patterns == NULL) {
    return False;
  }
  for (int j = 0; j < patterns->pattern_count; j++) {
    free(patterns->pattern[j]);
  }
  free(patterns->pattern);

  return True;
}

int parce(Tflags* flags, Tpatterns* patterns, int argc, char** argv) {
  int res = 0;

  patterns->pattern = malloc(sizeof(char*) * 32);

  for (int i = 0; i < argc; i++){
    for (int j = 0; j < (int)strlen(argv[i]); j++){
      if(argv[i][0] == '-' && argv[i][j] == 's') flags->s_flag = flags->any_flag = True;
    }
  }

  for (; (res = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1;) {
    switch (res) {
      case 'e':
        flags->e_flag = flags->any_flag = True;
        add_pattern(patterns, optarg);
        break;
      case 'f':
        flags->f_flag = flags->any_flag = True;
        if(!add_pattern_from_file(optarg, patterns, flags)){
          return 0;
        }
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
        return False;
    }
  }
  return True;
}

void pattern_process(FILE* file, Tpatterns* patterns, Tflags* flags, char* path, int file_counter) {
  char buf[4096];

  bool str_in = False;
  int all_str_count = 0;

  for (int str_counter = 1; (fgets(buf, 4096, file)) != NULL; str_counter++) {
    replace_enter(buf, '\0');
    char* ptrn;

    for (int i = 0; ((ptrn = patterns->pattern[i]) != NULL); i++) {
      if(flags->o_flag && !flags->l_flag) {
        if(re_match(ptrn, buf, flags->i_flag) != 0)
        if (file_counter > 1 && str_in) printf("%s:", path);
        str_in = cnt_str(buf, ptrn, flags->i_flag);
      } else {
        str_in = re_match(ptrn, buf, flags->i_flag);
      }
      if (str_in) break;
    }
    if (flags->v_flag) str_in = !str_in;
    if (str_in) {
      if (!flags->c_flag && !flags->l_flag && (!flags->o_flag)) {
        if (file_counter > 1 && !flags->h_flag) printf("%s:", path);
        if (flags->n_flag) printf("%d:", str_counter);
        printf("%s", buf);
        putchar('\n');
      } else {
        all_str_count++;
        if (flags->l_flag)
          break;
        else
          continue;
      }
      all_str_count++;
    }
  }
  if (flags->c_flag) flags->n_flag = False;
  if (flags->c_flag && (!flags->o_flag)) {
    if (file_counter > 1 && !flags->h_flag) printf("%s:", path);
    printf("%d\n", all_str_count);
  }
  if (flags->l_flag && all_str_count) {
    printf("%s\n", path);
  }
}

bool replace_enter(char* str, char c) {
  for (int i = 0; i < (int)strlen(str); i++)
    if (str[i] == '\n') {
      str[i] = c;
      return True;
    }
  return False;
}

bool cnt_str(char *str, char *ptrn, bool ignore_case) {
  regex_t regex;
  regmatch_t match[4096];

  int cnt;

  if(regcomp(&regex, ptrn, ignore_case ? REG_ICASE|REG_EXTENDED : REG_EXTENDED) != 0){
    return 0;
  }

  while((regexec(&regex, str, 4096, match, 0) == 0)){
    int start = match[0].rm_so;
    int end = match[0].rm_eo;
    printf("%.*s\n", end-start, str+start);

    str = str+end;
    cnt++;
  }

  regfree(&regex);

  return (cnt > 0);
}

bool re_match(char* pattern, char* string, bool ignore_case) {
  regex_t reegex;
  int status;

  if (regcomp(&reegex, pattern, ignore_case ? REG_ICASE | REG_EXTENDED : 0) !=
      0)
    return 0;

  status = regexec(&reegex, string, 0, NULL, 0);

  regfree(&reegex);

  if (status != 0) return False;

  return True;
}

void add_pattern(Tpatterns* patterns, char* buf) {
  patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * 4098);
  strcpy(patterns->pattern[patterns->pattern_count++], buf);
}

void scan_files(Tflags* flags, char** argv, bool cooked, Tpatterns* patterns) {
  char* path;
  FILE* file;

  int file_counter = 0;
  int i = 0;

  if ((!flags->f_flag && !flags->e_flag) && argv[0] != NULL) {
    add_pattern(patterns, argv[0]);
    file_counter--;
    if (cooked) i++;
  }

  for (int j = 0; (path = argv[j]) != NULL; file_counter++, j++)
    ;

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
          if (!flags->s_flag)
            fprintf(stderr, "grep: %s: No such file or directory\n", path);
        } else {
          pattern_process(file, patterns, flags, path, file_counter);
        }
      } else {
        file = fopen(path, "r");
        if (file == NULL) {
          if (!flags->s_flag)
            fprintf(stderr, "grep: %s: No such file or directory\n", path);
        } else {
          pattern_process(file, patterns, flags, path, file_counter);
        }
      }
    }
  }
}

bool add_pattern_from_file(char* path, Tpatterns* patterns, Tflags* flags) {
  FILE* file;

  bool error = True;

  if (path == NULL) {
    if(flags->s_flag)
      fprintf(stderr, "grep: %s: No such file or directory\n", path);
    error = False;
  } else {
    file = fopen(path, "r");
    if (file == NULL) {
      if(flags->s_flag)
        fprintf(stderr, "grep: %s: No such file or directory\n", path);
      error = False;
    } else {
      char buf[4096];
      for (int i = 0; (fgets(buf, 4096, file)) != NULL; i++) {
        if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
        add_pattern(patterns, buf);
      }
    }
  }
  return error;
}
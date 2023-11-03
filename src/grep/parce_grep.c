#include "parce_grep.h"

int patternFree(pattern_t* patterns) {
  if (patterns == NULL){
    return 0;
  }
  for (int j = 0; j < patterns->pattern_count; j++) {
    if(patterns->pattern[j] != NULL)
      free(patterns->pattern[j]);
  }
  return 1;
}

int optionParce(option_t* options, pattern_t* patterns, int argc, char** argv) {
  int res = 0;

  patterns->pattern = malloc(sizeof(char*) * 32);

  for (int i = 0; i < argc; i++) {
    for (int j = 0; j < (int)strlen(argv[i]); j++) {
      if (argv[i][0] == '-' && argv[i][j] == 's')
        options->opt_s = options->active = 1;
    }
  }

  for (; (res = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1;) {
    switch (res) {
      case 'e':
        options->opt_e = options->active = 1;
        patternAdd(patterns, optarg);
        break;
      case 'f':
        options->opt_f = options->active = 1;
        if (!patternImportFromFile(optarg, patterns)) {
          return 0;
        }
        break;
      case 'i':
        options->opt_i = options->active = 1;
        break;
      case 'v':
        options->opt_v = options->active = 1;
        break;
      case 'c':
        options->opt_c = options->active = 1;
        break;
      case 'l':
        options->opt_l = options->active = 1;
        break;
      case 'n':
        options->opt_n = options->active = 1;
        break;
      case 'h':
        options->opt_h = options->active = 1;
        break;
      case 's':
        options->opt_s = options->active = 1;
        break;
      case 'o':
        options->opt_o = options->active = 1;
        break;
      case '?':
        printf("%s%s",
               "usage: grep [-eivclnhsfo] [-A num] [-B num] [-C[num]]\n",
               "\t[-e pattern] [-f file]\n");
        return 0;
    }
  }
  return 1;
}

void patternMatch(FILE* file, pattern_t* patterns, option_t* options,
                  char* path, int file_counter) {
  
  char line[MAX_BUFF_SIZE] = {0};
  int pattern_matched = 0;
  int total_pattern_matched = 0;
  int line_number_counter = 1;

  if(options->opt_v || options->opt_c || options->opt_l) options->opt_o = 0;

  for (; (fgets(line, MAX_BUFF_SIZE, file)) != NULL;
       line_number_counter++) {
    replaceEnterInString(line);
    char* ptrn = NULL;

    for (int i = 0; ((ptrn = patterns->pattern[i]) != NULL); i++) {
      if (options->opt_o) {
        if (patternIsFoundInString(ptrn, line, options) != 0)
          if (file_counter > 1 && pattern_matched)
            printf("%s:", path);
        pattern_matched = allPatternInString(line, ptrn, options);
      } else {
        pattern_matched = patternIsFoundInString(ptrn, line, options);
      }
      if (pattern_matched) break;
    }
    if (options->opt_v) pattern_matched = !pattern_matched;
    if (pattern_matched) {
      if (!options->opt_c && !options->opt_l && (!options->opt_o)) {
        if (file_counter > 1 && !options->opt_h) printf("%s:", path);
        if (options->opt_n) printf("%d:", line_number_counter);
        printf("%s", line);
        putchar('\n');
      } else {
        total_pattern_matched++;
        if (options->opt_l)
          break;
        else
          continue;
      }
      total_pattern_matched++;
    }
  }
  if (options->opt_c) options->opt_n = 0;
  if (options->opt_c && (!options->opt_o)) {
    if (file_counter > 1 && !options->opt_h) printf("%s:", path);
    printf("%d\n", total_pattern_matched);
  }
  if (options->opt_l && total_pattern_matched) {
    printf("%s\n", path);
  }
}

int replaceEnterInString(char* str) {
  for (int i = 0; i < (int)strlen(str); i++)
    if (str[i] == '\n') {
      str[i] = '\0';
      return 1;
    }
  return 0;
}

void patternAdd(pattern_t* patterns, char* buf) {
  patterns->pattern[patterns->pattern_count] = malloc(sizeof(char) * MAX_BUFF_SIZE);
  strcpy(patterns->pattern[patterns->pattern_count++], buf);
}

void runGrep(option_t* options, char** argv, int cooked, pattern_t* patterns) {
  char* path = NULL;

  int file_counter = 0;
  int i = 0;

  if ((!options->opt_f && !options->opt_e) && argv[0] != NULL) {
    patternAdd(patterns, argv[0]);
    file_counter--;
    if (cooked) i++;
  }

  for (int j = 0; (path = argv[j]) != NULL; file_counter++, j++)
    ;

  for (; (path = argv[i]) != NULL || i == 0; i++) {
    if (path != NULL) {
      FILE* file = fopen(path, "r");
      if (file == NULL) {
        if (!options->opt_s)
          fprintf(stderr, "grep: %s: No such file or directory\n", path);
      } else {
        patternMatch(file, patterns, options, path, file_counter);
        fclose(file);
      }
    }
  }
}

int patternImportFromFile(char* path, pattern_t* patterns) {
  int error = 1;

  if (path == NULL) {
    error = 0;
  } else {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
      fprintf(stderr, "grep: %s: No such file or directory\n", path);
      error = 0;
    } else {
      char buf[MAX_BUFF_SIZE];
      for (int i = 0; (fgets(buf, MAX_BUFF_SIZE, file)) != NULL; i++) {
        if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
        patternAdd(patterns, buf);
      }

      fclose(file);
    }
  }
  return error;
}
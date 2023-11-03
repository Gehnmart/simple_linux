#include "re_grep.h"

int allPatternInString(char* str, char* ptrn, option_t* options) {
  regex_t regex;
  regmatch_t match[MAX_BUFF_SIZE];

  int counter = 0;

  if (regcomp(&regex, ptrn,
              options->opt_i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED) != 0) {
    return 0;
  }

  for (int i = 0; (regexec(&regex, str, MAX_BUFF_SIZE, match, 0) == 0); i++) {
    int start = match[0].rm_so;
    int end = match[0].rm_eo;
    printf("%.*s\n", end - start, str + start);

    str = str + end;
    counter += end;
  }

  regfree(&regex);

  return counter;
}

int patternIsFoundInString(char* ptrn, char* str, option_t* options) {
  regex_t reegex;
  int status;

  if (regcomp(&reegex, ptrn,
              options->opt_i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED) != 0)
    return 0;

  status = regexec(&reegex, str, 0, NULL, 0);

  regfree(&reegex);

  if (status != 0) return 0;

  return 1;
}
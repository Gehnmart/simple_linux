#include "re_grep.h"

int allPatternInString(char* str, char* ptrn, option_t* options) {
  regex_t regex;
  regmatch_t match[MAX_BUFF_SIZE];

  int cnt;

  if (regcomp(&regex, ptrn,
              options->opt_i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED) != 0) {
    return 0;
  }

  while ((regexec(&regex, str, MAX_BUFF_SIZE, match, 0) == 0)) {
    int start = match[0].rm_so;
    int end = match[0].rm_eo;
    printf("%.*s\n", end - start, str + start);

    str = str + end;
    cnt++;
  }

  regfree(&regex);

  return (cnt > 0);
}

int patternIsFoundInString(char* pattern, char* string, option_t* options) {
  regex_t reegex;
  int status;

  if (regcomp(&reegex, pattern, options->opt_i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED) !=
      0)
    return 0;

  status = regexec(&reegex, string, 0, NULL, 0);

  regfree(&reegex);

  if (status != 0) return 0;

  return 1;
}
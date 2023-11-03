#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "re_grep.h"
#include "parce_grep.h"

int main(int argc, char** argv) {
  option_t options = {0};
  pattern_t patterns;
  patterns.pattern_count = 0;

  if (!optionParce(&options, &patterns, argc, argv)) {
    patternFree(&patterns);
    return 0;
  }

  argv += optind;

  if (options.active) {
    runGrep(&options, argv, 1, &patterns);
  } else {
    argv += 1;
    runGrep(&options, argv, 0, &patterns);
  }

  patternFree(&patterns);


  return 0;
}
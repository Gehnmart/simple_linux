#include "parce_grep.h"
#include "re_grep.h"

int main(int argc, char** argv) {
  option_t options = {0};
  pattern_t patterns_storage;
  patterns_storage.pattern_count = 0;

  if (!optionParce(&options, &patterns_storage, argc, argv)) {
    patternFree(&patterns_storage);
    return 0;
  }

  argv += optind;

  if (options.active) {
    runGrep(&options, argv, 1, &patterns_storage);
  } else {
    argv += 1;
    runGrep(&options, argv, 0, &patterns_storage);
  }

  patternFree(&patterns_storage);

  return 0;
}
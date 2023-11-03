#include "parce_grep.h"
#include "re_grep.h"

int main(int argc, char** argv) {
  option_t options = {0};
  pattern_t pattern_storage;
  pattern_storage.pattern_count = 0;
  pattern_storage.pattern = (char**)malloc(sizeof(char*) * 32);
  for(int i = 0; i < 32; i++) pattern_storage.pattern[i] = NULL;

  int is_parce = 0;
  is_parce = optionParce(&options, &pattern_storage, argc, argv);

  if (is_parce) {
    argv += optind;

    if (options.active == 1) {
      runGrep(&options, argv, 1, &pattern_storage);
    } else {
      argv += 1;
      runGrep(&options, argv, 0, &pattern_storage);
    }
  }

  patternFree(&pattern_storage);

  return 0;
}
#ifndef GREP_PARCE_H
#define GREP_PARCE_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "import_grep.h"
#include "re_grep.h"

void patternMatch(FILE* file, pattern_t* pattern_storage, option_t* options,
                  char* path, int file_counter);
void runGrep(option_t* options, char** argv, int cooked,
             pattern_t* pattern_storage);
void patternAdd(pattern_t* pattern_storage, char* buf);
int optionParce(option_t* options, pattern_t* pattern_storage, int argc,
                char** argv);
int patternImportFromFile(char* path, pattern_t* pattern_storage);
int patternFree(pattern_t* pattern_storage);
int replaceEnterInString(char* str);

#endif /*GREP_PARCE_H*/
#ifndef GREP_PARCE_H
#define GREP_PARCE_H

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "import_grep.h"
#include "re_grep.h"

extern char* optarg;

void patternMatch(FILE* file, pattern_t* patterns, option_t* options, char* path, int file_counter);
void runGrep(option_t* options, char** argv, int cooked, pattern_t* pattern);
void patternAdd(pattern_t* patterns, char* buf);
int optionParce(option_t* options, pattern_t* patterns, int argc, char** argv);
int patternImportFromFile(char* path, pattern_t* patterns);
int patternFree(pattern_t* patterns);
int replaceEnterInString(char* str);

#endif /*GREP_PARCE_H*/
#ifndef RE_GREP_H
#define RE_GREP_H

#include <regex.h>
#include <stdio.h>

#include "import_grep.h"

int patternIsFoundInString(char* ptrn, char* str, option_t* options);
int allPatternInString(char* str, char* ptrn, option_t* options);

#endif /*RE_GREP_H*/
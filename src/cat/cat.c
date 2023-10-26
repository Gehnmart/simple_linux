#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_argument(char* arg);
int type_of_arg(char* arg);
FILE* get_file(char* arg);
void simple_out_from_file(FILE* file);
int string_ending_from_file(FILE* file);
int numbers_all_lines_from_file(FILE* file);

int main(int argc, char** argv) {
    int arg_type = 0;
    for(int i = 1; i < argc; i++){
        if(is_argument(argv[i])){
            arg_type = type_of_arg(argv[i]);
        }
        FILE* file = get_file(argv[i]);

        if(file != NULL) {
            switch(arg_type){
                case 0:
                    simple_out_from_file(file);
                    break;
                case 1:
                    
                case 2:
                    string_ending_from_file(file);
                    break;
                case 3:
                    numbers_all_lines_from_file(file);
                    break;
                default:
                    printf("Error");
            }

        }
    }
}

int is_argument(char* arg) {
    return arg[0] == '-'? 1 : 0;
}

int type_of_arg(char* arg) {
    switch(arg[1]){
        case 'b':
            return 1;
        case 'e':
            return 2;
        case 'n':
            return 3;
        case 's':
            return 4;
        case 't':
            return 5;
        default:
            return 0;
    }
}

FILE* get_file(char* arg) {
    FILE* file = fopen(arg, "r");
    if(file == NULL) {
        return NULL;
    } else {
        return file;
    }
}

void simple_out_from_file(FILE* file){
    char c = fgetc(file);

    for(; c != EOF; c = fgetc(file)){
        printf("%c", c);
    }
}

int numbers_non_void_lines_from_file(FILE* file){
    char buff[256] = {0};

    for(int i = 0; fgets(buff, 256, file); i++) {
        printf("     %d  ", i+1);
        for(int j = 0; j < (int)strlen(buff); j++) {
            printf("%c", buff[j]);
        }
    }
    return 0;
}

int string_ending_from_file(FILE* file){
    char buff[256] = {0};

    for(int i = 1; fgets(buff, 256, file); i++) {
        for(int j = 0; j < (int)strlen(buff); j++) {
            if(buff[j] == '\n') printf("$");
            printf("%c", buff[j]);
        }
    }
    return 0;
}

int numbers_all_lines_from_file(FILE* file){
    char buff[256] = {0};

    for(int i = 0; fgets(buff, 256, file); i++) {
        printf("     %d  ", i+1);
        for(int j = 0; j < (int)strlen(buff); j++) {
            printf("%c", buff[j]);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_argument(char* arg);
int type_of_arg(char* arg);
int is_file_name(char* arg);
void simple_out_from_file(char* arg);
int end_string_from_file(char* arg);
int numerick_from_file(char* arg);

int main(int argc, char** argv) {
    int arg_type = 0;
    for(int i = 1; i < argc; i++){
        if(is_argument(argv[i])){
            arg_type = type_of_arg(argv[i]);
        } else if(is_file_name(argv[i])) {
            switch(arg_type){
                case 0:
                    simple_out_from_file(argv[i]);
                    break;
                case 2:
                    end_string_from_file(argv[i]);
                    break;
                case 3:
                    numerick_from_file(argv[i]);
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

int is_file_name(char* arg) {
    FILE* file = fopen(arg, "r");
    if(file = NULL) {
        fclose(file);
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

void simple_out_from_file(char* arg){
    FILE* file = fopen(arg, "r");
    char c = fgetc(file);
    for(; c != EOF; c = fgetc(file)){
        printf("%c", c);
    }
}

int end_string_from_file(char* arg){
    FILE* file = fopen(arg, "r");
    char buff[256] = {0};
    char c = '0';

    for(int i = 1; fgets(buff, 256, file); i++) {
        for(int j = 0; j < strlen(buff); j++) {
            if(buff[j] == '\n') printf("$");
            printf("%c", buff[j]);
            if(c == EOF || c == '\0'){
                return 1;
            }
        }
    }
}

int numerick_from_file(char* arg){
    FILE* file = fopen(arg, "r");
    char buff[256] = {0};
    char c = '0';

    for(int i = 1; fgets(buff, 256, file); i++) {
        printf("     %d  ", i);
        for(int j = 0; j < strlen(buff); j++) {
            printf("%c", buff[j]);
            if(c == EOF || c == '\0'){
                return 1;
            }
        }
    }
}
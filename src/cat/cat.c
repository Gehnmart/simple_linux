#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_argument(char* arg);
int type_of_arg(char* arg);
FILE* get_file(char* arg);
void none_argument(FILE* file);
void b_argument(FILE* file);
void e_argument(FILE* file);
void n_argument(FILE* file);
void s_argument(FILE* file);
void t_argument(FILE* file);

int main(int argc, char** argv) {
    int arg_type = 0;
    for(int i = 1; i < argc; i++){
        if(is_argument(argv[i])){
            arg_type = type_of_arg(argv[i]);
        }

        FILE* file = get_file(argv[i]);

        if(file != NULL) {
            fprintf(file, "\t");
            switch(arg_type){
                case 0:
                    none_argument(file);
                    break;
                case 1:
                    b_argument(file);
                    break;
                case 2:
                    e_argument(file);
                    break;
                case 3:
                    n_argument(file);
                    break;
                case 4:
                    s_argument(file);
                    break;
                case 5:
                    t_argument(file);
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

void none_argument(FILE* file){
    char c = fgetc(file);

    for(; c != EOF; c = fgetc(file)){
        printf("%c", c);
    }
}

void b_argument(FILE* file){
    char buff[256] = {0};
    int flag = 0;
    for(int i = 0; fgets(buff, 256, file);){
        flag = 0;
        for(int j = 0; j < (int)strlen(buff); j++) {
            if(buff[j] > 31 && buff[j] < 127){
                flag = 1;
                break;
            }
        }
        if(flag) printf("     %d  %s", ++i, buff);
        else putchar('\n');
    }
}

void e_argument(FILE* file){
    char buff[256] = {0};

    while(fgets(buff, 256, file)) {
        for(int j = 0; j < (int)strlen(buff); j++) {
            if(buff[j] == '\n') putchar('$');
            putchar(buff[j]);
        }
    }
}

void n_argument(FILE* file){
    char buff[256] = {0};

    for(int i = 0; fgets(buff, 256, file); i++)
        printf("     %d  %s", i+1, buff);
}

void s_argument(FILE* file){
    char buff[256] = {0};
    int count = 0;
    while(fgets(buff, 256, file)){
        for(int j = 0; j < (int)strlen(buff); j++, count++) {
            if(buff[j] > 31 && buff[j] < 127){
                count = 0;
                break;
            }
        }
        if(count == 0) printf("%s", buff);
        else if(count == 1) putchar('\n');
    }
}

void t_argument(FILE* file){
    char c = fgetc(file);

    for(; c != EOF; c = fgetc(file)){
        printf("%s", c != '\t' ? (char[2]) { (char) c, '\0'} : "^|");
    }
}
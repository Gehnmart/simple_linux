#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define True 1
#define False 0

typedef char bool;

static struct option longopts[] = {
             { "number-nonblank",      no_argument,            NULL,           'b' },
             { "number",               no_argument,            NULL,           'n' },
             { "squeeze-blank",        no_argument,            NULL,           's' }
     };

char* cat_cooking(char* argv);
void usage();
void scan_files(int argc, char** argv, bool is_cooked);

bool b_flag = False;
bool e_flag = False;
bool n_flag = False;
bool s_flag = False;
bool t_flag = False;
bool v_flag = False;

int main(int argc, char** argv) {

    int res;
    int error = 0;
	int idx = 0;

    while((res = getopt_long(argc, argv, "beEnstTv", longopts, &idx)) != -1)
        switch(res) {
            case 'b':
                b_flag = True;
                break;
            case 'e':
                e_flag = True;
                v_flag = True;
                break;
            case 'E':
                e_flag = True;
                break;
            case 'n':
                n_flag = True;
                break;
            case 's':
                s_flag = True;
                break;
            case 't':
                t_flag = True;
                v_flag = True;
                break;
            case 'T':
                t_flag = True;
                break;
            case 'v':
                v_flag = True;
                break;
            case '?':
                error = 1;
                break;
            default:
                error = 1;
                break;
        }
    
    if(error){
        usage();
    }
    if(b_flag || e_flag || n_flag || s_flag || t_flag || v_flag){
        scan_files(argc, argv, False);
    }else{
        scan_files(argc, argv, True);
    }

}

void usage()
{
	printf("usage: cat [-benstuv] [file ...]\n");
	exit(1);
}

void scan_files(int argc, char** argv, bool is_cooked){
    
    char* path;
    FILE* file;
    int i = 1;

    while((path = argv[i]) != NULL){
        
    }
    if(is_cooked){
        for(int i = 1; i < argc; i++){
            FILE* file = fopen(argv[i], "r");
            if(file == NULL){
                printf("cat: %s: No such file or directory\n", argv[i]);
                continue;
            }else{
                char ch;
                while((ch = fgetc(file))!=EOF)
                    putchar(ch);
            }
        }
    }else{

    }
}

char* cat_cooking(char* argv){
    return argv;
}

bool is_printable(char ch){
    return ((ch >= ' ') && (ch <= '~')) ? True : False;
}
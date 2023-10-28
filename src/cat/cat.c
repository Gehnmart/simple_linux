#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <ctype.h>

#define True 1
#define False 0

typedef char bool;

static struct option longopts[] = {
             { "number-nonblank",      no_argument,            NULL,           'b' },
             { "number",               no_argument,            NULL,           'n' },
             { "squeeze-blank",        no_argument,            NULL,           's' }
};

void cat_cook(FILE* file);
void scan_files(char** argv, bool cooked);
bool is_printable(int ch);
bool is_ascii(int ch);
bool is_cntrl(int ch);

bool b_flag = False;
bool e_flag = False;
bool n_flag = False;
bool s_flag = False;
bool t_flag = False;
bool v_flag = False;

char* filename[FILENAME_MAX];

int main(int argc, char** argv) {

    int res;
    int error = 0;
	int idx = 0;

    while((res = getopt_long(argc, argv, "beEnstTv", longopts, &idx)) != -1)
        switch(res) {
            case 'b':
                b_flag = True;
                n_flag = True;
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
    argv += optind;
    
    if(error){
        printf("usage: cat [-benstuv] [file ...]\n");
        exit(1);
    }
    if(b_flag || e_flag || n_flag || s_flag || t_flag || v_flag){
        scan_files(argv, True);
    }else{
        scan_files(argv, False);
    }

}

void scan_files(char** argv, bool cooked){
    
    char* path;
    FILE* file;
    int i = 0;

    for(; (path = argv[i]) != NULL || i == 0; i++){
        if(path == NULL){
            while(True){
                char buf[4096];
                scanf("%s", buf);
                printf("%s\n", buf);
            }
        }else{
            if(!cooked){
                file = fopen(path, "r");
                if(file == NULL){
                    printf("cat: %s: No such file or directory\n", path);
                }else{
                    char ch;
                    while((ch = getc(file)) != EOF){
                        putchar(ch);
                    }
                }
            } else {
                file = fopen(path, "r");
                cat_cook(file);
            }
        }
    }
}

void cat_cook(FILE* file){
    int ch, prev;
    int line = 0;
    bool gooble = False;

    for(prev = '\n'; (ch = fgetc(file)) != EOF; prev = ch){
        if(prev == '\n'){
            if(s_flag){
                if(ch == '\n'){
                    if(gooble)
                        continue;
                    gooble = 1;
                } else {
                    gooble = 0;
                }
            }
            if(n_flag && (!b_flag || ch != '\n'))
                printf("%6d\t", ++line);
        }
        if(ch == '\n'){
            if(e_flag && putchar('$') == EOF)
                break;
        }
        else if(ch == '\t'){
            if(t_flag){
                if(printf("^I") == EOF)
                    break;
                continue;
            }
        }
        else if(v_flag){
            if (!is_ascii(ch) && !is_printable(ch)) {
				if (putchar('M') == EOF || putchar('-') == EOF)
					break;
                ch = toascii(ch);
			}
            if (is_cntrl(ch)) {
				if (putchar('^') == EOF || putchar(ch == 127 ? '?' : ch+64) == EOF)
					break;
				continue;
			}
        }
        if (putchar(ch) == EOF)
			break;
    }
}

bool is_printable(int ch){
    return ((ch >= ' ') && (ch <= '~'));
}

bool is_ascii(int ch){
    return ((ch >= 0) && (ch <= 127));
}

bool is_cntrl(int ch){
    return (ch == 127 || (ch >= 0 && ch <= 31));
}
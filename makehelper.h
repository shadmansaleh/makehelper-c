
typedef struct {
    char MAIN[80];
    char SRCS[3000];
    char INCLUDES[300];
    char LIBS[300];
    char CFLAGS[300];
    char LFLAGS[300];
    char CC[80];
    char EXT[10]; 
} val;

void create_new(val v);

void findfiles(char *OUT, char *PATERN);

char *strfr(char *s, char *f, char *r);

void assign(char *to, char *from);

void readMakefile(val *v);
void edit(val *v, val *w, char flag);
void modify(char *m, char *mod, char flag);
char * getFiles(const char* path,const char *patern , int showHidden);

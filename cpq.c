#include "cpq.h"

int main(int argc, char* argv[])
{
    char* name, *ext = NULL; 
    if(argc != 2)
    {
        fprintf(stderr, "%s", messages[1].string);
        return 0;
    }
    name = argv[1];
    ext = argv[1] + strlen(argv[1]) - LENEXT;
    if (!strcmp(ext, ".ou") || !strcmp(ext, ".OU"))
    {
        if(!(yyin = openFile(argv[1], "r")))
            return 0;
        
        strcpy(ext,".qud");
        
        if(!(quad = openFile(name, "w")))
            return 0;
            
        if(yyparse() || error_number)
        {
            fclose(quad);
            remove(name);
            fprintf(stderr,"%s", messages[2].string);
        }
        fclose(yyin);
        fclose(quad);
        
        return 1;
    }
    fprintf(stderr,"%s", messages[3].string);
    return 0;
}

/*Open file function*/
FILE* openFile(char* name,  char* type)
{
    FILE* file = NULL;
    file = fopen(name, type);
    if (file == NULL)
    {
        fprintf(stderr,"%s", messages[0].string);
    }
    return file;
}
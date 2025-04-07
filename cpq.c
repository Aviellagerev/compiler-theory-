#include "cpq.h"


/*error messeges*/

/* Open file function */
FILE* openFile(char* name, char* type) {
    FILE* file = fopen(name, type);
    if (file == NULL) {
     report_error(error_messeges[0]);
    }
    return file;
}

int main(int argc, char* argv[]) {
    char* name;
    char* ext = NULL; 
    
    if (argc != 2) {
        report_error(error_messeges[1]);
        return 0;
    }
    name = argv[1];
    ext = argv[1] + strlen(argv[1]) - LENEXT;
    if (!strcmp(ext, ".ou") || !strcmp(ext, ".OU")) {   
        if (!(yyin = openFile(argv[1], "r")))
            return 0;
        
        /* Change file extension for output file */
        strcpy(ext, ".qud");
        
        if (!(quad = openFile(name, "w")))
            return 0;
            
        if (yyparse() || error_number) {
          
            fclose(quad);
            remove(name);
            fclose(yyin);
            report_error(error_messeges[2]);
            
        }
        else{
            printf("Success ^-^\n ");
        fclose(yyin);
        fclose(quad);
        }

        return 1;
    }
    report_error(error_messeges[3]);
    return 0;
}

#include "translator.h"


/*--- Definitions for fixed-size storage ---*/
#define ERRLEN 100   /* Memory reserved for error message string */
#define CHRLEN 1     /* Memory reserved for a single char */
#define STRLEN 4     /* Memory reserved for command string */

/*--- Type definitions (unchanged names for compatibility) ---*/
typedef char genErrors[ERRLEN];
typedef char chars[CHRLEN];
typedef char strings[STRLEN];

/*--- Global declarations ---*/
genErrors GENERR0, GENERR1;
chars CHAR0, CHAR1, CHAR2, CHAR3, CHAR4, CHAR5;
/* Instead of separate STR0...STR13 variables, we will use our operatorStrings array below */


/* Global label counter */
int labelsCount = 0;

/*--- New error reporting routine (unused parameter 'code' now used) ---*/
typedef enum {
    NO_ERROR,
    SYNTAX_ERROR,
    SEMANTIC_ERROR,
    RUNTIME_ERROR
} ErrorCode;

static void reportError(ErrorCode code,  char *msg, int line) {
    /* For now, we simply print the error.
       The 'code' parameter could be used for further processing. */
    (void)code;  /* Avoid unused parameter warning */
    fprintf(stderr, "Error (line %d): %s\n", line, msg);
}

/*--- New static arrays for error messages, operator strings, and genChars ---*/
static char* operatorStrings[] = {
    "1",    /* index 0 */
    "TOR",  /* index 1 */
    "ASN",  /* index 2 */
    "TOI",  /* index 3 */
    "ADD",  /* index 4 */
    "SUB",  /* index 5 */
    "DIV",  /* index 6 */
    "MLT",  /* index 7 */
    "EQL",  /* index 8 */
    "NQL",  /* index 9 */
    "GRT",  /* index 10 */
    "LSS",  /* index 11 */
    "MPZ"   /* index 12 */
};

/* Array of command-character definitions */
typedef struct {
    char charCmd;
    chars* charAddress;
} charCmd;

static charCmd genCharsArr[] = {
    { 'I', &CHAR0 }, /* int */
    { 'R', &CHAR1 }, /* float/real */
    { 'N', &CHAR2 }, /* not */
    { 'E', &CHAR3 }, /* equal */
    { '*', &CHAR4 }, /* temporary label variable */
    { 'J', &CHAR5 }  /* jump */
};

/* Error messages using GENERR arrays */
typedef struct {
    char* genString;
    genErrors* genAddress;
} errGenMsg;

static errGenMsg genMessages[] = {
    { "ERROR: unknown variable, not defined in the symbol table\n", &GENERR0 },
    { "cast from float to int ERROR!\n", &GENERR1 }
};

/*--- Prototypes for external functions (assumed to be defined elsewhere) ---*/


/*--- Function prototypes changed to accept  strings for input ---*/

/*--- Function implementations ---*/

/* Merge two command lists */
command_list* merge_comnd_list(command_list* head, command_list* tail) {
    command_list* last = head;
    if (!head)
        return tail;
    while (last->next)
        last = last->next;
    last->next = tail;
    return head;
}

/* Prepend a new command to the command list */
command_list* add_new_command_list(command_list* list, command* com) {
    command_list* newNode = (command_list*)malloc(sizeof(command_list));
    if (!newNode) {
        reportError(RUNTIME_ERROR, "Memory allocation failed in add_new_command_list", __LINE__);
        return list;
    }
    newNode->com = com;
    newNode->next = list;
    return newNode;
}

/* Merge two command sequences */
command* merege_comand(command* head, command* tail) {
    if (!head)
        return tail;
    command* last_comnd = get_last_command(head);
    last_comnd->next = tail;
    return head;
}

/* Retrieve the last command in a linked list */
command* get_last_command(command* head) {
    command* last_comnd = head;
    while (last_comnd && last_comnd->next)
        last_comnd = last_comnd->next;
    return last_comnd;
}

/* Create and append a quad command */
command* translate_comand(command* head, char type,  char *com,  char *firstArg,  char *secondArg,  char *thirdArg) {
    command *new_comnd, *prev_comnd;
    if (!head) {
        head = (command *)malloc(sizeof(command));
        if (!head) {
            reportError(RUNTIME_ERROR, "Memory allocation failed in translate_comand", __LINE__);
            return NULL;
        }
        new_comnd = head;
    } else {
        prev_comnd = get_last_command(head);
        new_comnd = (command *)malloc(sizeof(command));
        if (!new_comnd) {
            reportError(RUNTIME_ERROR, "Memory allocation failed in translate_comand", __LINE__);
            return head;
        }
        prev_comnd->next = new_comnd;
    }
    sprintf(new_comnd->com, "%c%s", type, com);
    sprintf(new_comnd->firstArg, "%s", firstArg);
    sprintf(new_comnd->secondArg, "%s", secondArg);
    sprintf(new_comnd->thirdArg, "%s", thirdArg);
    new_comnd->next = NULL;
    return head;
}

/* Create assignment command */
command* add_assign_commadn(char* var, char* exp, char expType, command* expHead) {
    var_node* symbol = search_varible(var);
    command* head = NULL;
    free_state(exp);
    if (!symbol) {
        reportError(SYNTAX_ERROR, genMessages[0].genString, __LINE__);
        return NULL;
    }
    else if (symbol->type == genCharsArr[0].charCmd && expType == genCharsArr[1].charCmd) {
        reportError(SYNTAX_ERROR, genMessages[1].genString, __LINE__);
        return NULL;
    }
    else {
        if (symbol->type == genCharsArr[1].charCmd && expType == genCharsArr[0].charCmd)
            return translate_comand(expHead, genCharsArr[0].charCmd, operatorStrings[1], var, exp, " ");
        if (!expHead)
            return translate_comand(NULL, symbol->type, operatorStrings[2], var, exp, " ");
        rename_argument(get_last_command(expHead), var);
        return expHead;
    }
    return NULL;
}

/* Build arithmetic command combining two command sequences */
command* build_arithmetic_command(char op, char type, char* last, char* firstArgLast, char* secondArgLast, char firstType, char secondType, command* firstHead, command* secondHead) {
    command* head = NULL;
    var_node* symbol;
    if (firstType == genCharsArr[0].charCmd && secondType == genCharsArr[1].charCmd)
        firstHead = convert_to_float(firstHead, firstArgLast);
    else if (secondType == genCharsArr[0].charCmd && firstType == genCharsArr[1].charCmd)
        secondHead = convert_to_float(secondHead, secondArgLast);
    free_state(firstArgLast);
    free_state(secondArgLast);
    head = merege_comand(firstHead, secondHead);
    symbol = add_temp_var(type);
    strcpy(last, symbol->name);
    return build_math_operator_command(op, head, type, symbol->name, firstArgLast, secondArgLast);
}

/* Build math operator command (for +, -, /, *) */
command* build_math_operator_command(char op, command* head, char type,  char* firstArg,  char* secondArg,  char* thirdArg) {
    switch (op) {
        case '+':
            return translate_comand(head, type, operatorStrings[4], firstArg, secondArg, thirdArg);
        case '-':
            return translate_comand(head, type, operatorStrings[5], firstArg, secondArg, thirdArg);
        case '/':
            return translate_comand(head, type, operatorStrings[6], firstArg, secondArg, thirdArg);
        default:
            return translate_comand(head, type, operatorStrings[7], firstArg, secondArg, thirdArg);
    }
}

/* Build relational operator command */
command* build_relop_command(int relopType, char* firstVar, char* secondVar, command* firstHead, command* secondHead, char compareType) {
    printf("build relop !!\n");
    command* head;
    var_node* var;
    head = merege_comand(firstHead, secondHead);
    free_state(firstVar);
    free_state(secondVar);
    var = add_temp_var(genCharsArr[0].charCmd); /* temporary variable */
    switch (relopType) {
        case equal:
            head = translate_comand(head, compareType, operatorStrings[8], var->name, firstVar, secondVar);
            break;
        case notEqual:
            head = translate_comand(head, compareType, operatorStrings[9], var->name, firstVar, secondVar);
            break;
        case bigger:
            head = translate_comand(head, compareType, operatorStrings[10], var->name, firstVar, secondVar);
            break;
        case smaller:
            head = translate_comand(head, compareType, operatorStrings[11], var->name, firstVar, secondVar);
            break;
        case biggerOrEqual:
            head = translate_comand(head, compareType, operatorStrings[11], var->name, firstVar, secondVar);
            head = flip_command(head, var->name);
            break;
        case smallerOrEqual:
            head = translate_comand(head, compareType, operatorStrings[10], var->name, firstVar, secondVar);
            head = flip_command(head, var->name);
            break;
    }
    head = translate_comand(head, genCharsArr[5].charCmd, operatorStrings[12], " ", var->name, " ");
    free_state(var->name);
    return head;
}

/* Flip relational operator command */
command* flip_command(command* head, char* lastVar) {
    command* last = get_last_command(head);
    /* Compare using the charCmd field */
    if (!strcmp(last->com + 1, operatorStrings[8])) { // EQL
        *(last->com + 1) = genCharsArr[2].charCmd; // Change to 'N'
    }
    else if (!strcmp(last->com + 1, operatorStrings[9])) { // NQL
        *(last->com + 1) = genCharsArr[3].charCmd; // Change to 'E'
    }
    else {
        head = translate_comand(head, genCharsArr[0].charCmd, operatorStrings[5], lastVar, operatorStrings[0], lastVar);
    }
    return head;
}

/* Add a new label command */
command* add_label(command* head) {
    char buffer[ARGLEN];
    printf("adds label\n");
    labelsCount++;
    sprintf(buffer, "%d", labelsCount);
    return translate_comand(head, genCharsArr[4].charCmd, buffer, " ", " ", " ");
}

/* Convert a command’s last argument to float */
command* convert_to_float(command* head, char* last) {
    var_node* tempVar = add_temp_var(genCharsArr[1].charCmd);
    head = translate_comand(head, genCharsArr[0].charCmd, operatorStrings[1], tempVar->name, last, " ");
    free_state(last);
    strcpy(last, tempVar->name);
    return head;
}

/* Convert a command’s last argument to int */
command* convert_to_int(command* head, char* last) {
    var_node* tempVar = add_temp_var(genCharsArr[0].charCmd);
    head = translate_comand(head, genCharsArr[1].charCmd, operatorStrings[3], tempVar->name, last, " ");
    free_state(last);
    strcpy(last, tempVar->name);
    return head;
}

/* Decide resulting type from two types */
char type_decider(char type1, char type2) {
    if (type1 == genCharsArr[1].charCmd || type2 == genCharsArr[1].charCmd)
        return genCharsArr[1].charCmd;
    return genCharsArr[0].charCmd;
}

/* Returns cast code for a given cast operator */
int cast(int castOp) {
    int number = 0;
    switch (castOp) {
        case castToInt:
            number = 1;
            break;
        case castToFloat:
            number = 2;
            break;
        default:
            break;
    }
    return number;
}

/* Update command list: rename first argument of each command in the list */
void update_list_to_label(command_list* head, command* label) {
    command_list* next;
    while (head) {
        next = head->next;
        rename_argument(head->com, label->com);
        free(head);
        head = next;
    }
}

/* Rename a command’s first argument */
void rename_argument(command* com, char* newArg) {
    free_state(com->firstArg);
    sprintf(com->firstArg, "%s", newArg);
}

/* Print all commands from the linked list to the output file (quad) */
void command_print(command* head) {
    int commandsCounter = 1;
    int lables[LABELS] = {0};
    command* start = head;
    while (start) {
        if (*(start->com) == genCharsArr[4].charCmd) {
            lables[atoi(start->com + 1)] = commandsCounter;
        } else {
            ++commandsCounter;
        }
        start = start->next;
    }
    while (head) {
        if (*(head->com) != genCharsArr[4].charCmd) {
            if (*(head->firstArg) == genCharsArr[4].charCmd)
                sprintf(head->firstArg, "%d", lables[atoi(head->firstArg + 1)]);
            fprintf(quad, "%s\t%s\t%s\t%s\n", head->com, head->firstArg, head->secondArg, head->thirdArg);
        }
        head = head->next;
    }
}

/* Free all commands in the linked list */
void free_list(command *head) {
    command *current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

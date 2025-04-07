#include "translator.h"

chars CHAR0, CHAR1, CHAR2, CHAR3, CHAR4, CHAR5;
strings STR0, STR1, STR2, STR3, STR4, STR5, STR6, STR7, STR8, STR9, STR10, STR11, STR12, STR13;

/* Array of character commands, representing operation types:
 * 'I' for integer, 'R' for real (float), 'N' for not, 'E' for equal,
 * '*' for labels, 'J' for jumps.
 */
charCmd genChars[] = {
    {'I', &CHAR0}, /* Integer operations */
    {'R', &CHAR1}, /* Float operations */
    {'N', &CHAR2}, /* Logical NOT */
    {'E', &CHAR3}, /* Equality check */
    {'*', &CHAR4}, /* Label marker */
    {'J', &CHAR5}  /* Jump operations */
};

/* Array of string commands, representing specific operations:
 * "1" for constant 1, "TOR" for to real, "ASN" for assignment,
 * "TOI" for to integer, "ADD" for addition, etc.
 */
strCmd genStrings[] = {
    {"1", &STR1},    /* Constant 1 */
    {"TOR", &STR2},  /* Convert to real (float) */
    {"ASN", &STR3},  /* Assignment */
    {"TOI", &STR4},  /* Convert to integer */
    {"ADD", &STR5},  /* Addition */
    {"SUB", &STR6},  /* Subtraction */
    {"DIV", &STR7},  /* Division */
    {"MLT", &STR8},  /* Multiplication */
    {"EQL", &STR9},  /* Equality */
    {"NQL", &STR10}, /* Inequality */
    {"GRT", &STR11}, /* Greater than */
    {"LSS", &STR12}, /* Less than */
    {"MPZ", &STR13}  /* Possibly jump if zero */
};

/* Counter for the number of labels generated */
int labelsCount = 0;

/**
 * Merges two command lists by appending the second list to the first.
 * 
 * @param head The first command list.
 * @param tail The second command list to append.
 * @return The merged command list, or tail if head is NULL.
 */
command_list* merge_comnd_list(command_list* head, command_list* tail)
{
    command_list* last = head;
    if (!head)
        return tail;
    while (last->next)
        last = last->next;
    last->next = tail;
    return head;
}

/**
 * Prepends a new command to the beginning of a command list.
 * 
 * @param list The existing command list.
 * @param com The command to prepend.
 * @return The updated command list with the new command at the beginning.
 */
command_list* add_new_command_list(command_list* list, command* com)
{
    command_list* previous_comnd;
    if (!list)
    {
        list = (command_list*)malloc(sizeof(command_list));
        if (!list)
        {
            fprintf(stderr, "Error: Memory allocation failed for new command list.\n");
            return NULL; // Indicate failure
        }
        list->next = NULL;
        list->com = com;
        return list;
    }
    previous_comnd = (command_list*)malloc(sizeof(command_list));
    if (!previous_comnd)
    {
        fprintf(stderr, "Error: Memory allocation failed for new command list.\n");
        return list; // Return original list to avoid losing it
    }
    previous_comnd->next = list;
    previous_comnd->com = com;
    return previous_comnd;
}
/**
 * Merges two command sequences by appending the second to the first.
 * 
 * @param head The first command sequence.
 * @param tail The second command sequence to append.
 * @return The merged command sequence, or tail if head is NULL.
 */
command* merege_comand(command* head, command* tail)
{
    command* last_comnd;
    if (!head)
        return tail;
    last_comnd = get_last_command(head);
    last_comnd->next = tail;
    return head;
}

/**
 * Retrieves the last command in a command sequence.
 * 
 * @param head The head of the command sequence.
 * @return The last command in the sequence.
 */
command* get_last_command(command* head)
{
    command* last_comnd = head;
    while (last_comnd->next)
        last_comnd = last_comnd->next;
    return last_comnd;
}

/**
 * Creates a new command with the specified type, command string, and arguments,
 * and appends it to the existing command sequence.
 * 
 * @param head The existing command sequence.
 * @param type The type character (e.g., 'I', 'R').
 * @param com The command string (e.g., "ADD", "ASN").
 * @param firstArg The first argument.
 * @param secondArg The second argument.
 * @param thirdArg The third argument.
 * @return The updated command sequence with the new command appended.
 */
command* translate_comand(command* head, char type, char* com, char* firstArg, char* secondArg, char* thirdArg)
{
    command* new_comnd, *previous_comnd;
    if (!head)
    {
        head = (command*)malloc(sizeof(command));
        if (!head)
        {
            report_error(error_messeges[22]);
            return NULL;
        }
        new_comnd = head;
    }
    else
    {
        previous_comnd = get_last_command(head);
        new_comnd = (command*)malloc(sizeof(command));
        if (!new_comnd)
        {
           report_error(error_messeges[22]);
            return head;
        }
        previous_comnd->next = new_comnd;
    }
    sprintf(new_comnd->com, "%c%s", type, com);
    sprintf(new_comnd->firstArg, "%s", firstArg);
    sprintf(new_comnd->secondArg, "%s", secondArg);
    sprintf(new_comnd->thirdArg, "%s", thirdArg);
    new_comnd->next = NULL;
    return head;
}

/**
 * Creates an assignment command, handling type checking and conversions.
 * 
 * @param var The variable to assign to.
 * @param exp The expression to assign.
 * @param expType The type of the expression ('I' or 'R').
 * @param expHead The command sequence for the expression.
 * @return The command sequence for the assignment, or NULL on error.
 */
command* add_assign_commadn(char* var, char* exp, char expType, command* expHead)
{
    var_node* symbol = NULL;
    command* head = NULL;
    free_variable_state(exp); /* Free the expression variable’s state */

    if (!(symbol = search_variable(var)))
        report_error(error_messeges[4], var); /* Error: variable not found */
    else if (symbol->type == genChars[0].charCmd && expType == genChars[1].charCmd)
        report_error(error_messeges[18]); /* Error: cannot assign float to int */
    else
    {
        if (symbol->type == genChars[1].charCmd && expType == genChars[0].charCmd)
            /* Convert int to float for assignment to float variable */
            return translate_comand(expHead, genChars[0].charCmd, genStrings[1].stringCmd, var, exp, " ");
        if (!expHead)
            /* Create a new assignment command if no prior sequence exists */
            return translate_comand(NULL, symbol->type, genStrings[2].stringCmd, var, exp, " ");
        /* Rename the last command’s first argument to the variable */
        rename_argument(get_last_command(expHead), var);
        return expHead;
    }
    return NULL;
}

/**
 * Builds an arithmetic command, handling type conversions and temporary variables.
 * 
 * @param op The arithmetic operator (+, -, /, *).
 * @param type The result type ('I' or 'R').
 * @param last The variable to store the result.
 * @param firstArgLast The first operand.
 * @param secondArgLast The second operand.
 * @param firstType The type of the first operand.
 * @param secondType The type of the second operand.
 * @param firstHead The command sequence for the first operand.
 * @param secondHead The command sequence for the second operand.
 * @return The command sequence for the arithmetic operation.
 */
command* build_arithmetic_command(char op, char type, char* last, char* firstArgLast, char* secondArgLast, char firstType, char secondType, command* firstHead, command* secondHead)
{
    command* head = NULL;
    var_node* symbol;
    if (firstType == genChars[0].charCmd && secondType == genChars[1].charCmd)
        firstHead = convert_to_float(firstHead, firstArgLast); /* Convert int to float */
    else if (secondType == genChars[0].charCmd && firstType == genChars[1].charCmd)
        secondHead = convert_to_float(secondHead, secondArgLast); /* Convert int to float */
    free_variable_state(firstArgLast);
    free_variable_state(secondArgLast);
    head = merege_comand(firstHead, secondHead);
    symbol = add_temp_var(type);
    strcpy(last, symbol->name);
    return build_math_operator_command(op, head, type, symbol->name, firstArgLast, secondArgLast);
}

/**
 * Builds a math operator command based on the given operator.
 * 
 * @param op The operator (+, -, /, *).
 * @param head The existing command sequence.
 * @param type The type of the operation ('I' or 'R').
 * @param firstArg The result variable.
 * @param secondArg The first operand.
 * @param thirdArg The second operand.
 * @return The updated command sequence.
 */
command* build_math_operator_command(char op, command* head, char type, char* firstArg, char* secondArg, char* thirdArg)
{
    switch (op)
    {
    case '+':
        return translate_comand(head, type, genStrings[4].stringCmd, firstArg, secondArg, thirdArg); /* Addition */
    case '-':
        return translate_comand(head, type, genStrings[5].stringCmd, firstArg, secondArg, thirdArg); /* Subtraction */
    case '/':
        return translate_comand(head, type, genStrings[6].stringCmd, firstArg, secondArg, thirdArg); /* Division */
    default:
        return translate_comand(head, type, genStrings[7].stringCmd, firstArg, secondArg, thirdArg); /* Multiplication */
    }
}

/**
 * Builds a relational operator command with a jump based on the result.
 * 
 * @param relopType The type of relational operation (e.g., equal, notEqual).
 * @param firstVar The first variable.
 * @param secondVar The second variable.
 * @param firstHead The command sequence for the first variable.
 * @param secondHead The command sequence for the second variable.
 * @param compareType The type for comparison ('I' or 'R').
 * @return The command sequence for the relational operation.
 */
command* build_relop_command(int relopType, char* firstVar, char* secondVar, command* firstHead, command* secondHead, char compareType)
{
    command* head;
    var_node* var;
    head = merege_comand(firstHead, secondHead);
    free_variable_state(firstVar);
    free_variable_state(secondVar);
    var = add_temp_var(genChars[0].charCmd); /* Create integer temp var for result */
    switch (relopType)
    {
    case equal:
        head = translate_comand(head, compareType, genStrings[8].stringCmd, var->name, firstVar, secondVar); /* == */
        break;
    case notEqual:
        head = translate_comand(head, compareType, genStrings[9].stringCmd, var->name, firstVar, secondVar); /* != */
        break;
    case bigger:
        head = translate_comand(head, compareType, genStrings[10].stringCmd, var->name, firstVar, secondVar); /* > */
        break;
    case smaller:
        head = translate_comand(head, compareType, genStrings[11].stringCmd, var->name, firstVar, secondVar); /* < */
        break;
    case biggerOrEqual:
        head = translate_comand(head, compareType, genStrings[11].stringCmd, var->name, firstVar, secondVar); /* < flipped to >= */
        head = flip_command(head, var->name);
        break;
    case smallerOrEqual:
        head = translate_comand(head, compareType, genStrings[10].stringCmd, var->name, firstVar, secondVar); /* > flipped to <= */
        head = flip_command(head, var->name);
        break;
    }
    head = translate_comand(head, genChars[5].charCmd, genStrings[12].stringCmd, " ", var->name, " "); /* Jump if zero */
    free_variable_state(var->name);
    return head;
}

/**
 * Flips a relational command’s result (e.g., for >= or <=).
 * 
 * @param head The command sequence.
 * @param lastVar The variable whose value is flipped.
 * @return The updated command sequence.
 */
command* flip_command(command* head, char* lastVar)
{
    command* last = get_last_command(head);
    if (!strcmp(last->com + 1, genStrings[8].stringCmd)) { /* EQL (==) */
        *((last->com) + 1) = genChars[2].charCmd; /* Change to NQL (!=) */
    }
    else if (!strcmp(last->com + 1, genStrings[9].stringCmd)) { /* NQL (!=) */
        *((last->com) + 1) = genChars[3].charCmd; /* Change to EQL (==) */
    }
    else { /* For >= or <= */
        /*Cheadck: Flip by subtracting from 1 */
        head = translate_comand(head, genChars[0].charCmd, genStrings[5].stringCmd, lastVar, genStrings[0].stringCmd, lastVar);
    }
    return head;
}

/**
 * Adds a new label to the command sequence.
 * 
 * @param head The existing command sequence.
 * @return The updated command sequence with the new label.
 */
command* add_label(command* head)
{
    char buffer[ARGLEN];
    labelsCount++;
    sprintf(buffer, "%d", labelsCount);
    return translate_comand(head, genChars[4].charCmd, buffer, " ", " ", " ");
}

/**
 * Converts a variable to a float, generating a conversion command.
 * 
 * @param head The command sequence.
 * @param last The variable to convert.
 * @return The updated command sequence.
 */
command* convert_to_float(command* head, char* last)
{
    var_node* commandName;
    commandName = add_temp_var(genChars[1].charCmd); /* New float temp var */
    head = translate_comand(head, genChars[0].charCmd, genStrings[1].stringCmd, commandName->name, last, " ");
    free_variable_state(last);
    strcpy(last, commandName->name);
    return head;
}

/**
 * Converts a variable to an integer, generating a conversion command.
 * 
 * @param head The command sequence.
 * @param last The variable to convert.
 * @return The updated command sequence.
 */
command* convert_to_int(command* head, char* last)
{
    var_node* commandName;
    commandName = add_temp_var(genChars[0].charCmd); /* New int temp var */
    head = translate_comand(head, genChars[1].charCmd, genStrings[3].stringCmd, commandName->name, last, " ");
    free_variable_state(last);
    strcpy(last, commandName->name);
    return head;
}

/**
 * Determines the resulting type of an operation based on operand types.
 * 
 * @param type1 The first operand’s type ('I' or 'R').
 * @param type2 The second operand’s type ('I' or 'R').
 * @return 'R' if either operand is real, otherwise 'I'.
 */
char type_decider(char type1, char type2)
{
    return (type1 == 'R' || type2 == 'R') ? 'R' : 'I';
}

/**
 * Maps a cast operation to an integer code.
 * 
 * @param castOp The cast operation (castToInt or castToFloat).
 * @return 1 for castToInt, 2 for castToFloat, 0 otherwise.
 */
int cast(int castOp)
{
    int number = 0;
    switch (castOp)
    {
    case castToInt:
        number = 1;
        break;
    case castToFloat:
        number = 2;
        break;
    }
    return number;
}

/**
 * Updates a command list to point to a specific label.
 * 
 * @param head The command list.
 * @param label The label command to reference.
 */
void update_list_to_label(command_list* head, command* label)
{
    command_list* next;
    while (head)
    {
        next = head->next;
        rename_argument(head->com, label->com);
        free(head);
        head = next;
    }
}

/**
 * Renames the first argument of a command.
 * 
 * @param com The command to modify.
 * @param newArg The new argument value.
 */
void rename_argument(command* com, char* newArg)
{
    free_variable_state(com->firstArg);
    sprintf(com->firstArg, "%s", newArg);
}

/**
 * Prints the command sequence to the output file, resolving labels.
 * 
 * @param head The command sequence to print.
 */
void command_print(command* head)
{
    int commandsCounter = 1;
    int lables[LABELS];
    command* start = head;
    /* First pass: map labels to their positions */
    while (start)
    {
        if (*(start->com) == genChars[4].charCmd)
            lables[atoi(1 + start->com)] = commandsCounter;
        else
            ++commandsCounter;
        start = start->next;
    }
    /* Second pass: print commands, replacing label references */
    while (head)
    {
        if (*(head->com) != genChars[4].charCmd)
        {
            if (*(head->firstArg) == genChars[4].charCmd)
                sprintf(head->firstArg, "%d", lables[atoi(1 + head->firstArg)]);
            fprintf(quad, "%s\t%s\t%s\t%s\n", head->com, head->firstArg, head->secondArg, head->thirdArg);
        }
        head = head->next;
    }
}

/**
 * Frees the memory allocated for a command sequence.
 * 
 * @param head The head of the command sequence.
 */
void free_list(command* head)
{
    command* current = head;
    while (head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }
}
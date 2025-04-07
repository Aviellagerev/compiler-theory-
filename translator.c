#include "translator.h"




chars CHAR0, CHAR1, CHAR2, CHAR3, CHAR4, CHAR5;
strings STR0, STR1, STR2, STR3, STR4, STR5, STR6, STR7, STR8, STR9, STR10, STR11, STR12, STR13;

charCmd genChars[] = {
    {'I', &CHAR0}, /* int */
    {'R', &CHAR1}, /* float(real) */
    {'N', &CHAR2}, /* not */
    {'E', &CHAR3}, /* equal */
    {'*', &CHAR4}, /* temp number to add label */
    {'J', &CHAR5}  /* jump */
};

strCmd genStrings[] = {
    {"1", &STR1},    /* string 1 */
    {"TOR", &STR2},  /* string 2 */
    {"ASN", &STR3},  /* string 3 */
    {"TOI", &STR4},  /* string 4 */
    {"ADD", &STR5},  /* string 5 */
    {"SUB", &STR6},  /* string 6 */
    {"DIV", &STR7},  /* string 7 */
    {"MLT", &STR8},  /* string 8 */
    {"EQL", &STR9},  /* string 9 */
    {"NQL", &STR10}, /* string 10 */
    {"GRT", &STR11}, /* string 11 */
    {"LSS", &STR12}, /* string 12 */
    {"MPZ", &STR13}  /* string 13 */
};

int labelsCount = 0;

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

command_list* add_new_command_list(command_list* list, command* com)
{
    command_list* previous_comnd;
    if (!list)
    {
        list = (command_list*)malloc(sizeof(command_list));
        list->next = NULL;
        list->com = com;
        return list;
    }
    previous_comnd = (command_list*)malloc(sizeof(command_list));
    previous_comnd->next = list;
    previous_comnd->com = com;
    return previous_comnd;
}

command* merege_comand(command* head, command* tail)
{
    command* last_comnd;
    if (!head)
        return tail;
    last_comnd = get_last_command(head);
    last_comnd->next = tail;
    return head;
}

command* get_last_command(command* head)
{
    command* last_comnd = head;
    while (last_comnd->next)
        last_comnd = last_comnd->next;
    return last_comnd;
}

command* translate_comand(command* head, char type, char* com, char* firstArg, char* secondArg, char* thirdArg)
{
    command* new_comnd, *previous_comnd;
    if (!head)
    {
        head = (command*)malloc(sizeof(command));
        new_comnd = head;
    }
    else
    {
        previous_comnd = get_last_command(head);
        new_comnd = (command*)malloc(sizeof(command));
        previous_comnd->next = new_comnd;
    }
    sprintf(new_comnd->com, "%c%s", type, com);
    sprintf(new_comnd->firstArg, "%s", firstArg);
    sprintf(new_comnd->secondArg, "%s", secondArg);
    sprintf(new_comnd->thirdArg, "%s", thirdArg);
    new_comnd->next = NULL;
    return head;
}

command* add_assign_commadn(char* var, char* exp, char expType, command* expHead)
{
    var_node* symbol = NULL;
    command* head = NULL;
    free_state(exp);

    if (!(symbol = search_varible(var)))
        printf("ERROR: unknown variable, not defined in the symbol table\n");
    else if (symbol->type == genChars[0].charCmd && expType == genChars[1].charCmd)
        printf("cast from float to int ERROR!  \n");
    else
    {
        if (symbol->type == genChars[1].charCmd && expType == genChars[0].charCmd)
            return translate_comand(expHead, genChars[0].charCmd, genStrings[1].stringCmd, var, exp, " ");
        if (!expHead)
            return translate_comand(NULL, symbol->type, genStrings[2].stringCmd, var, exp, " ");
        rename_argument(get_last_command(expHead), var);
        return expHead;
    }
    return NULL;
}

command* build_arithmetic_command(char op, char type, char* last, char* firstArgLast, char* secondArgLast, char firstType, char secondType, command* firstHead, command* secondHead)
{
    command* head = NULL;
    var_node* symbol;
    if (firstType == genChars[0].charCmd && secondType == genChars[1].charCmd)
        firstHead = convert_to_float(firstHead, firstArgLast);
    else if (secondType == genChars[0].charCmd && firstType == genChars[1].charCmd)
        secondHead = convert_to_float(secondHead, secondArgLast);
    free_state(firstArgLast);
    free_state(secondArgLast);
    head = merege_comand(firstHead, secondHead);
    symbol = add_temp_var(type);
    strcpy(last, symbol->name);
    return build_math_operator_command(op, head, type, symbol->name, firstArgLast, secondArgLast);
}

command* build_math_operator_command(char op, command* head, char type, char* firstArg, char* secondArg, char* thirdArg)
{
    switch (op)
    {
    case '+':
        return translate_comand(head, type, genStrings[4].stringCmd, firstArg, secondArg, thirdArg);
    case '-':
        return translate_comand(head, type, genStrings[5].stringCmd, firstArg, secondArg, thirdArg);
    case '/':
        return translate_comand(head, type, genStrings[6].stringCmd, firstArg, secondArg, thirdArg);
    default:
        return translate_comand(head, type, genStrings[7].stringCmd, firstArg, secondArg, thirdArg);
    }
}

command* build_relop_command(int relopType, char* firstVar, char* secondVar, command* firstHead, command* secondHead, char compareType)
{
    command* head;
    var_node* var;
    head = merege_comand(firstHead, secondHead);
    free_state(firstVar);
    free_state(secondVar);
    var = add_temp_var(genChars[0].charCmd);
    switch (relopType)
    {
    case equal:
        head = translate_comand(head, compareType, genStrings[8].stringCmd, var->name, firstVar, secondVar);
        break;
    case notEqual:
        head = translate_comand(head, compareType, genStrings[9].stringCmd, var->name, firstVar, secondVar);
        break;
    case bigger:
        head = translate_comand(head, compareType, genStrings[10].stringCmd, var->name, firstVar, secondVar);
        break;
    case smaller:
        head = translate_comand(head, compareType, genStrings[11].stringCmd, var->name, firstVar, secondVar);
        break;
    case biggerOrEqual:
        head = translate_comand(head, compareType, genStrings[11].stringCmd, var->name, firstVar, secondVar);
        head = flip_command(head, var->name);
        break;
    case smallerOrEqual:
        head = translate_comand(head, compareType, genStrings[10].stringCmd, var->name, firstVar, secondVar);
        head = flip_command(head, var->name);
        break;
    }
    head = translate_comand(head, genChars[5].charCmd, genStrings[12].stringCmd, " ", var->name, " ");
    free_state(var->name);
    return head;
}

command* flip_command(command* head, char* lastVar)
{
    command* last = get_last_command(head);
    if (!strcmp(last->com + 1, genStrings[8].stringCmd)) { // EQL (==)
        *((last->com) + 1) = genChars[2].charCmd; // Change to NQL (!=)
    }
    else if (!strcmp(last->com + 1, genStrings[9].stringCmd)) { // NQL (!=)
        *((last->com) + 1) = genChars[3].charCmd; // Change to EQL (==)
    }
    else { // For >= or <=
        head = translate_comand(head, genChars[0].charCmd, genStrings[5].stringCmd, lastVar, genStrings[0].stringCmd, lastVar);
    }
    return head;
}

command* add_label(command* head)
{
    char buffer[ARGLEN];
    labelsCount++;
    sprintf(buffer, "%d", labelsCount);
    return translate_comand(head, genChars[4].charCmd, buffer, " ", " ", " ");
}

command* convert_to_float(command* head, char* last)
{
    var_node* commandName;
    commandName = add_temp_var(genChars[1].charCmd);
    head = translate_comand(head, genChars[0].charCmd, genStrings[1].stringCmd, commandName->name, last, " ");
    free_state(last);
    strcpy(last, commandName->name);
    return head;
}

command* convert_to_int(command* head, char* last)
{
    var_node* commandName;
    commandName = add_temp_var(genChars[0].charCmd);
    head = translate_comand(head, genChars[1].charCmd, genStrings[3].stringCmd, commandName->name, last, " ");
    free_state(last);
    strcpy(last, commandName->name);
    return head;
}

char type_decider(char type1, char type2)
{
    return (type1 == 'R' || type2 == 'R') ? 'R' : 'I';
}

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

void rename_argument(command* com, char* newArg)
{
    free_state(com->firstArg);
    sprintf(com->firstArg, "%s", newArg);
}

void command_print(command* head)
{
    int commandsCounter = 1;
    int lables[LABELS];
    command* start = head;
    while (start)
    {
        if (*(start->com) == genChars[4].charCmd)
            lables[atoi(1 + start->com)] = commandsCounter;
        else
            ++commandsCounter;
        start = start->next;
    }
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
#include "translator.h"

chars CHAR0, CHAR1, CHAR2, CHAR3, CHAR4, CHAR5;
strings STR0, STR1, STR2, STR3, STR4, STR5, STR6, STR7, STR8, STR9, STR10, STR11, STR12, STR13;

/* Array of character commands, representing operation types:
 * 'I' for integer, 'R' for real (float), 'N' for not, 'E' for equal,
 * '*' for labels, 'J' for jumps.
 */
char_command_struct op_array_char[] = {
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
string_command_struct op_array_string[] = {
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
            report_error(error_messeges[22]);
            return NULL; // Indicate failure
        }
        list->next = NULL;
        list->com = com;
        return list;
    }
    previous_comnd = (command_list*)malloc(sizeof(command_list));
    if (!previous_comnd)
    {
       report_error(error_messeges[22]);
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
 * @param first_argument The first argument.
 * @param second_argument The second argument.
 * @param third_argument The third argument.
 * @return The updated command sequence with the new command appended.
 */
command* translate_comand(command* head, char type, char* com, char* first_argument, char* second_argument, char* third_argument)
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
    sprintf(new_comnd->first_argument, "%s", first_argument);
    sprintf(new_comnd->second_argument, "%s", second_argument);
    sprintf(new_comnd->third_argument, "%s", third_argument);
    new_comnd->next = NULL;
    return head;
}

/**
 * Creates an assignment command, handling type checking and conversions.
 * 
 * @param var The variable to assign to.
 * @param exp The expression to assign.
 * @param expression_type The type of the expression ('I' or 'R').
 * @param expression_head The command sequence for the expression.
 * @return The command sequence for the assignment, or NULL on error.
 */
command* add_assign_commadn(char* var, char* exp, char expression_type, command* expression_head)
{
    var_node* symbol = NULL;
    command* head = NULL;
    free_variable_state(exp); /* Free the expression variable’s state */

    if (!(symbol = search_variable(var)))
        report_error(error_messeges[4], var); /* Error: variable not found */
    else if (symbol->type == op_array_char[0].char_command && expression_type == op_array_char[1].char_command)
        report_error(error_messeges[18]); /* Error: cannot assign float to int */
    else
    {
        if (symbol->type == op_array_char[1].char_command && expression_type == op_array_char[0].char_command)
            /* Convert int to float for assignment to float variable */
            return translate_comand(expression_head, op_array_char[0].char_command, op_array_string[1].string_command, var, exp, " ");
        if (!expression_head)
            /* Create a new assignment command if no prior sequence exists */
            return translate_comand(NULL, symbol->type, op_array_string[2].string_command, var, exp, " ");
        /* Rename the last command’s first argument to the variable */
        rename_argument(get_last_command(expression_head), var);
        return expression_head;
    }
    return NULL;
}

/**
 * Builds an arithmetic command, handling type conversions and temporary variables.
 * 
 * @param op The arithmetic operator (+, -, /, *).
 * @param type The result type ('I' or 'R').
 * @param last The variable to store the result.
 * @param first_argumentLast The first operand.
 * @param second_argumentLast The second operand.
 * @param first_type The type of the first operand.
 * @param second_type The type of the second operand.
 * @param first_head The command sequence for the first operand.
 * @param second_head The command sequence for the second operand.
 * @return The command sequence for the arithmetic operation.
 */
command* build_arithmetic_command(char op, char type, char* last, char* first_argumentLast, char* second_argumentLast, char first_type, char second_type, command* first_head, command* second_head)
{
    command* head = NULL;
    var_node* symbol;
    if (first_type == op_array_char[0].char_command && second_type == op_array_char[1].char_command)
        first_head = convert_to_float(first_head, first_argumentLast); /* Convert int to float */
    else if (second_type == op_array_char[0].char_command && first_type == op_array_char[1].char_command)
        second_head = convert_to_float(second_head, second_argumentLast); /* Convert int to float */
    free_variable_state(first_argumentLast);
    free_variable_state(second_argumentLast);
    head = merege_comand(first_head, second_head);
    symbol = add_temp_var(type);
    strcpy(last, symbol->name);
    return build_math_operator_command(op, head, type, symbol->name, first_argumentLast, second_argumentLast);
}

/**
 * Builds a math operator command based on the given operator.
 * 
 * @param op The operator (+, -, /, *).
 * @param head The existing command sequence.
 * @param type The type of the operation ('I' or 'R').
 * @param first_argument The result variable.
 * @param second_argument The first operand.
 * @param third_argument The second operand.
 * @return The updated command sequence.
 */
command* build_math_operator_command(char op, command* head, char type, char* first_argument, char* second_argument, char* third_argument)
{
    switch (op)
    {
    case '+':
        return translate_comand(head, type, op_array_string[4].string_command, first_argument, second_argument, third_argument); /* Addition */
    case '-':
        return translate_comand(head, type, op_array_string[5].string_command, first_argument, second_argument, third_argument); /* Subtraction */
    case '/':
        return translate_comand(head, type, op_array_string[6].string_command, first_argument, second_argument, third_argument); /* Division */
    default:
        return translate_comand(head, type, op_array_string[7].string_command, first_argument, second_argument, third_argument); /* Multiplication */
    }
}

/**
 * Builds a relational operator command with a jump based on the result.
 * 
 * @param relation_op_type The type of relational operation (e.g., equal, notEqual).
 * @param first_varible The first variable.
 * @param second_varible The second variable.
 * @param first_head The command sequence for the first variable.
 * @param second_head The command sequence for the second variable.
 * @param cmp_types The type for comparison ('I' or 'R').
 * @return The command sequence for the relational operation.
 */
command* build_relop_command(int relation_op_type, char* first_varible, char* second_varible, command* first_head, command* second_head, char cmp_types)
{
    command* head;
    var_node* var;
    head = merege_comand(first_head, second_head);
    free_variable_state(first_varible);
    free_variable_state(second_varible);
    var = add_temp_var(op_array_char[0].char_command); /* Create integer temp var for result */
    switch (relation_op_type)
    {
    case equal:
        head = translate_comand(head, cmp_types, op_array_string[8].string_command, var->name, first_varible, second_varible); /* == */
        break;
    case notEqual:
        head = translate_comand(head, cmp_types, op_array_string[9].string_command, var->name, first_varible, second_varible); /* != */
        break;
    case bigger:
        head = translate_comand(head, cmp_types, op_array_string[10].string_command, var->name, first_varible, second_varible); /* > */
        break;
    case smaller:
        head = translate_comand(head, cmp_types, op_array_string[11].string_command, var->name, first_varible, second_varible); /* < */
        break;
    case biggerOrEqual:
        head = translate_comand(head, cmp_types, op_array_string[11].string_command, var->name, first_varible, second_varible); /* < flipped to >= */
        head = flip_command(head, var->name);
        break;
    case smallerOrEqual:
        head = translate_comand(head, cmp_types, op_array_string[10].string_command, var->name, first_varible, second_varible); /* > flipped to <= */
        head = flip_command(head, var->name);
        break;
    }
    head = translate_comand(head, op_array_char[5].char_command, op_array_string[12].string_command, " ", var->name, " "); /* Jump if zero */
    free_variable_state(var->name);
    return head;
}

/**
 * Flips a relational command’s result (e.g., for >= or <=).
 * 
 * @param head The command sequence.
 * @param last_varible The variable whose value is flipped.
 * @return The updated command sequence.
 */
command* flip_command(command* head, char* last_varible)
{
    command* last = get_last_command(head);
    if (!strcmp(last->com + 1, op_array_string[8].string_command)) { /* EQL (==) */
        *((last->com) + 1) = op_array_char[2].char_command; /* Change to NQL (!=) */
    }
    else if (!strcmp(last->com + 1, op_array_string[9].string_command)) { /* NQL (!=) */
        *((last->com) + 1) = op_array_char[3].char_command; /* Change to EQL (==) */
    }
    else { /* For >= or <= */
        /*Cheadck: Flip by subtracting from 1 */
        head = translate_comand(head, op_array_char[0].char_command, op_array_string[5].string_command, last_varible, op_array_string[0].string_command, last_varible);
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
    return translate_comand(head, op_array_char[4].char_command, buffer, " ", " ", " ");
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
    var_node* command_name;
    command_name = add_temp_var(op_array_char[1].char_command); /* New float temp var */
    head = translate_comand(head, op_array_char[0].char_command, op_array_string[1].string_command, command_name->name, last, " ");
    free_variable_state(last);
    strcpy(last, command_name->name);
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
    var_node* command_name;
    command_name = add_temp_var(op_array_char[0].char_command); /* New int temp var */
    head = translate_comand(head, op_array_char[1].char_command, op_array_string[3].string_command, command_name->name, last, " ");
    free_variable_state(last);
    strcpy(last, command_name->name);
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
 * @param cast_operation The cast operation (castToInt or castToFloat).
 * @return 1 for castToInt, 2 for castToFloat, 0 otherwise.
 */
int cast(int cast_operation)
{
    int number = 0;
    switch (cast_operation)
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
    free_variable_state(com->first_argument);
    sprintf(com->first_argument, "%s", newArg);
}

/**
 * Prints the command sequence to the output file, resolving labels.
 * 
 * @param head The command sequence to print.
 */
void command_print(command* head)
{
    int cmd_counter = 1;
    int lables[LABELS];
    command* start = head;
    /* First pass: map labels to their positions */
    while (start)
    {
        if (*(start->com) == op_array_char[4].char_command)
            lables[atoi(1 + start->com)] = cmd_counter;
        else
            ++cmd_counter;
        start = start->next;
    }
    /* Second pass: print commands, replacing label references */
    while (head)
    {
        if (*(head->com) != op_array_char[4].char_command)
        {
            if (*(head->first_argument) == op_array_char[4].char_command)
                sprintf(head->first_argument, "%d", lables[atoi(1 + head->first_argument)]);
            fprintf(quad, "%s\t%s\t%s\t%s\n", head->com, head->first_argument, head->second_argument, head->third_argument);
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

#include "monty.h"
#include <string.h>

void free_tokens(void);
unsigned int token_arr_len(void);
int is_empty_line(char *line, char *delims);
void (*get_op_func(char *opcode))(stack_t**, unsigned int);
int run_monty(FILE *script_fd);

/**
 * free_tokens -its frees the global op_toks array of strings
 */
void free_tokens(void)
{
	size_t i = 0;

	if (op_toks == NULL)
		return;

	for (i = 0; op_toks[i]; i++)
		free(op_toks[i]);

	free(op_toks);
}

/**
 * token_arr_len -its gets the length of current op_toks
 *
 * Return:the length of current op_toks (as int)
 */
unsigned int token_arr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * is_empty_line -its checks if a line read from getline only contains delimiters
 * @line: the pointer to the line
 * @delims: string of delimiter characters
 *
 * Return: If  the line contains only delimiters - 1
 *         Otherwise - 0
 */
int is_empty_line(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * get_op_func -its matches an opcode with its corresponding function
 * @opcode opcode to match
 *
 * Return: the pointer to the corresponding function
 */
void (*get_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", monty_push},
		{"pall", monty_pall},
		{"pint", monty_pint},
		{"pop", monty_pop},
		{"swap", monty_swap},
		{"add", monty_add},
		{"nop", monty_nop},
		{"sub", monty_sub},
		{"div", monty_div},
		{"mul", monty_mul},
		{"mod", monty_mod},
		{"pchar", monty_pchar},
		{"pstr", monty_pstr},
		{"rotl", monty_rotl},
		{"rotr", monty_rotr},
		{"stack", monty_stack},
		{"queue", monty_queue},
		{NULL, NULL}
	};
	int i;

	for (i = 0; op_funcs[i].opcode; i++)
	{
		if (strcmp(opcode, op_funcs[i].opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
}

#define MAX_LINE_LENGTH 1024  /* Choose an appropriate maximum line length */

/**
 * run_monty - The primary function to execute a Monty bytecodes script.
 * @script_fd: The file descriptor for the open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, error code on failure.
 */
int run_monty(FILE *script_fd)
{
    stack_t *stack = NULL;
    char line[MAX_LINE_LENGTH];
    size_t len;
    int exit_status = EXIT_SUCCESS;
    unsigned int line_number = 0;
    void (*op_func)(stack_t**, unsigned int);
    unsigned int prev_tok_len = 0;

    if (init_stack(&stack) == EXIT_FAILURE)
        return (EXIT_FAILURE);

    while (fgets(line, sizeof(line), script_fd) != NULL)
    {
        line_number++;

        /* Remove trailing newline character, if present */
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        op_toks = strtow(line, DELIMS);
        if (op_toks == NULL)
        {
            if (is_empty_line(line, DELIMS))
                continue;
            free_stack(&stack);
            return (malloc_error());
        }
        else if (op_toks[0][0] == '#') /* Comment line */
        {
            free_tokens();
            continue;
        }
        op_func = get_op_func(op_toks[0]);
        if (op_func == NULL)
        {
            free_stack(&stack);
            exit_status = unknown_op_error(op_toks[0], line_number);
            free_tokens();
            break;
        }
        prev_tok_len = token_arr_len();
        op_func(&stack, line_number);
        if (token_arr_len() != prev_tok_len)
        {
            if (op_toks && op_toks[prev_tok_len])
                exit_status = atoi(op_toks[prev_tok_len]);
            else
                exit_status = EXIT_FAILURE;
            free_tokens();
            break;
        }
        free_tokens();
    }
    free_stack(&stack);

    if (line[0] == '\0')
        return (malloc_error());

    return (exit_status);
}

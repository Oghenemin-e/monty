#include "monty.h"
#include <string.h>

void free_stack(stack_t **stack);
int init_stack(stack_t **stack);
int check_mode(stack_t *stack);

/**
 * free_stack -its frees a stack_t stack
 * @stack: the pointer to the top (stack) or
 *         bottom (queue) of a stack_t
 */
void free_stack(stack_t **stack)
{
	stack_t *tmp = *stack;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

/**
 * init_stack -its initializes a stack_t stack with beginning
 *              stack and ending queue nodes
 * @stack: the pointer to an unitialized stack_t stack
 *
 * Return: if an error occurs - EXIT_FAILURE
 *         Otherwise - EXIT_SUCCESS
 */
int init_stack(stack_t **stack)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (s == NULL)
		return (malloc_error());

	s->n = STACK;
	s->prev = NULL;
	s->next = NULL;

	*stack = s;

	return (EXIT_SUCCESS);
}

/**
 * check_mode -its checks if a stack_t linked list is in stack or queue mode
 * @stack: the pointer to the top (stack) or bottom (queue)
 *         of a stack_t linked list
 *
 * Return: if the stack_t is in stack mode - STACK (0)
 *         if the stack_t is in queue mode - QUEUE (1)
 *         Otherwise - 2
 */
int check_mode(stack_t *stack)
{
	if (stack->n == STACK)
		return (STACK);
	else if (stack->n == QUEUE)
		return (QUEUE);
	return (2);
}

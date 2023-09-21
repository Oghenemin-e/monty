#include "monty.h"

void monty_rotl(stack_t **stack, unsigned int line_number);
void monty_rotr(stack_t **stack, unsigned int line_number);
void monty_stack(stack_t **stack, unsigned int line_number);
void monty_queue(stack_t **stack, unsigned int line_number);

/**
 * monty_rotl -its rotates the top value of the stack_t linked list to the bottom
 * @stack: the pointer to the top mode node of the stack_t linked list
 * @line_number: current working line number of a Monty bytecodes file
 */
void monty_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top, *bottom;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
		return;

	top = (*stack)->next;
	bottom = (*stack)->next;
	while (bottom->next != NULL)
		bottom = bottom->next;

	top->next->prev = *stack;
	(*stack)->next = top->next;
	bottom->next = top;
	top->next = NULL;
	top->prev = bottom;

	(void)line_number;
}

/**
 * monty_rotr -its rotates the bottom value of the stack_t linked list to the top
 * @stack: the pointer to the top mode node of a stack_t linked list
 * @line_number: current working line number of a Monty bytecodes file
 */
void monty_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *top, *bottom;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
		return;

	top = (*stack)->next;
	bottom = (*stack)->next;
	while (bottom->next != NULL)
		bottom = bottom->next;

	bottom->prev->next = NULL;
	(*stack)->next = bottom;
	bottom->prev = *stack;
	bottom->next = top;
	top->prev = bottom;

	(void)line_number;
}

/**
 * monty_stack -its converts the queue to a stack.
 * @stack: the pointer to the top mode node of the stack_t linked list
 * @line_number: current working line number of a Monty bytecodes file
 */
void monty_stack(stack_t **stack, unsigned int line_number)
{
	(*stack)->n = STACK;
	(void)line_number;
}

/**
 * monty_queue -its converts a stack to a queue
 * @stack: the pointer to the top mode node of the stack_t linked list
 * @line_number: current working line number of a Monty bytecodes file
 */
void monty_queue(stack_t **stack, unsigned int line_number)
{
	(*stack)->n = QUEUE;
	(void)line_number;
}


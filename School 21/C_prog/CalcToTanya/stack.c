#include "stack.h"

int_stack** int_stack_push(int_stack** stack, int elem) {
  int_node* new_elem = (int_node*)malloc(sizeof(int_node));
  new_elem->value = elem;
  new_elem->next = *stack;
  *stack = new_elem;
  return stack;
}

int int_stack_pop(int_stack** stack) {
  int_node* currNode = *stack;
  *stack = (*stack)->next;
  int pop = currNode->value;
  free(currNode);
  return pop;
}

int int_stack_top(int_stack* stack) {
  if (stack == NULL) {
    return -1;
  } else {
    return stack->value;
  }
}

double_stack** double_stack_push(double_stack** stack, double elem) {
  double_node* new_elem = (double_node*)malloc(sizeof(double_node));
  new_elem->value = elem;
  new_elem->next = *stack;
  *stack = new_elem;
  return stack;
}

double double_stack_pop(double_stack** stack) {
  double_node* currNode = *stack;
  *stack = (*stack)->next;
  double pop = currNode->value;
  free(currNode);
  return pop;
}

double double_stack_top(double_stack* stack) {
  if (stack == NULL) {
    return -1.212121;
  } else {
    return stack->value;
  }
}

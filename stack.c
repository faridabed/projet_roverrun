//
// Created by flasque on 19/10/2024.
//
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "stack.h"

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack* createStack(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_stack* stack = NULL;
    stack = malloc(sizeof (t_stack));
    stack->size = size;
    stack->nbElts = 0;
    stack->values = (int *)malloc(size * sizeof(int));
    if (stack->values == NULL ) {
        printf("Erreur d'allocation dynamique\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}


/**
 * @brief Function to push a value in the stack
 * @param stack : the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack* p_stack, int value){
    // the stack must not be full
    /*if(p_stack->nbElts == p_stack->size) {
        printf("stack is full ");
        exit(EXIT_FAILURE);
    }else {*/
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
}



/**
 * @brief Function to pop a value from the stack
 * @param stack : the stack
 * @return the value popped
 */
int pop(t_stack *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
int top(t_stack* stack)
{
    // the stack must not be empty
    /*  if(stack.nbElts == 0 ) {
          printf("stack is empty ");
          exit(EXIT_FAILURE);
      }
  */
    assert(stack->nbElts > 0);
    return stack->values[stack->nbElts - 1];
}

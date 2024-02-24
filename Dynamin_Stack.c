#include "Dynamin_Stack.h"
#include <stdio.h>
#define stack_DEBUG

stack_status_t stack_full(stack_ds_t *my_stack);
stack_status_t stack_empty(stack_ds_t *my_stack);

/**
 * @brief Creates a new stack with the specified maximum size.
 * 
 * This function dynamically allocates memory for a new stack structure 
 * and initializes its attributes. The maximum size of the stack is 
 * specified by the parameter max_size. The status of the operation 
 * is returned through the parameter ret_stack.
 * 
 * @param max_size The maximum size of the stack.
 * @param ret_stack Pointer to a stack_status_t where the status 
 *                  of the operation will be stored.
 *                  Possible values are:
 *                  - STACK_OK: Operation succeeded.
 *                  - STACK_NULL_POINTER: Invalid pointer.
 * 
 * @return Pointer to the newly created stack structure if successful, 
 *         otherwise NULL.
 */
stack_ds_t *create_stack(unsigned int max_size, stack_status_t *ret_stack)
{
    stack_ds_t *my_stack = NULL;

    if (NULL == ret_stack)
    {
        *ret_stack = STACK_NULL_POINTER;
        my_stack = NULL;
    }
    else
    {
        my_stack = (stack_ds_t*) malloc(max_size * sizeof(stack_ds_t));
        if (NULL == my_stack)
        {
            *ret_stack = STACK_NULL_POINTER;
            my_stack = NULL;
        }
        else
        {
            my_stack->stack_top = -1;
            my_stack->max_size = max_size;
            my_stack->stack_count = ZERO;
            my_stack->stack_array = (void**) calloc(max_size, sizeof(void*));
            if (NULL == my_stack->stack_array)
            {
                *ret_stack = STACK_NULL_POINTER;
                my_stack = NULL;
            }
            else
            {
                *ret_stack = STACK_OK;
            }
        }
    }
    return my_stack;
}

/**
 * @brief Destroys the stack and releases allocated memory.
 * 
 * This function deallocates memory associated with the specified stack 
 * and sets the stack pointer to NULL. The status of the operation 
 * is returned through the parameter ret_stack.
 * 
 * @param my_stack Pointer to the stack structure.
 * @param ret_stack Pointer to a stack_status_t where the status 
 *                  of the operation will be stored.
 *                  Possible values are:
 *                  - STACK_OK: Operation succeeded.
 *                  - STACK_NULL_POINTER: Invalid pointer.
 */
stack_ds_t *destroy_stack(stack_ds_t *my_stack, stack_status_t *ret_stack)
{
    if (NULL == my_stack || NULL == ret_stack)
    {
        ret_stack = STACK_NULL_POINTER;
    }
    else
    {
        free(my_stack->stack_array);
        free(my_stack);
        *ret_stack = STACK_OK;
    }
    return NULL;
}

/**
 * @brief Inserts an element onto the top of the stack.
 * 
 * This function inserts the specified element onto the top of the stack.
 * If the stack is full, the operation fails, and the appropriate status 
 * code is returned.
 * 
 * @param my_stack Pointer to the stack structure.
 * @param element Pointer to the element to be inserted.
 * 
 * @return stack_status_t indicating the status of the operation.
 */
stack_status_t push_stack(stack_ds_t *my_stack, void *element)
{
    stack_status_t ret = STACK_NOT_OK;

    if (NULL == my_stack || NULL == element)
    {
        ret = STACK_NULL_POINTER;
    }
    else
    {
        if (STACK_FULL == stack_full(my_stack))
        {
            ret = STACK_FULL;
        }
        else
        {
            my_stack->stack_top++;
            my_stack->stack_array[my_stack->stack_top] = element;
            my_stack->stack_count++;
            ret = STACK_OK;
        }
    }
    return ret;
}

/**
 * @brief Removes and returns the element at the top of the stack.
 * 
 * This function removes and returns the element at the top of the stack.
 * If the stack is empty, the operation fails, and the appropriate status 
 * code is returned.
 * 
 * @param my_stack Pointer to the stack structure.
 * @param ret_stack Pointer to a stack_status_t where the status 
 *                  of the operation will be stored.
 *                  Possible values are:
 *                  - STACK_OK: Operation succeeded.
 *                  - STACK_NULL_POINTER: Invalid pointer.
 *                  - STACK_EMPTY: Stack is empty.
 * 
 * @return Pointer to the removed element if successful, 
 *         otherwise NULL.
 */
void *pop_stack(stack_ds_t *my_stack, stack_status_t *ret_stack)
{
    void *ptr = NULL;
    *ret_stack = STACK_NOT_OK;

    if (NULL == my_stack || NULL == ret_stack)
    {
        *ret_stack = STACK_NULL_POINTER;
    }
    else
    {
        if (STACK_EMPTY == stack_empty(my_stack))
        {
            *ret_stack = STACK_EMPTY;
        }
        else
        {
            ptr = my_stack->stack_array[my_stack->stack_top];
            my_stack->stack_top--;
            my_stack->stack_count--;
            *ret_stack = STACK_OK;
        }
    }
    return ptr;
}

/**
 * @brief Returns the element at the top of the stack without removing it.
 * 
 * This function returns the element at the top of the stack without removing it.
 * If the stack is empty, the operation fails, and the appropriate status 
 * code is returned.
 * 
 * @param my_stack Pointer to the stack structure.
 * @param ret_stack Pointer to a stack_status_t where the status 
 *                  of the operation will be stored.
 *                  Possible values are:
 *                  - STACK_OK: Operation succeeded.
 *                  - STACK_NULL_POINTER: Invalid pointer.
 *                  - STACK_EMPTY: Stack is empty.
 * 
 * @return Pointer to the element at the top of the stack if successful, 
 *         otherwise NULL.
 */
void *stack_top(stack_ds_t *my_stack, stack_status_t *ret_stack)
{
    void *ptr = NULL;
    *ret_stack = STACK_NOT_OK;

    if (NULL == my_stack || NULL == ret_stack)
    {
        *ret_stack = STACK_NULL_POINTER;
    }
    else
    {
        if (STACK_EMPTY == stack_empty(my_stack))
        {
            *ret_stack = STACK_EMPTY;
        }
        else
        {
            ptr = my_stack->stack_array[my_stack->stack_top];
            *ret_stack = STACK_OK;
        }
    }
    return ptr;
}

/**
 * @brief Returns the current count of elements in the stack.
 * 
 * This function returns the current count of elements in the stack.
 * 
 * @param my_stack Pointer to the stack structure.
 * @param stack_count Pointer to an unsigned integer where the count 
 *                    of elements will be stored.
 * 
 * @return stack_status_t indicating the status of the operation.
 */
stack_status_t stack_count(stack_ds_t *my_stack, unsigned int *stack_count)
{
    stack_status_t ret = STACK_NOT_OK;

    if (NULL == my_stack || NULL == stack_count)
    {
        ret = STACK_NULL_POINTER;
    }
    else
    {
        *stack_count = my_stack->stack_count;
        ret = STACK_OK;
    }
    return ret;
}

/**
 * @brief Checks if the stack is full.
 * 
 * This function checks if the stack is full.
 * 
 * @param my_stack Pointer to the stack structure.
 * 
 * @return stack_status_t indicating the status of the operation.
 */
stack_status_t stack_full(stack_ds_t *my_stack)
{
    stack_status_t ret = STACK_NOT_OK;

    if (my_stack->stack_count == my_stack->max_size)
    {
        ret = STACK_FULL;
    }
    else
    {
        ret = STACK_OK;
    }
    return ret;
}

/**
 * @brief Checks if the stack is empty.
 * 
 * This function checks if the stack is empty.
 * 
 * @param my_stack Pointer to the stack structure.
 * 
 * @return stack_status_t indicating the status of the operation.
 */
stack_status_t stack_empty(stack_ds_t *my_stack)
{
    stack_status_t ret = STACK_NOT_OK;

    if (-1 == my_stack->stack_top)
    {
        ret = STACK_EMPTY;
    }
    else
    {
        ret = STACK_OK;
    }
    return ret;
}

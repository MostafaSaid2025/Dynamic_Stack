#include "Dynamin_Stack.h"
#include <stdio.h>
#define stack_DEBUG

stack_status_t stack_full(stack_ds_t *my_stack);
stack_status_t stack_empty(stack_ds_t *my_stack);


stack_ds_t *create_stack  (unsigned int max_size, stack_status_t *ret_stack)
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
                #ifdef stack_DEBUG
                printf("Stack has been created\n");
                #endif // stack_DEBUG
                *ret_stack = STACK_OK;
            }
        }

    }
    return my_stack;
}
stack_ds_t *destroy_stack (stack_ds_t *my_stack, stack_status_t *ret_stack)
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
        #ifdef stack_DEBUG
        printf("Stack has been destroyed\n");
        #endif // stack_DEBUG
    }
    return NULL;
}
stack_status_t push_stack (stack_ds_t *my_stack, void *element)
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
            #ifdef stack_DEBUG
            printf("Pushing done successfully\n");
            #endif // stack_DEBUG
        }

    }
    return ret;

}
void *pop_stack(stack_ds_t *my_stack , stack_status_t *ret_stack)
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
            ptr =  my_stack->stack_array[my_stack->stack_top];
            my_stack->stack_top--;
            my_stack->stack_count--;
            *ret_stack = STACK_OK;
            #ifdef stack_DEBUG
            printf("Poping done successfully\n");
            #endif // stack_DEBUG
        }
    }
    return ptr ;
}
void *stack_top  (stack_ds_t *my_stack, stack_status_t *ret_stack)
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
            ptr =  my_stack->stack_array[my_stack->stack_top];
            *ret_stack = STACK_OK;
            #ifdef stack_DEBUG
            printf("top done successfully\n");
            #endif // stack_DEBUG
        }
    }
    return ptr ;
}
stack_status_t stack_count  (stack_ds_t *my_stack, unsigned int *stack_count)
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
stack_status_t stack_full(stack_ds_t *my_stack)
{
    stack_status_t ret = STACK_NOT_OK;
    if (my_stack->stack_count == my_stack->max_size)
    {
        ret = STACK_FULL;
        #ifdef stack_DEBUG
        printf("Stack is Full\n");
        #endif // stack_DEBUG
    }
    else
    {
        ret = STACK_OK;
    }
    return ret;
}
stack_status_t stack_empty(stack_ds_t *my_stack)
{
    stack_status_t ret = STACK_NOT_OK;
    if (-1 == my_stack->stack_top)
    {
        ret = STACK_EMPTY;
        #ifdef stack_DEBUG
        printf("Stack is empty\n");
        #endif // stack_DEBUG
    }
    else
    {
        ret = STACK_OK;
    }
    return ret;
}

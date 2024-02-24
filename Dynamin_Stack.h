#ifndef _DYNAMIC_STACK_H
#define _DYNAMIC_STACK_H

#define ZERO 0

typedef struct stack_ds
{
   void **stack_array;
   signed int stack_top;
   unsigned int max_size;
   unsigned int stack_count;

}stack_ds_t;

typedef enum stack_status
{
   STACK_EMPTY = 0,
   STACK_FULL,
   STACK_NOT_OK,
   STACK_OK,
   STACK_NULL_POINTER,

}stack_status_t;

stack_ds_t *create_stack  (unsigned int max_size , stack_status_t *ret_stack);
stack_ds_t *destroy_stack (stack_ds_t *my_stack , stack_status_t *ret_stack);
stack_status_t push_stack (stack_ds_t *my_stack , void *element);
void *pop_stack  (stack_ds_t *my_stack , stack_status_t *ret_stack);
void *stack_top  (stack_ds_t *my_stack , stack_status_t *data);
stack_status_t stack_count  (stack_ds_t *my_stack , unsigned int *stack_count);



#endif // _DYNAMIC_STACK_H

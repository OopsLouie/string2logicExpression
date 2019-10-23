#include <stdint.h>
#include "common_define.h"


uint32_t num_stack_push(num_stack * s , num_attr_t n);
num_attr_t num_stack_pop(num_stack * s);
num_attr_t num_stack_top(num_stack *s);
int num_stack_isFull(num_stack * s);
int num_stack_isEmpty(num_stack * s);


int op_stack_push(op_stack * s , op_attr_t op);
op_attr_t op_stack_pop(op_stack * s);
op_attr_t op_stack_top(op_stack * s);
int op_stack_isFull(op_stack *s);
int op_stack_isEmpty(op_stack * s);


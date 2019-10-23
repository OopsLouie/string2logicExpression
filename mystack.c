#include <stdio.h>
#include "mystack.h"


uint32_t num_stack_push(num_stack * s , num_attr_t n)
{
    if(s->topIdx == MAX_STACK_SIZE -1)
    {
        printf("num stack full\n");
        return -1;
    }
    s->nums[s->topIdx].num = n.num;
    s->nums[s->topIdx].isId = n.isId;
    s->topIdx++;
    return 0;
}

num_attr_t num_stack_pop(num_stack * s)
{
    num_attr_t num_attr;
    num_attr.num = -1;
    num_attr.isId = 0;
    if(s->topIdx == 0)
    {
        printf("stack is empty\n");
        return num_attr;
    }
    num_attr.num = s->nums[s->topIdx-1].num;
    num_attr.isId = s->nums[s->topIdx-1].isId;
    s->topIdx--;
    return num_attr;
}

num_attr_t num_stack_top(num_stack * s)
{
    num_attr_t num_attr;
    num_attr.num = -1;
    num_attr.isId = 0;
    if(s->topIdx == 0)
    {
        printf("stack is empty\n");
        return num_attr;
    }
    num_attr.num = s->nums[s->topIdx-1].num;
    num_attr.isId = s->nums[s->topIdx-1].isId;
    return num_attr;
}

int num_stack_isFull(num_stack * s)
{
    if(s->topIdx == MAX_STACK_SIZE -1)
        return 1;
    return 0;
}

int num_stack_isEmpty(num_stack * s)
{
    if(s->topIdx == 0)
        return 1;
    return 0;
}

int op_stack_push(op_stack * s , op_attr_t op_attr)
{
    if(s->topIdx == MAX_STACK_SIZE -1)
    {
        printf("op stack full\n");
        return -1;
    }
    s->ops[s->topIdx].op = op_attr.op;
    s->ops[s->topIdx].paren = op_attr.paren;
    s->topIdx++;
    return 0;
}

op_attr_t op_stack_pop(op_stack * s)
{
    op_attr_t op_attr;
    if(s->topIdx == 0)
    {
        op_attr.op = OP_INVALID;
        op_attr.paren = -1;
        printf("stack is empty\n");
        return op_attr;
    }
    op_attr.op = s->ops[s->topIdx-1].op;
    op_attr.paren = s->ops[s->topIdx-1].paren;
    s->topIdx--;
    return op_attr;
}

op_attr_t op_stack_top(op_stack * s)
{
    op_attr_t op_attr;
    if(s->topIdx == 0)
    {
        op_attr.op = OP_INVALID;
        op_attr.paren = -1;
        printf("stack is empty\n");
        return op_attr;
    }
    op_attr.op = s->ops[s->topIdx-1].op;
    op_attr.paren = s->ops[s->topIdx-1].paren;
    return op_attr;
}

int op_stack_isFull(op_stack * s)
{
    if(s->topIdx == MAX_STACK_SIZE)
        return 1;
    return 0;
}

int op_stack_isEmpty(op_stack * s)
{
    if(s->topIdx == 0)
        return 1;
    return 0;
}



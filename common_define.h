#ifndef __COMMON_DEFINE_H__
#define __COMMON_DEFINE_H__

#define MAX_STACK_SIZE 50

typedef struct
{
    uint32_t num;
    int isId;
}num_attr_t;

typedef struct
{
    int topIdx;
    num_attr_t nums[MAX_STACK_SIZE];
}num_stack;

typedef struct
{
    int op;
    int paren;
}op_attr_t;

typedef struct
{
    int topIdx;
    op_attr_t ops[MAX_STACK_SIZE];
}op_stack;

enum OP_TYPE
{
    OP_NOT = 1,
    OP_AND,
    OP_OR,
    OP_INVALID
};


#endif

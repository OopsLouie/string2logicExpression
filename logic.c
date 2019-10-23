#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "mystack.h"

int parseLogic(const char * logic);
int getBoolFromNum(int a);
uint32_t getIdFromlogic(const char * logic , uint32_t digit_begin , uint32_t digit_end);
int getOpPriority(char c);
int cmpOpPriority(op_attr_t op1 , op_attr_t op2);
int calculateOnce(num_stack * ns , op_stack * os);

int main()
{
    char * logic = "!(101 & 201   | 301  )| !401  & 501";
    int result = parseLogic(logic);
    if(result == -1)
    {
        printf("Calculate error\n");
        return -1;
    }
    else
    {
        printf("Calculate success\n");
        printf("logic expression is %s \n",logic);
        printf("the result is %d \n",result);
    }
    return 0;
}


int parseLogic(const char * logic)
{
    uint32_t digit_begin = (uint32_t)-1;
    uint32_t id = (uint32_t)-1;
    uint32_t i;
    int paren = 0;
    num_stack ns;
    op_stack os;
    memset(&ns ,0 ,sizeof(num_stack));
    memset(&os ,0 ,sizeof(op_stack));
    for(i = 0;i<strlen(logic);i++)
    {
        if(isdigit(logic[i]))
        {
            if(digit_begin == (uint32_t)-1)
                digit_begin = i;
        }
        else
        {
            id = getIdFromlogic(logic , digit_begin ,i);
            if(id != (uint32_t)-1)
            {
                digit_begin = (uint32_t)-1;
                num_attr_t num_attr;
                num_attr.num = id;
                num_attr.isId = 1;
                num_stack_push(&ns , num_attr);
            }
            if(logic[i] == ' ')
                continue;
            if(logic[i] == '(')
                paren++;
            else if(logic[i] == ')')
            {
                if(paren<=0)
                {
                    printf("not enough left parentheses\n");
                    return -1;
                }
                paren--;
            }
            else
            {
                int op_prio = getOpPriority(logic[i]);
                if(op_prio != OP_INVALID)
                {
                    op_attr_t op_attr;
                    op_attr.op = op_prio;
                    op_attr.paren = paren;
                    while(!op_stack_isEmpty(&os) && cmpOpPriority(op_stack_top(&os) , op_attr))
                    {
                        if(calculateOnce(&ns , &os) == -1)
                            return -1;
                    }
                    op_stack_push(&os , op_attr);
                }
                else
                {
                    printf("Invalid character\n");
                    return -1;
                }
            }
        }
    }
    if(paren != 0)
    {
        printf("Not enough parentheses\n");
        return -1;
    }
    if((id = getIdFromlogic(logic , digit_begin ,i)) != (uint32_t)-1)
    {
        digit_begin = (uint32_t)-1;
        num_attr_t num_attr;
        num_attr.num = id;
        num_attr.isId = 1;
        num_stack_push(&ns , num_attr);
    }
    while(!op_stack_isEmpty(&os))
    {
        if(calculateOnce(&ns , &os) == -1)
            return -1;
    }
    if(ns.topIdx != 1)
    {
        printf("Internal error\n");
        return -1;
    }
    return num_stack_pop(&ns).num;
}


int getBoolFromNum(int a)
{
    if(a == 101)
        return 1;
    else if(a == 201)
        return 1;
    else if(a == 301)
        return 1;
    else if(a == 401)
        return 1;
    else if(a == 501)
        return 1;
    else
        return 1;
}
uint32_t getIdFromlogic(const char * logic , uint32_t digit_begin , uint32_t digit_end)
{
    if(digit_begin == (uint32_t)-1)
    {
        return (uint32_t)-1;
    }
    assert(digit_end>digit_begin);
    if(digit_end-digit_begin>9)
        printf("Expression is too large\n");
    uint32_t multi = 1;
    uint32_t sum = 0;
    uint8_t i;
    for(i = digit_end - 1;i > digit_begin -1;i--)
    {
        assert(isdigit(logic[i]));
        sum += (logic[i]-'0')*multi;
        multi *= 10;
    }
    return sum;
}


int calculateOnce(num_stack * ns , op_stack * os)
{
    if(num_stack_isEmpty(ns))
    {
        printf("not enough operand\n");
        return -1;
    }
    num_attr_t right = num_stack_pop(ns);
    num_attr_t left;
    left.num = -1;
    left.isId = 0;
    op_attr_t op_attr = op_stack_pop(os);
    if(op_attr.op != OP_NOT)
    {
        if(num_stack_isEmpty(ns))
        {
            printf("not enough operand\n");
            return -1;
        }
        left = num_stack_pop(ns);
    }
    num_attr_t result;
    uint32_t left_num,right_num;
    if(left.isId == 1)
        left_num = getBoolFromNum(left.num);
    else
        left_num = left.num;
    if(right.isId == 1)
        right_num = getBoolFromNum(right.num);
    else
        right_num = right.num;
    switch(op_attr.op)
    {
        case OP_NOT:
        {
            result.num = !right_num;
            result.isId = 0;
            break;
        }
        case OP_AND:
        {
            result.num = left_num & right_num;
            result.isId = 0;
            break;
        }
        case OP_OR:
        {
            result.num = left_num | right_num;
            result.isId = 0;
            break;
        }
        default:
            printf("bad operator\n");
            break;
    }
    num_stack_push(ns , result);
    return num_stack_top(ns).num;
}


int getOpPriority(char c)
{
    switch(c)
    {
        case '!' :
            return OP_NOT;
        case '&' :
            return OP_AND;
        case '|' :
            return OP_OR;
        default:
            return OP_INVALID;
    }
}

int cmpOpPriority(op_attr_t op1 , op_attr_t op2)
{
    if(op1.paren < op2.paren)
        return 0;
    if(op1.paren > op2.paren)
        return 1;
    assert(op1.paren == op2.paren);
    if(op1.op > op2.op)
        return 0;
    if(op1.op < op2.op)
        return 1;
    return 1;
}

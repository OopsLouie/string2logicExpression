from string2logic_class import *

def parseString(logic):
    digit_begin = -1
    rule_id = -1
    paren = 0
    num_stack = []
    op_stack = []

    if not isinstance(logic ,str):
        return "Invalid logic string format" , None

    for i in range(len(logic)):
        if logic[i] not in valid_char_list:
            return "Invalid char in logic string" , None
        if logic[i].isdigit():
            if digit_begin == -1:
                digit_begin = i
        else:
            if digit_begin != -1:
                rule_id = int(logic[digit_begin : i])
                digit_begin = -1
                num_stack.append(Node('@' , rule_id , None , True))
            if logic[i] == ' ':
                continue
            if logic[i] == '(':
                paren+=1
            elif logic[i] == ')':
                if paren <= 0:
                    return "not enough left parentheses" , None
                paren-=1
            else:
                op_now = op_attr(op_prio_map[logic[i]] , paren)
                while len(op_stack) != 0 and cmpOpPrio(op_stack , op_now):
                    if op_stack[-1].op_prio == op_prio_map['!']:
                        if len(num_stack) == 0:
                            return "Internal error" , None
                        num_stack.append(Node(op_prio_map[op_stack.pop().op_prio] , num_stack.pop() , None , False))
                    else:
                        if len(num_stack) == 1:
                            return "Internal error" , None
                        num_stack.append(Node(op_prio_map[op_stack.pop().op_prio] , num_stack.pop() , num_stack.pop() , False))
                op_stack.append(op_now)
    if paren != 0:
        return "Not engoth parentheses" , None
    if digit_begin != -1:
        rule_id = int(logic[digit_begin : i+1])
        digit_begin = -1
        num_stack.append(Node('@' , rule_id , None , True))
    while len(op_stack) != 0:
        if op_stack[-1].op_prio == op_prio_map['!']:
            if len(num_stack) == 0:
                return "Internal error" , None
            num_stack.append(Node(op_prio_map[op_stack.pop().op_prio] , num_stack.pop() , None , False))
        else:
            if len(num_stack) == 1:
                return "Internal error" , None
            num_stack.append(Node(op_prio_map[op_stack.pop().op_prio] , num_stack.pop() , num_stack.pop() , False))
    if len(num_stack) != 1:
        return "Internal error" , None

    return "Success" , num_stack.pop()



def cmpOpPrio(op_stack , op_now):
    if len(op_stack) == 0:
        return False
    if op_stack[-1].paren > op_now.paren:
        return True
    if op_stack[-1].paren < op_now.paren:
        return False
    if op_stack[-1].op_prio < op_now.op_prio:
        return True
    if op_stack[-1].op_prio > op_now.op_prio:
        return False
    return True
def initGlobal():
    global n_l
    global nl_l
    global o_l
    global ol_l
    global level
    n_l = []
    o_l = []
    level = 0
def tree2list(sp_num):
    global n_l
    global nl_l
    global o_l
    global ol_l
    global level
    level+=1
    if sp_num.op == '@':
        n_l.append(sp_num.n1)
        nl_l.append(level)
        level-=1
        return None
    if sp_num.n1.op != '@':
        n1 = tree2list(sp_num.n1)
    else:
        n1 = sp_num.n1.n1
    if sp_num.op == '!':
        n2 = None
    else:
        if sp_num.n2.op != '@':
            n2 = tree2list(sp_num.n2)
        else:
            n2 = sp_num.n2.n1
    if n1 is not None:
        n_l.append(n1)
        nl_l.append(level)
    if n2 is not None:
        n_l.append(n2)
        nl_l.append(level)
    o_l.append(sp_num.op)
    ol_l.append(level)
    level-=1
    return None



n_l = []
nl_l = []
o_l = []
ol_l = []
level = 0


if __name__ == "__main__":
    ret_str , ret = parseString("! (101 & 201|301)|!401&501")
    #print tree
    #501
    print(ret.n1.n1.n1)
    #401
    print(ret.n1.n2.n1.n1)
    #301
    print(ret.n2.n1.n1.n1)
    #201
    print(ret.n2.n1.n2.n1.n1)
    #101
    print(ret.n2.n1.n2.n2.n1)

    initGlobal()
    tree2list(ret)
    print(n_l)
    print(nl_l)
    print(o_l)
    print(ol_l)
    n_s = Number_stack()
    o_s = Operator_stack()

    for i in range(len(n_l)):
        n_s.num[i] = n_l[-(i+1)]
        n_s.level[i] = nl_l[-(i+1)]
    n_s.topIdx = len(n_l)

    for i in range(len(o_l)):
        o_s.num[i] = o_l[-(i+1)]
        o_s.level[i] = ol_l[-(i+1)]
    o_s.topIdx = len(o_l)



    ret_str , ret = parseString("101")
    #101
    print(ret.n1)
    #None
    print(ret.n2)
    # @
    print(ret.op)









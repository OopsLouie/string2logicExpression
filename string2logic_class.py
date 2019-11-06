from ctypes import *

# '?' = Invalid
# '@' = self
# '!' = not
# '&' = and
# '|' = or



valid_char_list = [' ' , '(' , ')' , '!' , '&' , '|']
for i in range(10):
    valid_char_list.append(str(i))

op_prio_map = {
    1:"!" , "!":1,
    2:"&" , "&":2,
    3:"|"  , "|" :3,
}




class Number_stack(Structure):
    _fields_ = [
                ("topIdx" , c_ubyte),
                ("num" , c_uint * 10),
                ("level" , c_ubyte * 10) ]

class Operator_stack(Structure):
    _fields_ = [
                ("topIdx" , c_ubyte),
                ("op" , c_char * 10),
                ("level" , c_ubyte * 10) ]

class op_attr(object):
    def __init__(self , op_prio , paren):
        self.op_prio = op_prio
        self.paren = paren


class Node(object):
    def __init__(self , op , n1 , n2 , isID):
        self.op = op
        self.n1 = n1
        self.n2 = n2
        self.isID = isID


if __name__ == '__main__':
    n1 = Node('@', 1 , True)
    n2 = Node('@', 2 , True)
    n3 = Node('|', n1 , n2 , False)

    l = [n1,n2,n3]

    for i in range(len(l)):
        print(l[i].n1,end='')
        print(l[i].op,end='')
        print(l[i].n2)

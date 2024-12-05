![](.\reg.png)



### STP指令详解

![](.\stp.png)

**类型1、**STP <Xt1>, <Xt2>, [<Xn|SP>], #<imm>

将Xt1和Xt2存入Xn|SP对应的地址内存中，然后，将Xn|SP的地址变更为Xn|SP + imm偏移量的新地址

**类型2、**STP <Xt1>, <Xt2>, [<Xn|SP>, #<imm>]!

将Xt1和Xt2存入Xn|SP的地址自加imm对应的地址内存中，然后，将Xn|SP的地址变更为Xn|SP + imm的offset偏移量后的新地址

**类型3、**STP <Xt1>, <Xt2>, [<Xn|SP>{, #<imm>}]

将Xt1和Xt2存入Xn|SP的地址自加imm对应的地址内存中



函数调用在栈中的关系**（call function压栈，地址递减；return弹栈，地址递增）：**

![](.\sp.png)
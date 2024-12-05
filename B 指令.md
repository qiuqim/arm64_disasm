### B 指令

#### 一、Branch指令分类：

- 1、 无条件分支+立即数：直接跳转到某地址，不能跳转到寄存器（指令有两个：”b label” ”bl label”。在编译过程，编译器会将label翻译成立即数（label处的地址）B指令：简单的程序跳转，跳转到目标标号处执行

- 2、 无条件分支+寄存器：

  - blr  Xm：跳转到由Xm目标寄存器指定的地址处，同时将下一条指令存放到X30寄存器中。
  - br   Xm：跳转到由Xm目标寄存器指定的地址处。不是子程序返回
  - ret   {Xm}：跳转到由Xm目标寄存器指定的地址处。是子程序返回。Xm可以不写，默认是X30.

- 3、 条件分支：所有条件分支的跳转目标都是立即数！

  ARMv8的条件分支写法：b.cond  label。其中cond是条件码共十六个（EQ,NE,CS等等）
  
  bl.eq equal 等于
  bl.ne not equal 不等于
  bl.gt greater than 大于
  bl.ge greater equal 大于等于
  bl.lt less than 小于
  bl.le less equal 小于等于

#### 二、指令格式

```
b 0x17向后跳转，0x14向前跳转
mask: 0xfc000000   1111 1100 0 0 0 0 0 0
opcode: 0x14000000 0001 0100 0 0 0 0 0 0
bl 0x97向后跳转  0x94向前跳转
mask:  0xfc000000
opcode:0x94000000  1001 0100 0 0 0 0 0 0
BL指令与B指令几乎一样，唯一的区别就是它跳转的时候会将下一条指令（PC+4）的地址写入到LR寄存器。这条指令表示调用了一个函数。

 
['ADDR_PCREL26']

|31|30|29|28| 27|26|25|24| 23~00|

imm26 after split: imm26

|0001 |01AA |A |A|A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |A |

mask as follow:

|1111 |1100 |0 |0|0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |

A  - imm26
```

#### 三、用法解析

#####   为什么b指令的base opcode是0x14000000，而“b  label”指令翻译成二级制是0x17ffffff？？？

------

>  Branch指令是相对当前pc地址的分支指令 
>
> 以比当前pc地址小的为后 ， 大的为前

###### 1.在ARMv8中，相对于当前b指令向后跳转时

编译器生成指令的二进制encoding（即b指令最终生成的二进制代码）的过程如下：

向后跳转时，branch指令将除base opcode之外的位（imm26的位）全部置一，然后做减法如下：

指令的Encoding = （0x14000000 | 0x03ffffff）—（当前b指令所在的指令地址 — branch指令的目标地址）/4 — 1

即当前b指令地址与目标地址做差后整出4（因为是32位地址），再减一。

```
000000000040051c <label2>:
label2():
  40051c:      d503201f        nop
  400520:       d503201f        nop
  400524:       d503201f        nop
  400528:       17fffffd       b       40051c <label2>

Encoding=0x17ffffff—（400528—40051c）/4—1= 0x17ffffff—2 = 17fffffd 
TO = 400528 + (-3 * 4) //向后跳3
```



###### 2.向前跳转是同理的

向前跳转时，branch指令将除base opcode之外的位全部置零，然后做加法如下：

指令的Encoding = （0x14000000 &0xfc000000）+（branch指令的目标地址—当前b指令所在的指令地址）/4

###### 3.跳转计算

imm26 = Encoding & 0x03ffffff  （全ff 为-1 即向后跳 [-1 * 4]

To = pc + imm26
# Sequential logic

by Lekang Yuan

## Introduction 

`where we are?`

In this chapter we are going to introduce another kind of logic besides combinational logic: sequential logic.In the same time we will build memory chips, and we will focus on understanding the key concept of memory: space and time. 

`why sequential?`

**Need of previous state**

​	Combinational logic means that the output of a combinational chip **depends solely on the current input**, regardless of what **the sequence of previous input** the chip has. So here is a question: Can we build a computer with only combinational logic ?

​	Not actually. See this simple example. Let's suppose there is a counter,  whenever you press the bottom, the number will increase by one. To do this, only **the current input**(whether or not you are pressing the bottom)is not enough,  the **state** of the counter(the total number), which is **the result of the previous input** shuold also be an input. And to record the state, we must introduce the concept of time.

**Reduce space complexity**

​	Another reason for why we need time is that by expand through time we can greatly reduce **space complexity**. If there is only combinational logic, we can not form a loop(If so, there will be logic conflict like O=I+1;O=I), so each compoent can only be used once. If we want to solve a complex problem, we can link many ALUs together, each to carry out one step--It works, but it's so stupid as it cost too much.So we choose to deal with the problem by **expanding through time**, by **doing one step in one clock cycle**(introduced later), so we can use only one ALU to solve the same problem.    

`Introduing the time`

**Master clock**

​	Since maintaining state or memorizing values is **timedependent**, we must talk about the **Clock**. In most computers, there is a master clock that continuously delivers periodic change signals. Each sequential chip receives this time signal so that different chips can perform functions in a **uniform time frame**. 

​	About its implement and the meaning of being uniform, please read CPT3.21,CPT3.1_Figure3.4.

**DFF**

​	Next we should find a **component** which is **time-dependent.** And the most basic time-dependent expression can be: **out(t) = in(t-1)**. We can change state at t by define in(t-1), and by input the output we can maintain state.  

​	Note that we will abstract away the complexity of building DFF, and simply use it as a **build-in** building block like Nand gate.For more details, please read CPT3.2.1.

##Specification

`Memory series`

Having introduced the concept of time, let's see what shuold be considered tio make a memory. 

First are the **operations**.It shuold have the ability to maintain state, and we can read(get the stored state) or write(change the state). Think about the time expression, and think how we can do that. Deal with that on one bit,and we will get a 1-Bit register.

Next is **expansion through space**.First in one word, expand 1bit register tio 16bits register.Then bundle register together to form RAM of different sizes.To access one register,  we shuold make chioce by its **address**.

`Control chip:counter`

We can store data in memory, and we can also **store instruction** in memory. The figure is that a set of instructions is stored in memory, one by one, and **in each time cycle** we fetch and execute one instruction by its **address**.

So we need a chip to help with that. In common cases, we will just goto the next instruction, so the address should increase by 1.Sometimes we want to jump to another location,  which can be done by inputing a address and use it as the next address. When we want to run the program again,the address should be reset to 0. These are all we need from a counter.



## Project

We will build the register, RAM of different sizes and a counter.  

The project is not hard. Just go to proj_03 to do it. Focus on how to make choose between operations and locations.（Recall the gates built in chapter1, and think about how we do the same thing in chapter2.）



## Addentional Points

**Comparision: Different kinds of Memory**

Forming a circut cycle is not the only way to build memory. We can also build non-volatile memory like disk, using whether or not the meterial is magenetized to represent state. It can maintain the state when powered off, but it's slower.

**Address**

In the previous parts we've spilled a lot of ink talking about time, why we need time, and the basic operation based on time: maintain, read,write.Here lets see another important concept of memory: space. 

When we are considering about space we need to foucs on address. When we are introducing a new varible, we musy allocate memory for it and record the address. When we want to access previous declared varibles, we get them by address. When some variables are not needed, we recycle the memory in that address. Actually,every variable name or function name in the following chapter, no matter in assembly ,VM,or high level project, is just a represent of a certain address.

So for every problem involved with memory, you can consider about it in the following manner: 

* Are we doing read or write?
* How the memory is allocated?

Some questions can be as follows:

**Expansion through space: File and Web**

* More memory across space.
* Different location, but the structure is the same.
* Edited later.

## Next chapter

As we already have memory and ALU, the thrilling time is just in front of us. In the next chapter we will combine everything together to form a completed computer!  Σ(⊙▽⊙"a.
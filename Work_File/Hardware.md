# Boolean logic
###### Chen Yihao
___
## Logic model
![logic model](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter01/LogicModel1.png)
___
## Introdution to this chapter
When we talk about computers, what are we really talking about? I guess you must have had this question in your mind. Are they just calculators? Are they media players? Or are they communication tools? Or maybe you have your own ideas about that.

In a way, computers can be anything you can imagine. They have been part of the modern civilization, no matter how people defined them.

So here comes another question – quite a natural question – what features do these definitions have in common?

To put it another way, **what determines a computer’s essence?**

If you once tried to explore the world of computers, you may have known that the information in today’s computers is represented as patterns of **bits.** A bit (binary digit) is either one of two digits – 0 and 1 – which are symbols with no numeric meaning.

And amazingly, **this is exactly the essence, the origin and the foundation of our computers – Boolean logic.**

Boolean logic is introduced by Boole George to represent the truth values and the operations on them. Claude Shannon’s circuit design theory later demonstrated that Boolean logic was realizable in physics. These act as the foundation of a computer system.

And it can be proved that **the Nand gate is complete** in Boolean logic. So in some way, we can say that the computer is constructed on the base of Nand gates.

In this first chapter, we are going to learn how the Boolean logic serves as a foundation of the whole computer system, which is also the basic knowledge for all the later chapters.
___
## Specifications
The book  _The Elements of Computing Systems_ gives very detailed information about the Boolean Algebra. For the specific principles of Boolean logic, you may refer to the pages from 24 to 30 in the book. For the implementation of Boolean logic in HDL, you may refer to the pages from 33 to 42 in the book.

Here we are going to focus particularly on the most basic Nand gate and explain its functional completeness, because we think these parts actually lay the foundation of the overall computer system, but were not given enough attention in the original textbook.
#### Nand gate
>What is Nand? Literally, Nand is “not and”. It is a logical operation on two logical values. It produces a value of true, only if at least one of the propositions is false.
>
>In Claude Shannon’s circuit design theory, we can put the Boolean operation into practice by using electrical circuity. Such implementations are called gates. Nand gate is one of them.
>
>Of course there are other operations in Boolean logic, such as And, Or, Not and Xor. But we choose to focus on the Nand only, why?
>
>As is mentioned above, the **Nand only is functionally complete** enough in Boolean logic. That is to say, we can achieve all the operations in Boolean algebra with only Nand. By the way, Nor is another operation that is complete.
>
>Maybe you are curious why the only single operation of Nand can perform all the Boolean algebra. Here we are going to give the demonstration.

![Nand gate](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter01/nand.png)
#### Completeness of Nand
>It is evident that a binary operation in Boolean logic can have 16 possible outputs in total. As long as we demonstrate that all the 16 situations can be realized by only Nand, then we can say the Nand is functionally complete.
>
>To put the problem easier, we can firstly demonstrate that all the elements of the set {And, Or, Not} are functionally complete, and then demonstrate they can be constructed by Nand only. This way is also the application of **bootstrapping method.**
>
>By using the truth table, one can easily find that And, Or and Not together are complete. And we can also implement them three by only Nand like this:
>
>_Q = A And B = ( A Nand B ) Nand ( A Nand B )_
>_Q = A Or B = ( A Nand A ) Nand ( B Nand B )_
>_Q = Not( A ) = A Nand A_
>
>In summary, we demonstrate the completeness of Nand.
___
## Project introduction
For this part, _The Elements of Computing System_ gives very detailed information. You may just refer to the pages from 45 to 46 in the book.
___
## Additional thoughts
Now that we have a powerful “construction material” Nand gate which is complete, we can just use it to construct more complex structures, including And, Not, Or, Xor and  more. It has been proven just now that by this way, we can perform any operations in Boolean algebra.

Then one may ask: “So…what?”

What is the significance of that? 

It is true that the Nand only is complete enough for our Boolean algebra, and is the foundation of all the computer system. All of our computer science can be seen as an extension of this tiny chip. This is one aspect – **the high degree of consistency and form-simplicity in computer science.**

But if you want to build a computer totally from scratch, using mountains of piles of Nand gates, then you will find it is not so easy.

That is another aspect. Still we are talking about the **bootstrapping concept**. In the Boolean logic, we particularly focus on Nand and see it as a point of departure, so we use Nand gate to build other gates. In this way, we are actually performing the process of bootstrapping. After we build an more advanced layer of our system, we can just forget its inner implementation but to freely use its interface. That can largely decreases the difficulty and complexity of our building tasks.

And bootstrapping is exactly where the computational thinking hides.
![Bootstrap in picture](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter01/bootstrap.png)
___
## About the next chapter
This first chapter talks about how the Boolean logic serves as a foundation of the whole computer system, which is also the basic knowledge for all the later chapters. Next chapter will introduce the more complex composition of Boolean logic, which is called _combinational logic_.
___
## References
[1] Nand2Tetris, chapter 01
[2] The Elements of Computing Systems
[3] https://en.wikipedia.org/wiki/NAND_logic
[4] Computer Science: an Overview

___

# ALU

by Lekang Yuan

## Introduction 

`Where we are?`

​	The chapter 1 gets us through the door by introducing Boolean Logic, and in this chapter we will take a step further to **combinational logic**, which enables our computer to do **arithmetic operations**. And instead of only talking about logic, we will also focus on **building  the first compoent of a real computer**: the ALU.

`What to do to build a computer?`	

​	Computer is all about **operations on the state of data**. The OS and all the software we see can be divided into 2 parts , frontend and backend. Backend by nature is about data structure and logic. Frontend deals with what users see and how we interact with computer, and these are also data: RGB, (x,y), a character.

​        So there is only 2 things we are going to consider about, **how to maintain data, **and **how to operate on data**. The latter one can be further divided into **what's the basic operations** and **how to do these operations**, and in this chapter we will foucs on all the basic operations needed in a computer.

`"Only Add"`

​       How many kinds of operations do we need in a computer? 1000, or 10000? Actually, we only need one (roughly): add.  

​       Consider about  how we do **math**.Substraction can be viewed as adding a negetive number, and  we get "×"and "÷" by adding or substracting in a common procedure. Even those operations in the Advanced Mathematics, like matrix operation and integration, is no more than adding and substraction, though  there will be there will be many steps. And do **draw something on the screen**, computer are only need to calculate the states of the pixels, which is again a series of adding.(You can see that in the part of OS). 

​	Well, maybe add can't literally  do everything (shifting[wiki] for example), but we can see that great amout of operations can be **rooted to several meta operations**. So here, we can focus only on **building foundamental gates**, instead of having trouble dealing with the countless needs one by one. 

`Consider about Logic and Translation`

​	So how to building these new gates? Are we solving circuit problems? No. As we can see in the first chapter, **computer is all about logic**. What we are going to do is only to **translate**, first clearify how we do things, then consider about the corresponding expression in **Boolean Logic**. For basic 2 bits logic, we can consider about **truth table**, and for more complex ones, we can abstract the gates built before by their functions. (For example, we can use Mux and DMux to "choose" or build "branch". )

## Specification

`Binary numbers`

You can see what's binary number, how to convert binary with decimal number in 2.1.Binary Numbers.

`Data storage in computer`

The figure is listed in 2.1_figure2.1. Notice that the **top is limited**. It's like a clock, whose top is 12. And adding in a clock is something interesting, in that 5 hours past 8 is not 13, but 1.And how you can get 1 from 8 by substraction?

`ALU`

In ALU we want to achieve some **necessary basic operations on hardware level**, so we can acheive the left ones by **designing algorithms on software level**.So what do we need?We need some basic **arthmetic oprations** like add or substraction, and some basic **logic operations** like and,not,or,and "**compare**".So how can we do that? Instead of creating the operations one by one, ALU does like this:

1.Do **one** binary **logic** operation (And) and **arithmetic** operation (+)

2.**Change** on inputs and calculated result. (By combining 1 and 2 we can get 28 common  binary logic operation and arithmetic operation.)

3. Compare the result with 0.(To do flow contols, as we will see in machine code.) 

You can also see a more detailed describtion in 2. 2.2

When doing the projects in the latter chapter, you can see that all the projects we are going to build can be based on these operations.

## Project

You've already have all the knowledge to build the project of this chapter.Instead of giving you all the details(As the original book does),we strongly suggest you do the project by you own.If you have any problem, you can read the following hints.

### Adder

Build a 16bits adder.

**How to get started?**

Consider about adding on one bit first. What's the logic of adding two numbers?Consider about the truth table. 

**All right.But we have more than one bit.How to deal with it?**

When we are doing adding , there will be a carrie.When adding two numbers on one bit, what's the carrier? What's adding with a carrier? (Just add twice,right?) 

### ALU

Build an ALU. The function list is in 2.2.2. As ALU is the first complex project we are going to build in this book, though much easier than the latter ones, we will use it to demostrate important thinking method used in building big project.

**How can you divide the project?**

We can **divide it into 4 parts**: process the input, basic arithmetic or logic operation, process the result, analyse the final output.The **input of one part is the output of the previous part**, and for each part we only have to consider its own function.By doing so, we change one complex problem into 4 smaller problems.

**What's the key in building each parts?**

Actually, there is only two kinds of things we are going to do:**make choice and 3 operations: not,and,add.** We already have gates to do the operations, so how to make chocies? We can use branch gates built in chapeter1.For example, when we want to get !x when nx==1 and x hwn x ==0, we can calculate !x first, and use a DMux to choose between the result and x.

**So what kind of method we can learn from this? **

In building the complex system, we will foucs on building realizable **basic blocks**, and then to **abstract** them to build more complex things. Abstraction means that we will only focus on the port, the surface, the overall function, without considering about the inside structure and realization. We are using the strategy when we are using previous gates like adder, not, and, DMux.

Having had these blocks, we are still not going to build the whole system at once. Instead, we are going to **divide the system into several parts**, each for a specific goal. In doing this, we will try to reach the goal of "**High cohesion, low coupling**", so we don't have to bother about other parts when building one part.

## Addentional points

**Analog computer**: Differ from the digital computer we are building, it uses the continuously changeable aspects of physical phenomena such as [electrical](https://en.wikipedia.org/wiki/Electrical_network), [mechanical](https://en.wikipedia.org/wiki/Mechanics), or [hydraulic](https://en.wikipedia.org/wiki/Hydraulics) quantities to [model](https://en.wikipedia.org/wiki/Scientific_modelling) the problem being solved. By comparing it with our computer, you can further understand that the principle of digital computer is more about logic rather than circuit.(Not for really building.)

**"One to all strategy":** In chapter one we rooted all the  gates to nand, and in this chapter we rooted all the operations to add (and a few more).When building a system, we can think of its **basic words**, the **only root**, focus on the **unity** instead of spending time thinking about trivial details. This strategy can be seen in many areas, like the particle system in After Effect: we only conside about altering the motion and shape of particles, and countless things can be achieved——even those not so particle-alike. 



##Next chapter

Having finished this chapter , there is still something remained to be solved:

From the point of hardware : ALU is a function which has 2 inputs,1 output,and 64 possible operations . So where to get the input and store the output? Which operation to do?

From the point of logic: we've introduced combinational logic in this chapter. Can it solve any problems?

We will see in the next chapter.



(from: http://weili.ooopic.com/weili_11291382.html)

https://en.wikipedia.org/wiki/Combinational_logic

https://en.wikipedia.org/wiki/State_(computer_science)

___

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

___

# Computer Architecture
###### Chen Yihao
___
## Logic model
![Logic model](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter05/LogicModel5.png)
___
## Intoduction to this chapter
In the previous chapters, we have learned about combinational logic and sequential logic. So, how can we use these discrete parts of knowledge to build a powerful computer?

Secrets hide in the way we "compute". Whenever we want to solve a problem, we always need a pattern to follow. If not, we have to find one. To solve similar problems at any time, we memorize the exact steps. In computers it is quite the same. Those "steps" become a category of instructions and are stored in the computer's "Instruction Memory". After that, when we want to calculate something, we always need a place to do it and note down the intermediate values. That place is called the "Data Memory". Also we need our brain, whose counterpart in computer is the CPU, and a reminder of what to do next, which is the Program Counter.

All these units form our ideal computer structure, and each one of them can be implemented by our logic gates. As you can see in our "Additional thoughts", our hack computer inherits the features of this structure, both advantages and disadvantages. **This structure is "one of" the computer architectures.**

The first documented computer architecture was in the correspondence between Charles Babbage and Ada Lovelace, describing the analytical engine. And in mordern computer science, the most well-known architecture is **Von Neumann architecture**, which is exactly what we are going to build in this chapter.

After that, the hardware of our Hack computer is done and we are going to software part. So in some way, the computer architecture is also a bridge between hardware and software. The upper level software will finally use the machine language instructions to coordinate the machine, and this process is just determined by the computer architecture.

Besides Von Neumann architecture, of course there are other computer architectures. **What are the connections among them?** And **what are the differences?** These questions are also what we are going to discuss.

___
## Specifications
In this chapter, we are going to build a Hack computer based on the Von Neumann architecture. So we should firstly know what Von Neumann architecture is. The book of _The Elements of Computing Systems_ has given very detailed information about the basic components in Von Neumann architecture as well as their functions. So you may just refer to the pages from 100 to 122 in the book. But the book doesn't tell us "why" -- **why we choose Von Neumann architecture**. To answer this question, we are going to focus on the characteristics of Von Neumann architecture rather than the common specifications.
#### Von Neumann architecture
It is quite clear that we must build our computer in Von Neumann architecture. But before that, there is a question -- why Von Neumann?

In other words, **what are the characteristics of Von Neumann architecture?**

>The von Neumann architecture, which is also known as the von Neumann model and Princeton architecture, is a computer architecture based on the 1945 description by the mathematician and physicist John von Neumann and others in the First Draft of a Report on the EDVAC.
>This describes a design architecture for an electronic digital computer with parts consisting of a processing unit containing an arithmetic logic unit and processor registers; a control unit containing an instruction register and program counter; a memory to store both data and instructions; external mass storage; and input and output mechanisms.
>The meaning has evolved to be **any stored-program computer in which an instruction fetch and a data operation cannot occur at the same time because they share a common bus**.
>This is referred to as the von Neumann bottleneck and often limits the performance of the system. (_Wikipedia_)

From the descriptions in _Wikipedia_ we can get such points:

* It has some basic parts like CPU, CU, memory, mass storage and I/O devices.
* An instruction fetch and a data operation cannot occur at the same time.
* Its performance is limited, but it is simpler compared with other architectures.

So that is what we should know about Von Neumann architecture -- **a standard and ralatively simple stored program computer architecture which has its bottleneck in performance**. It is the answer to the question and we should always understand that what we build is based on the Von Neumann architecture and it has its advantages as well as disadvantages.
![Von Neumann architecture](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter05/vonNeumann.gif)

#### Von Neumann bottleneck
As is mentioned above, there exists what is called Von Neumann bottleneck in Von Neumann architecture. Then you come to wonder how it could happen. So here is the detailed explanation to Von Neumann bottleneck.

In Von Neumanm architecture, there is **only one shared bus between the program memory and data memory**. Such design leads to the von Neumann bottleneck -- the limited throughput (data transfer rate) between the central processing unit (CPU) and memory compared to the amount of memory. Because the single bus can only access one of the two classes of memory at a time, throughput is lower than the rate at which the CPU can work.

This seriously limits the effective processing speed when the CPU is required to perform minimal processing on large amounts of data. The CPU is continually forced to wait for needed data to be transferred to or from memory. Since CPU speed and memory size have increased much faster than the throughput between them, the bottleneck has become more of a problem, a problem whose severity increases with every newer generation of CPU.

That is the answer.

So here you come to wonder -- **what can be done to avoid such bottleneck?** 

And that is the story of the other computer architectures. A relatively more advanced architecture called Harvard just solve this problem. We'll talk about it later.
___
## Project Introduction
This chapter's project is going to build a general Hack computer based on Von Neumann architecture. The book of _The Elements of Computing Systems_ gives very detailed information about this part, and you may just refer to the pages from 125 to 126 in the book.
___
## Additional thoughts
#### Harvard architecture
![Harvard architecture](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter05/Harvard_architecture.png)

As is explained above, the Von Neumann bottleneck is the consequence of the shared bus, so the most direct way to solve it is just adding another bus. And by this means, we have Harvard architecture.

>In a system with a pure von Neumann architecture, instructions and data are stored in the same memory, so instructions are fetched over the same data path used to fetch data. This means that a CPU cannot simultaneously read an instruction and read or write data from or to the memory. In a computer using the Harvard architecture, the CPU can both read an instruction and perform a data memory access at the same time, even without a cache.
>
>A Harvard architecture computer can thus be faster for a given circuit complexity because instruction fetches and data access do not contend for a single memory pathway. (Wikipedia)

Also, a Harvard architecture machine has **distinct code and data address spaces**: instruction address zero is not the same as data address zero. Instruction address zero might identify a twenty-four bit value, while data address zero might indicate an eight-bit byte that is not part of that twenty-four bit value.

#### Some other advanced architectures
As we all know, electric pulses travel through a wire no faster than the speed of light. Since light travels approximately 1 foot in a nanosecond (one billionth of a second), it requires at least 2 nanoseconds for the control unit in the CPU to fetch an instructions from a memory cell that is 1 foot away. Consequently, to fetch and execute an instruction in such a machine requires several nanoseconds -- which means that increasing speed of a machine ultimately becomes a miniaturization problem. Although fantastic advances have been made in this area, there appears to be a **limit**.

In an effort to solve this dilemma, computer science concentrates on **throughput** rather than merely execution speed. And throughput here refers to the total amount of work the machine can accomplish in a given amount of time rather than how it takes to do one task.

And some other advanced architectures based on this concept have been invented.

>#### Pipelining
>In computing, a pipeline, also known as a data pipeline, is a set of data processing elements connected in series, where the output of one element is the input of the next one. The elements of a pipeline are often executed in
>parallel or in time-sliced fashion. Some amount of buffer storage is often inserted between elements. (Wikipedia)

>#### Multiprocessing
>Multiprocessing is the use of two or more central processing units (CPUs) within a single computer system.  
>![Multiprocessing](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter05/Multiprocessing.png)

In conclusion, all these architectures are different steps towards **parallel processing**, which is the performance of several activities at the same time. 
___

## About the next chapter
In this chapter, we learned how to build a general-purpose Hack computer, which is in Von Neumann architecture. Actually, in the process we can found that any computers' functions, specifications and performance were directly revelent to the design of computer architectures. In a word, **computer architecture is the skeleton of the hardware part of computers**. Only with the well constructed computer architecture can the soul of the software part fully perform its functions.

After this chapter, we will go into the software part. And the next chapter is about machine language and assembly language, which are highly revelent to the structure of our computer architecture -- Von Neumann architecture. If you have problems in understanding them, you may as well go back here to have a look again.
___
## References
[1] Nand2Teris, chapter 05
[2] The Elements of Computing Systems
[3] https://en.wikipedia.org/wiki/Von_Neumann_architecture
[4] https://en.wikipedia.org/wiki/Harvard_architecture
[5] https://en.wikipedia.org/wiki/Pipelining
[6] https://en.wikipedia.org/wiki/Multiprocessing
[7] Computer Science: an Overview
___

# Assembly Language

*Han Zhilei*

After building the entire functional Hack computer, this chapter advances towards the hardware-binded control method of the computer, which is called **assembly language**. It's our first stop in the journey through the *software layer*.

*NOTE* the order has been rearranged, and this chapter is corresponded with original chapter 4.

![Logic Model](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/logicmodel.png)

## Introduction

Congratulations on your implementation of the Hack computer. It's fully functional, and also powerful. We originate from **Nand** gate only to build the whole computer and adopt Harvard architecture, which facilitate matters when we look into the underlying structure.Here's a graph to make your memory of **computer architecture** come back.[1] 

![Harvard](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/Harvard.png)

We're now going to build our software layers and this chapter will discuss the language that directly generated by hardware implementation and design an assembly language. In the end, we shall be able to get the machine running as instructed.

###What is program?

Instruction memory, or *ROM*, is where the instructions are stored. Recall the design of our Hack computer, and you may remember the **Reset** button on the surface of the computer, which will redirect PC to be 0 - equally restart the program. Computer reads instructions in ROM according to the content of PC, and all the instructions form the *program*.

Since you have already built the computer, it's quite easy to find the instructions can be classified into 2 kinds: One kind changes the content of A-register, while another carries out operations. You can divide the latter into 2 aspects as well :either jump among the instructions of the program or conduct arithmetical&logical operation.

What we use to encode our program is machine-binded string of 0s and 1s, computer explicitly obey the codes.We call them **Machine language**,because of its direct connection with the underlying hardware platform.

### What is programming?

In essence, what we are going to do in the following chapters is **all about solving problems by programming**. With our hardware architecture working perfectly, we have **potentially** a very powerful tool. To unlock this potential, we have to translate our human thoughts and concepts into a notation that is in conformation with the specifications of this architecture. **This** is what programming is ALL about. This process is better summarized in the graph bellow. [2]

![process](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/process.png)

As you can see, machine language serves as the fundamental of the software layer as well as the interface for hardware. We can prove that anything a computer can do is able to be expressed by this language.When we are **programming**,the code produced all originate from machine language. What we will do is just facilitate the process of programming.

### Assembly:Why do we need it?

The difference between a machine and a human brain decides there should be higher level of language for programmers.**Assembly Language** is the most fundamental abstraction, which can be understood as mnemonic notation for the machine language. For instance , `1110001110000000` can be represented by `D-1`.

The design of assembly language is not fixed, but it should be tightly-binded to machine language. Generally speaking, a single assembly instruction is in correspondance with a single machine instruction, so there is no true difference between these two, because the **vocabulary** of the languages is the same - as stated before, jumping and operations - Just like :

```sequence
English->French:one to one
French->English:

English->Latin:several to one
Latin->English:
```

But we will see later that although unnecessary, the assembly language can provide utilities for *programmers*,for the sake of simplifying the **programming process**.

## Specification

In this part we will see how the Hack Assembly language is designed, and learn how to program using this language. A vast part of details in this section can be found in **The Element of Computing system section 4.2**. Although we rearrange the order of the chapters, it still throws light on the topic.

### A- and C- Instructions

As mentioned before, from the input of CPU, we classify the instructions to two kinds.In assembly language we define them to A- and C- instructions, respectively.

A-instruction is used to change the content of A register, its syntax is:

![ins](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/AInstruction.png)

while C-instruction is used to carry out operation,jump through program and change the content of D and M register:

![ins](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/CInstruction.png)

These two kinds of instructions are all user-friendly notation for corresponding machine code,as shown above.For more information,just refer to the Nand2Tetris textbook where more details are discussed.

### Expanded Utilities of Hack Assembly Language

It's unnecessary to provide more feature for assembly language, as is in the sentence *Keep it simple and stupid*.But with care,adding a few of them boost the process of programming. 

* The First Improvement: You may notice that **A,D,M** are all pre-defined symbol respectively referring to A-,D-,M- register.As long as we have symbols for certain RAM location,we can bring in more predefined ones to simplify the coding.You can refer to section 4.2.4 for more information.

* The Second Improvement: We should provide the feature that is the most useful.When programming using assembly,counting the number of instructions is the greatest nuisance. A good way to get rid of it is to define a "symbol" as well.But the symbol is not for register but for instruction,and we call it **label**. A label represent the next following instruction and can be referred to by jump operation. It greatly reduces the time for programming.

  Likewise,we can allow programmers to define own symbols for certain registers.The user-defined identifier (label or symbol) will make the process more automatic.See section 4.2.4 for more information

These **improvement** adds up to the power of the assembly language,by which improves the efficiency.

## Projects

After fully learned the principles of assembly language,try to write programs to carry out practical opearations using hack assembly language,with specification of the project described in section 4.4

## Additional points

#### completenesss of *mov*,and the instruction set

![mov](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/raw/master/team2/final/pub_chapter04/mov.png)

**In previous chapter**,we have stated that  **Nand is complete** and **Add is complete**,.etc. What about the language part? Is a single instruction able to represent all the others?

*mov* is an instruction in [x86](https://en.wikipedia.org/wiki/X86) architecture,Stephen Dolan has proved that by using *mov* and using it only we can represent any process that a computer can do.[3]

However,just like we do not use Nand everytime we want to implement a chip,and do not use add always,we do not use a single instruction to carry out all the operations.Modern CPU takes several to thousands instructions as their input,and is divided to RISC and CISC accroding to the number of the instructions.Learn more from the link in [4].

## Summary

By learning how to write programs and what is programming using Hack Assembly language,you are supposed to have basic concept of what we will do in following chapters discussing more software abstraction layers. Before we advance to next layer,we have to implement all the features we learned here in next chapter,by a program called **assembler**.

## Reference

[1] Picture from http://www.toves.org/books/java/ch01-overview/index.html

[2] Picture from https://en.wikipedia.org/wiki/Harvard_architecture

[3] Stephen Dolan,mov is Turing-complete

[4] https://en.wikipedia.org/wiki/Reduced_instruction_set_computer

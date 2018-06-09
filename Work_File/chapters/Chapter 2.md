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
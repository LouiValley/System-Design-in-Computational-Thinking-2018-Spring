# VM Translator
*By Habib Derbyshire*

##	Preface: what is translation?

If you are reading this chapter, you probably have finished creating an assembler. Congratulations on creating your first translator! Over the course of reading this book, you will realise that computing, from the bare-bones hardware, all the way to the most complicated algorithms, is just a series of translations. By knowing how these translations work, you will hold the secret to understanding ***all*** computing systems. *Some* of these translations are absolutely necessary for the computer to be able to work. In the case of the hack computer, we have to create a translation from machine code to basic Boolean logic, so that when given an instruction, our ALU will be able to conduct a calculation and give us an output. Sometimes, however, a translation is not an integral part of the system's function, but rather an aid to us mere humans. They are introduced at some point, to make life easier for whoever's job it is to work with these translations. 

##	Two tier compilation: bridging the gap

As you should know by now, assembly is very hard for (most) humans to understand, but as far as the computer is concerned, it doesn't get simpler than this. At the other end of the spectrum, there's our high level language called Jack (which we will study in detail in the chapters to come), which is quite easy for us to understand, but in order for it to be meaningful, we have to translate it into assembly code. We've already done translation once, and that wasn't too easy a task (at least not for us!), and that was from assembly to machine code, two very similar languages. Imagine the challenge of translating two languages entirely different in complexity, dimension and syntax! Indeed, such a task is very difficult. 

Translating from Jack to assembly also presents another challenge: the resulting assembly will work for the computer we built, but what about another computer, with a different kind of assembly? We would have to go through the process of writing the translator all over again! Surely this is a tedious task. 

Since the root of all these difficulties is the disparities between Jack and assembly, why don't we find a way to bridge that gap? If we can create a language that is both "low" enough to translate into machine code easily, and yet "high" enough so that Jack can easily translate into it, it would make our lives (as compiler designers) a lot easier. And the added benefit we get is that if we should wish to compile Jack for any other machine, we can leave the part that deals with Jack alone, and only rewrite the part that deals with the assembly. We call this "in-between language" VM (virtual machine) language, and soon enough, this funny name will make sense to you. 


## Virtual machine
![Logic Model](https://github.com/LouiValley/System-Design-in-Computational-Thinking-2018-Spring/blob/master/team3/Publication/VM_TRANSLATOR_PART_1_LOGIC_MODEL.PNG?raw=true "Logic Model")

## Virtual machine specification
Ok, so this is what the virtual machine needs to be able do:

*	Arithemtic operations, adding, subtracting, negation, comparing
*	Read from and store into the memory
*	Program flow commands, such as executing certain lines of code
*	Function calling

At first glance, this seems quite similar to what assembly is capable of doing. However, the way it goes about doing it is quite different. When reading from and writing to the memory, assembly does it in the most basic way possible: by directly reading from given addresses in the memory, sometimes called a register machine. However, in the virtual machine, we have a *stack machine* to deal with memory read/write. 

##	Introducing the Stack

Imagine a very tall stack of books, only the book on the very top is exposed to our view. If we want to see the face of the second book, we will have to take the top book out of the stack, making the second book the topmost book, exposing it's cover for us to see. If we wanted to add a book to the stack, we would have to put it on the top of the stack. This is exactly how the stack machine works. We create a "stack" of registers, each time we can only read or write to the topmost register of the stack. This method of reading memory is sometimes called (quite fittingly) *last in first out*, or LIFO. In the stack machine, the act of reading the value of the topmost register is called *pop*, and the act of adding a value to the stack is called *push*. 

![](https://upload.wikimedia.org/wikipedia/commons/b/b4/Lifo_stack.png =400x300)

All the other stack operations are based around push and pop: when adding two numbers, we first pop the two topmost numbers from the stack, calculated the sum and push it back into the stack

### Stack arithmetic

Our virtual machine language comes with a set of arithmetic operators:
*add, sub    	*//addition and subtraction*
*neg 		    *//negation*
*eq, gt, lt     *//compare the size of two numbers*
*and, or, not   *//boolean operators*

When these operators are executed, they pop one or two numbers from the stack, perform the calculation, then push the result back into the stack.




### References
[Stack (abstract data type), Wikipedia](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)#/media/File:Lifo_stack.png)
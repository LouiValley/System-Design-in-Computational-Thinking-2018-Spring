# Translators

#	VM translator

##	Some thoughts on translation

If you are reading this chapter, you will probably have finished creating an assembler. Congratulations on creating your first translator! Over the course of reading this book, you will realise that computing, from the bare-bones hardware, all the way to the most complicated algorithms, is just a series of translations. By knowing how these translations work, you will hold the secret to understanding ***all*** computing systems. *Some* of these translations are absolutely necessary for the computer to be able to work. In the case of the hack computer, we have to create a translation from machine code to basic Boolean logic, so that when given an instruction, our ALU will be able to complete a calculation and give us an output. Sometimes, however, a translation is not an integral part of the system's function, but rather an aid to us mere humans. They are introduced at some point, to make life easier for whoever's job it is to work with these translations. 

##	Two tier compilation: bridging the gap

As you should know by now, assembly is very hard for (most) humans to understand, but as far as the computer is concerned, it doesn't get much more simple than this. At the other end of the spectrum, there's our high level language called Jack (which we will study in detail in the chapters to come), which is quite easy for us to understand, but in order for it to be meaningful, we have to translate it into assembly code. We've already done translation once, and that wasn't too easy a task (at least not for us!), and that was from assembly to machine code, two very similar languages. Imagine the challenge of having to translate between two languages entirely different in complexity, dimension and syntax! Indeed, such a task is very difficult. 

Translating from Jack to assembly also presents another challenge: the resulting assembly will work for the computer we built, but what about another computer, with a different kind of assembly? We would have to go through the process of writing the translator all over again! Surely this is a tedious and nearly impossible task. 

Since the root of all these difficulties is the disparities between Jack and assembly, why don't we find a way to bridge that gap? If we can create a language that is both "low" enough to translate into machine code easily, and yet "high" enough so that Jack can easily translate into it, it would make our lives (as compiler designers) a lot easier. And the added benefit we get is that if we should wish to compile Jack for any other machine, we can leave the part that deals with Jack alone, and only rewrite the part that deals with the assembly. We call this "in-between language" VM (virtual machine) language, and soon enough, this funny name will make sense to you. 

##	Ok, let's get to specifics


**Context:**
*	An intermediary language know as VM will make life easier for us

**Goals:**
*    Create a VM abstraction and a language;
*    Have a way of translating the VM language into assembly;
    
**Measurable effect:**
*    Readers will know understand the motivation behind the VM abstraction
*    Readers will should be able to implement a translator for our VM language

**Output:**
*    Working VM translations;

**Process:**
*	Understand the stack architecture;
	* Implement basic vm arithmetic commands
*	Understand vm memory access commands
	* Implement memory access commands

**Input:**
*    .vm file
*    test case


## Virtual machine specification
Ok, so this is what the virtual machine needs to be able do:

*	Arithemtic operations, adding, subtracting, negation, comparing
*	Read from and store into the memory
*	Program flow commands, such as executing certain lines of code
*	Function calling

At first glance, this seems quite similar to what assembly is capable of doing. However, the way it goes about doing it is quite different. When reading from and writing to the memory, assembly does it in the most basic way possible: by directly reading from given addresses in the memory, sometimes called a register machine. Howver, in the virtual machine, we have a *stack machine* to deal with memory read/write. 

##Introducing the Stack

Imagine a very tall stack of books, only the book on the very top is exposed to our view. If we want to see the face of the second book, we will have to take the top book out of the stack, making the second book the topmost book, exposing it's cover for us to see. If we wanted to add a book to the stack, we would have to put it on the top of the stack. This is exactly how the stack machine works. We create a "stack" of registers, each time we can only read or write to the topmost register of the stack. This method of reading memory is sometimes called (quite fittingly) *last in first out*, or LIFO. In the stack machine, the act of reading the value of the topmost register is called *pop*, and the act of adding a value to the stack is called *push*. 

*But why the stack machine?*
Using a stack machine has a few advantages over the register machine. 


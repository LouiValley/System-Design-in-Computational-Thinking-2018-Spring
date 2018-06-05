# Virtual Machine Part II : Program Control

## Logic Model for This Section

## Why are we here?

We are here because we want more.

Remember the loop statement in our assembly? You just made a simple label "(LOOP)"and then you can just use a "@LOOP" to tell your computer to go to run certain lines of codes.

***Is loop statement, or to be more accurate, "(LOOP)" , necessary in a hack program?***

Absolutely not. If the address of the following line is 143, you can just write "@143" instead of using two lines in your assembly. 

***Then why are there such statements?***

Because we are lazy, and we don't want to count the lines everytime we want to start a loop. We want the assembler to count it for us. You certainly have built this part in your assember. You know all the tricks.

What you might not fully understand is the answer to the subsequent question.

***Is it the assembler that makes your programming work easier?***

The answer is no, it's not the assembler. It's the mind effort you made when you tried hard to simplify things makes it easier. 

***Now you might have already known what we are gonna ask you to do.***

Make it even simpler. Last time you use "@LOOP" to point at one certain line.

This time, we will eventually possess a more powerful language, which enables you to use "call xxx" to instruct your computer to run a subroutine.

***Always remember, the more mind effort you make when designing and manufacturing your tools, the easier the following job will be.***

We would like you to build this amazing function in two steps. First, finish the program flow command, that is,the basic loop statement. And then we go on dealing with the function calling protocol.

## Program flow command

We are no strangers to this part. Last time we implemented the if-goto statement by using two lines like:

* @xxx
* D;JGT

This time we want to simplify them so that we can write codes easier.

There are three types of program flow commands:

* **label  declaration** Label declaration is quite the same as "(LOOP)". We use the pattern "label ***label***" to point at the address of the following line. ***label*** can be any string consisting of numbers, letters, underlines(_), dots(.) and colons(:), and start with non-numbers.
* **goto statement** Goto statement follows the pattern "goto ***label***". It is a unconditional jump to where the ***label*** is pointing at.
* **if-goto statement** This is a conditional jump. First, pop the boolean value from the top of the stack. If it is true, jump to the line which "***label***" is pointing at. Otherwise continue the following lines.

### Some suggestions

1. Whenever you write a program flow command, make sure that the "***label***" is pointing at a line **inside this program**. 
2. Since the subroutines we write may contain same labels, we decided that every ***label***  created in the VM language should gain the counterpart ***functionname$label*** in the assembly.



Quite easy, isn't it? Now you can go to our **project instructions** to start part I. Enjoy!







## Function Calling Protocol

### Background

Let us suppose that you are solving a math problem. At one certain step you suddenly realize that a theorem in one of your textbooks can be applied to this part. You go to your study and find that book, find the page that introduce the theorem, use it, memorize the answer, and then come back to your problem to continue.

We are no strangers to such measures we take when solving problems. And this is exactly how your virtual machine is gonna work. So, let us go into details and see how this **"referring to"** method really works.

First, you need to learn that theorem, or you'll never be able to use it. In our program, it means you'll have to write certain codes to implement that function.~~***(Of course you'll do it!)***~~

Next, remember the name of the function, and in which book this theorem is recorded.  In our program, this is called "***Function Declaration***".

Then the time comes when you need to use that theorem. So you note down the numbers you need and go to that certain page of that certain book. This, is the so-called "***Function Call***" .

Finally with the help of that theorem you managed to get what you want, so you go back to where you were, maybe your desk, find where you stopped and comtinue. We name this procedure "***Return***".

The above three together is what we called the "***Function Calling Protocol***".

Now you've known all the details of this method. We are now going to make it clearer to you.

### The Function Calling Protocol

Remember that all the calculations done by the VM language is conducted in the **STACK**, including the calculations of the main function and the subroutines'. However, the stack itself is totally invisible to our program. That is, the programs cannot see what the stack is like. They can only get access to the stack by using pointers: ARG, LCL, SP, THIS, and THAT. This means that even if ARG is not pointing at the **real** argument segment, the subroutine will not know. It will take what ARG is pointing at as the arguments.

With this feature, we can ***fool*** our subroutines and let all the functions we call happen only in our stack.  

The trick is, whenever we want to call a function, say "Multiply" (whose name was already made a symbol),  we take the following steps:

##### Function Call

(VM code: ***call f n*** )(Note: "***f***" is the function's name and n is the number of the arguments it needs.)

1. Push all the arguments that function needs into the stack.

2. Mark where we stop so that when the subroutine is over, we will know where to go to. Use the VM code   

   * push return-address-multiply

    The label ***"(return-address-multiply)"*** points at the end of this set of codes.(Given below)

3. Store our previous pointers in stack:

   * push LCL
   * push ARG
   * push THIS
   * push THAT

4. Generate our "*fake*" pointers for our subroutine:

   * ARG = SP-n-5
   * LCL = SP

5. Go to our subroutine:

   * goto multiply

6. Label our return address

   * (return-address-multiply)

And then your subroutine, in this case "multiply", will run successfully in our stack. After that, it is time to consider how this will end and go back to continue the main program. That is, the "***Return***".

##### Return

(VM code: ***return***)

1. Store the pointer LCL in a temporary variable **FRAME**:
   * FRAME = LCL
2. Store your return address in a temporary variable **RET**:
   * RET = *(FRAME-5)
3. A VM subroutine always return a value, now you need to pop it out, so:
   * *ARG = pop()
4. Reset all the pointers:
   * SP = ARG+1
   * THAT = *(FRAME-1)
   * THIS = *(FRAME-2)
   * ARG = *(FRAME-3)
   * LCL = *(FRAME-4)
5. Go to return address:
   * goto RET

Now all we lack is to declare a function.

##### Function Declare

(VM code: ***function f k*** )(Note: "***k***" is the number of ***f***'s local variables)

1. Generate a label for your function.
   * (f)
2. Repeat the following code **k** times to initialize the "local" section:
   * push constant 0

**Warnings:**

1. All the VM (pseudo) codes above should be inplemented in assembly.
2. *ARG represents the value stored in ARG.
3. The caller must push necessary arguments, and wait for the callee to return, but this won't be your concern. We hope this will help you understand why there must be a ARG = pop() in the implementation of ***return***.
4. Be careful with your RET's address.





## Project Instructions

~~***(Feel free to ignore this part if you are confident in yourself when building your translator.)***~~

~~***(ALSO feel free to come back when you find it difficult.)***~~



#### Before we start

In order to make sure you've understand the new VM codes, we suggest you write the following program on your own.

Exercise VM-1 

Write the following programs in VM language. Use the given VM translator to get your assembly and run them in the CPUEmulator to test your codes.

* 1) Mult.vm, the multiply subroutine.

  This subroutine should be declared as ***function mult 2***

  This function can multiply the two arguments on the top of the stack and leave the result there.

* 2) Factorial9.vm, the factorial main function.

  This program should be designed to get the value of 9! and store it into static.5




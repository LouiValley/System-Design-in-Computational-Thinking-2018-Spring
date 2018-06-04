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



## What have we already known?

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

1. Push all the arguments that function needs into the stack;

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



##### Function Declare



 
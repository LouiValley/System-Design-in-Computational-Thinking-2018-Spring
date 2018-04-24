# The Assembler
![jicheng](/home/linusboyle/jicheng.jpg)


Starting from basic chips,we build a general-purpose computer. For some implementation details,we choose to simplify the architecture of the machine,enabling a limited set of operations. We take the rather complicated part of logic and arthmetic operations from the hardware layer,and implement these operations by software layer-the first step to do so is to create a notation for the machine language,that is,the Assembly language.Assembler is the program that we build to translate text written in assembly language

## Content
1. Logic Model
2. From Hardware to Software
3. Deal with symbols-Two main passes
4. Translation to Machine Code
---
### Logic Model
__Background__：The general-purpose Hack computer built previously,which provide a set of machine instructions

__Goal__：use the built-in and implemented machine language to build a complete abstract assembly language layer.

__Input__：Hack computer simulator,implementation specification of assembly language,a high-level language.

__Output__：complete implementation of assembly language on Hack platform,using assembler to translate it to machine language
__Process__：

>1. Based on the specification of assembly language for Hack machine language,deal with the general implementation process
2. make the assembler able to deal with symbols and labels
3. implement the rest of the assembler.

__Effects__：provide the first software abstract layer of the language,making it less complicated to implement following software layers
__Outside factors__:We don't need to build an assembler using machine code.Carrying the building process on another computer is OK.

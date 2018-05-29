# Project

In this chapter, you will build an assembler in whatever programming language you like to translate assembly into Hack machine language. Make sure you know all the details of assembly, and start working on it. If you are not so sure, you can go through the following instructions first. 



## Instructions for project Assembler

The following tests will help you focus again on the language features and understand the proper way to write your assembler.

You are recommanded to accomplish the project following a two-tier strategy. First, implement a translator which does not deal with symbols. Then add new functions to your program to deal with symbols.



* A-1  Translate the following assembly codes manually and learn again the grammar in it.

​                This exercise is for non-symbol translator.

| Target Assembly                                              | Your Hack machine language |
| ------------------------------------------------------------ | -------------------------- |
| // This line is to check whether it ignores notes            |                            |
| @/\*Although not required, this note should also be ignored\*/5 |                            |
| D=A-1/\** Some notes are written this way \*/                |                            |
| A=D  // Another way to write A-instructions                  |                            |
| AM=A-1  // You will find such codes powerful in Chapter VM   |                            |
| 0;JMP //  Which line is it pointing at?                      |                            |



Now the first part of the project will be quite easy for you.



* A-2  Translate the following assembly codes manually and focus on your strategy and sequence when translating. You will need them when you start writing the second part.

  This is for assembler dealing with symbols.

| Target Assembly                                              | Your Hack machine language |
| ------------------------------------------------------------ | -------------------------- |
| @Start     // Where is the address?                          |                            |
| M=1                                                          |                            |
| @SUM                                                         |                            |
| M=0                                                          |                            |
| (LOOP1)     //What must you do to this line? And ***When***? |                            |
| @SUM                                                         |                            |
| MD=M+1                                                       |                            |
| @LOOP1                                                       |                            |
| D;JGT                                                        |                            |
| @LOOP2    //Careful! (LOOP) can exist before **AND** after @LOOP |                            |
| //How can you deal with that?                                |                            |
| 0;JMP                                                        |                            |
| @Whatever  //This line will be skipped                       |                            |
| (LOOP2)                                                      |                            |
| @TheEnd                                                      |                            |



* Remark:
* 1. One recommanded way of finish part II is first going through the codes without translating any of them. Instead, form a symbol table which includes all the critical information***(What information?).*** And then with the help of that table, translate the codes in the right way.
  2. Exercise above has three "@Xxx" A-instructions, but only two of them need to be assigned addresses.








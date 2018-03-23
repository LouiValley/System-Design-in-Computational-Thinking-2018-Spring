// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/Or16Way.tst

load Or16Way.hdl,
output-file Or16Way.out,
compare-to Or16Way.cmp,
output-list in%B2.16.2 out%B2.1.2;

set in %B0000000000000000,
eval,
output;

set in %B1111111111111111,
eval,
output;

set in %B0001000000000000,
eval,
output;

set in %B0000000100000000,
eval,
output;

set in %B0010011000000000,
eval,
output;
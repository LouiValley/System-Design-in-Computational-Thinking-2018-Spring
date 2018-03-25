load X.hdl,
output-file X.out,
output-list sel%B1.16.1 out%B1.16.1;

set sel %B0000000000000000,
eval,
output;

set sel %B1111111111111111,
eval,
output;

set sel %B1010101010101010,
eval,
output;

set sel %B0011110011000011,
eval,
output;

set sel %B0001001000110100,
eval,
output;
load Mux.hdl,
output-file Mux.out,
output-list a%B3.1.3 b%B3.1.3 sel%B3.1.3 out%B3.1.3;

set a 0,
set b 0,
set sel 0,
eval,
output;

set a 1,
set b 0,
set sel 0,
eval,
output;

set a 0,
set b 1,
set sel 0,
eval,
output;

set a 1,
set b 1,
set sel 0,
eval,
output;

set a 0,
set b 0,
set sel 1,
eval,
output;

set a 1,
set b 0,
set sel 1,
eval,
output;

set a 0,
set b 1,
set sel 1,
eval,
output;

set a 1,
set b 1,
set sel 1,
eval,
output;
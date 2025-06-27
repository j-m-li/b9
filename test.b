  three registers CPU stack based reverse polish notation.
  2 spaces introduce a comment till the end of line
  1 space introduce an instruction
  0 space is a label
  all characters except 01234abcd, <space> and <newline> are ignored.
  jump labels begin with a 0.
  data labels begin with 00.

  This is the entry point :
01
 14  div
 13  mul
 12  sub
 11  add
 10 001  consta (constant begining with a 0 is a label, otherwise it's a number)
 1a 
 1b 
 1c  
 1d  

 04  gt
 03  ge 
 02  eq
 01  eqz
 00  jump
 0a  nez
 0b  ne
 0c  le
 0d  lt

 a4  loada
 a3  storea
 a2  popa
 a1  pusha
 a0  swapab
 aa  pushb
 ab  popb
 ac  storeb
 ad  loadb

  Load the second trit from data label into register A:
02
 10 001
 a0
 10 1
 11
 ad

   Some data :
001
 ab 03 34 ac 23043ad8ea

 

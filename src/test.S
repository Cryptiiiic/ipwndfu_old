.text

.pool

//Do patches and return
.set JUMP_BACK, 0x180018004
.set BASE,      0x18001C000
.globl _main
_main:
  MOV X5, X0
  LDR X0, =BASE
  movz x1, 0x49e0
  movk x1, 0x528a, lsl 16
  movz x2, 0x5fff, lsl 16
  movk x2, 0xffff
  movz x4, 0xaa00
  movk x4, 0x52a8, lsl 16
  BL next_instr
  BL find_strb
  MOV X0, X5
  RET

next_instr:
  ldr w3, [x0], #4
  and w3, w3, w2
  cmp w3, w1
  b.ne next_instr
  ldr w3, [x0] // load the next instruction
  and w3, w3, w2
  cmp w3, w4 // check if it's the other mov
  b.eq found_first
  ldr w3, [x0,#-8] // load the prev instruction
  and w3, w3, w2
  cmp w3, w4 // check if it's the other mov
  b.ne next_instr
  RET

found_first:
  movz x1, 0x3900, lsl 16
  movz x2, 0xff00, lsl 16
  RET

find_strb:
  ldr w3, [x0], #-4 
  and w3, w3, w2
  cmp w3,w1
  b.ne find_strb
  add x0, x0, 4 // move back
  movz w3, 0x201f
  movk w3, 0xd503, lsl 16
  str w3, [x0] // patch
  RET

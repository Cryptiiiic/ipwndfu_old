.text
.pool
.set patch, 0x100D
.set page, 0x18000c400
.set usb_reset, 0x180003A74
.set new_perm, 0x60000100000625
.set old_perm, 0x1000006a5
.globl _main
_main:
  MSR DAIFSET, #0xF
  LDR X5, =page
  LDR X6, =new_perm
  STR X6, [X5]
  ISB
  DMB SY
  DSB SY
  SYS #0, c8, c7, #0
  DSB SY
  ISB
  LDR X4, =0x100005D70
  LDR W6, =0xD2800000
  STR W6, [X4]
  ADD X4, X4, 4
  LDR W6, =0xD65F03C0
  STR W6, [X4]
  LDR X4, =usb_reset
  LDR W6, 0x00000000
  STR W6, [X4]
  ISB
  LDR X5, =page
  LDR X6, =old_perm
  STR X6, [X5]
  ISB
  ISB
  DMB SY
  ISB
  DSB SY
  SYS #0, c8, c7, #0
  DSB SY
  ISB
  MSR DAIFSET, #0x0
  RET

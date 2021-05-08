asm(
  ".space 0x620, 0x0\n\t"
);
//INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
//GLOBALS
// 0x180018620
// 0x180094d21
void main(void);
void PATCH_INTERPOSER(void);
void PATCH_DEMOTE(void);
void PATCH_BOOTARGS(void);
// void *Amemcpy(void *dst, const void *src, size_t len);
void __attribute__((noinline))      MOV_X0_0(void);
void __attribute__((noinline))      MOV_X0_1(void);
void __attribute__((noinline))      MOV_W1_1(void);
void __attribute__((noinline))      MOV_X9_X8(void);
void __attribute__((noinline))      MOV_X19_X9(void);
void __attribute__((noinline))      RET(void);
void __attribute__((noinline))      NOP(void);
void __attribute__((noinline))      TEST(void);
#define JUMP_BACK_ADDR              0x180018004
#define IMG4_INTERPOSER_ADDR        0x180032148
#define IMG4_PROPERTIES_ADDR        0x180032FF4
#define IMG4_PROPERTIES1_ADDR       0x180032FF8
#define IMG4_PROPERTIES1_PATCH      0x3901E6A1
#define IMG4_PROPERTIES2_ADDR       0x180032FFC
#define IMG4_PROPERTIES2_PATCH      0x3904E3E1
#define IMG4_PROPERTIES3_ADDR       0x180033000
#define IMG4_PROPERTIES3_PATCH      0x390683E1
#define IMG4_PROPERTIES4_ADDR       0x180033004
#define IMG4_PROPERTIES4_PATCH      0x3904C3E1
#define IMG4_PROPERTIES5_ADDR       0x18003300C
#define IMG4_PROPERTIES5_PATCH      0xB807B2A1
#define IMG4_PROPERTIES6_ADDR       0x18007F1C8
#define IMG4_PROPERTIES6_PATCH      0x14000005
#define IMG4_PROPERTIES7_ADDR       0x18007F1E8
#define IMG4_PROPERTIES7_PATCH      0x14000018
#define IMG4_PROPERTIES8_ADDR       0x180032FAC
#define IMG4_PROPERTIES9_ADDR       0x180032D00
#define IMG4_PROPERTIES10_ADDR      0x18003306C
#define IMG4_PROPERTIES11_ADDR      0x180033094
#define IMG4_PROPERTIES12_ADDR      0x1800330BC
#define IMG4_PROPERTIES13_ADDR      0x1800330F8
#define IMG4_PROPERTIES14_ADDR      0x180033114
#define IMG4_PROPERTIES15_ADDR      0x180033120
#define IMG4_PROPERTIES16_ADDR      0x180032E94
#define IMG4_PROPERTIES17_ADDR      0x180032E40
#define IMG4_PROPERTIES18_ADDR      0x180032FA4
#define DEMOTE_ONE_ADDR             0x18003af9c
#define DEMOTE_TWO_ADDR             0x18003afa0
#define DEBUG_ADDR                  0x18003443c
#define BOOT_ARGS_ADDR              0x180094d21
#define BOOT_ARGS2_ADDR             0x18009D1D1
#define BOOT_ARGS_CSEL_ADDR         0x180035834
#define BOOT_ARGS_ADR_ONE_ADDR      0x180035924
#define BOOT_ARGS_ADR_ONE_PATCH     0x3033C573
#define BOOT_ARGS_ADR_TWO_ADDR      0x180035828
#define BOOT_ARGS_ADR_TWO_PATCH     0x3033CD49
#define BOOT_ARGS_STR               "rootdev=nvme_nand0 -v pwr-gating-hack=1 gfx-tlbi-hack=1 sep-pwr-gating-hack=1 amfi=0xff amfi_unrestrict_task_for_pid=1 amfi_allow_any_signature=1 amfi_get_out_of_my_way=1 cs_enforcement_disable=1 serial=3 debug=0x14e"
void    *BOOT_ARGS_ADDR_PTR         = (void*)BOOT_ARGS_ADDR;
// #define BOOT_ARGS_STR               "pwr-gating-hack=1 sep-pwr-gating-hack=1"
//MACROS
#define SET64(addr, val) \
    do { \
        *(volatile uint32_t*)((volatile uint64_t*)(addr)) = *(volatile uint32_t*)((volatile uint64_t*)(&val)); \
    } while(false)
#define SET32(addr, val) \
    do { \
        *(volatile uint32_t*)((volatile uint64_t*)(addr)) = (volatile uint32_t)(val); \
    } while(false)
//FUNCTIONS
void main(void) {
    __asm__ __volatile__("MSR DAIFSET, #0xF");
    // TEST();
    SET64(DEMOTE_ONE_ADDR, MOV_X0_1);
    SET64(DEMOTE_TWO_ADDR, NOP);
    SET64(IMG4_INTERPOSER_ADDR, MOV_X0_0);
    SET64(IMG4_INTERPOSER_ADDR + 4, RET);
    SET64(IMG4_PROPERTIES_ADDR, MOV_W1_1);
    SET32(IMG4_PROPERTIES1_ADDR, IMG4_PROPERTIES1_PATCH);
    SET32(IMG4_PROPERTIES2_ADDR, IMG4_PROPERTIES2_PATCH);
    SET32(IMG4_PROPERTIES3_ADDR, IMG4_PROPERTIES3_PATCH);
    SET32(IMG4_PROPERTIES4_ADDR, IMG4_PROPERTIES4_PATCH);
    SET32(IMG4_PROPERTIES5_ADDR, IMG4_PROPERTIES5_PATCH);
    SET32(IMG4_PROPERTIES6_ADDR, IMG4_PROPERTIES6_PATCH);
    SET32(IMG4_PROPERTIES7_ADDR, IMG4_PROPERTIES7_PATCH);
    SET64(IMG4_PROPERTIES8_ADDR, NOP);
    SET64(IMG4_PROPERTIES9_ADDR, NOP);
    SET64(IMG4_PROPERTIES10_ADDR, NOP);
    SET64(IMG4_PROPERTIES11_ADDR, NOP);
    SET64(IMG4_PROPERTIES12_ADDR, NOP);
    SET64(IMG4_PROPERTIES13_ADDR, NOP);
    SET64(IMG4_PROPERTIES14_ADDR, NOP);
    SET64(IMG4_PROPERTIES15_ADDR, NOP);
    SET64(IMG4_PROPERTIES16_ADDR, NOP);
    SET64(IMG4_PROPERTIES17_ADDR, NOP);
    SET64(IMG4_PROPERTIES18_ADDR, NOP);
    SET64(DEBUG_ADDR, MOV_X0_1);
    SET64(BOOT_ARGS_CSEL_ADDR, MOV_X19_X9);
    SET32(BOOT_ARGS_ADR_ONE_ADDR, BOOT_ARGS_ADR_ONE_PATCH);
    SET32(BOOT_ARGS_ADR_TWO_ADDR, BOOT_ARGS_ADR_TWO_PATCH);
    void *bootargs = (void*)BOOT_ARGS2_ADDR;
    // const char *bootargs_str = (void*)BOOT_ARGS_STR;
    // Amemcpy((void*)BOOT_ARGS_ADDR, "rootdev=nvme_nand0 serial=3 debug=0x14e", sizeof("rootdev=nvme_nand0 serial=3 debug=0x14e"));
    const char *s = BOOT_ARGS_STR;
    size_t len = sizeof(BOOT_ARGS_STR);
    char       *d = bootargs;
    // char       *d2 = bootargs2;
    int        pos = 0, dir = 1;

    if (d > s) {
        dir = -1;
        pos = len - 1;
    }
    
    int i = 0;
    while (len--) {
        if (i>= 1000) break;
        d[pos] = s[pos];
        // d2[pos] = s[pos];
        pos += dir;
        i++;
    }
    // PATCH_INTERPOSER();
    __asm__ __volatile__("ldp x29, x30, [sp]");
    __asm__ __volatile__("ISB");
    __asm__ __volatile__("ISB");
    __asm__ __volatile__("DMB SY");
    __asm__ __volatile__("ISB");
    __asm__ __volatile__("DSB SY");
    __asm__ __volatile__("SYS #0, c8, c7, #0");
    __asm__ __volatile__("DSB SY");
    __asm__ __volatile__("ISB");
    __asm__ __volatile__("MSR DAIFSET, #0x0");
    __asm__ __volatile__("mov x8, %0" : : "r" (JUMP_BACK_ADDR) : );
    __asm__ __volatile__("BR x8");
    // TEST();
}
// void PATCH_INTERPOSER(void) {
//     SET64(IMG4_INTERPOSER_ADDR, MOV_X0_0);
//     SET64(IMG4_INTERPOSER_ADDR + 4, RET);
// }
// void PATCH_DEMOTE(void) {
// }
// void PATCH_BOOTARGS(void) {
//     // void *bootargs = (void*)BOOT_ARGS_ADDR;
//     void *bootargs = (void*)BOOT_ARGS2_ADDR;
//     // const char *bootargs_str = (void*)BOOT_ARGS_STR;
//     // Amemcpy((void*)BOOT_ARGS_ADDR, "rootdev=nvme_nand0 serial=3 debug=0x14e", sizeof("rootdev=nvme_nand0 serial=3 debug=0x14e"));
//     // const char *s = "rootdev=nvme_nand0 pwr-gating-hack=1 sep-pwr-gating-hack=1 serial=3 debug=0x14e";
//     // size_t len = sizeof("rootdev=nvme_nand0 pwr-gating-hack=1 sep-pwr-gating-hack=1 serial=3 debug=0x14e");
//     const char *s = "rootdev=nvme_nand0 -v pwr-gating-hack=1 gfx-tlbi-hack=1 sep-pwr-gating-hack=1 amfi=0xff amfi_unrestrict_task_for_pid=1 amfi_allow_any_signature=1 amfi_get_out_of_my_way=1 cs_enforcement_disable=1 serial=3 debug=0x14e";
//     size_t len = sizeof("rootdev=nvme_nand0 -v pwr-gating-hack=1 gfx-tlbi-hack=1 sep-pwr-gating-hack=1 amfi=0xff amfi_unrestrict_task_for_pid=1 amfi_allow_any_signature=1 amfi_get_out_of_my_way=1 cs_enforcement_disable=1 serial=3 debug=0x14e");
//     char       *d = bootargs;
//     // char       *d2 = bootargs2;
//     int        pos = 0, dir = 1;

//     if (d > s) {
//         dir = -1;
//         pos = len - 1;
//     }
    
//     int i = 0;
//     while (len--) {
//         if (i>= 1000) break;
//         d[pos] = s[pos];
//         // d2[pos] = s[pos];
//         pos += dir;
//         i++;
//     }
// }
// void *Amemcpy(void *dst, const void *src, size_t len)
// {
//     const char *s = src;
//     char       *d = dst;
//     int        pos = 0, dir = 1;

//     if (d > s) {
//         dir = -1;
//         pos = len - 1;
//     }
    
//     int i = 0;
//     while (len--) {
//         if (i>= 1000) break;
//         d[pos] = s[pos];
//         pos += dir;
//         i++;
//     }

//     return dst;
// }
//GADGETS
void __attribute__((noinline)) MOV_X0_0(void) {
    __asm__ __volatile__ ("MOV x0, #0x0");
}
void __attribute__((noinline)) NOP(void) {
    __asm__ __volatile__ ("NOP");
}
void __attribute__((noinline)) MOV_X0_1(void) {
    __asm__ __volatile__ ("MOV x0, #0x1");
}
void __attribute__((noinline)) MOV_W1_1(void) {
    __asm__ __volatile__ ("MOV w1, #0x1");
}
void __attribute__((noinline)) MOV_X9_X8(void) {
    __asm__ __volatile__ ("MOV x9, x8");
}
void __attribute__((noinline)) MOV_X19_X9(void) {
    __asm__ __volatile__ ("MOV x19, x9");
}
void __attribute__((noinline)) RET(void) {
    __asm__ __volatile__ ("RET");
}
void __attribute__((noinline)) __attribute__((optnone)) TEST(void) {
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
    __asm__ __volatile__ ("NOP");
}

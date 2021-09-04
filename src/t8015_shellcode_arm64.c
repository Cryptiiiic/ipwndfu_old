asm(
  ".space 0x620, 0x0\n\t"
);
//INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
//GLOBALS
// 0x180018620
int main(void);
bool __attribute__((noinline)) platform_get_boot_device(int32_t index, int *boot_device, uint32_t *boot_flag, uint32_t *boot_arg);
void __attribute__((noinline)) platform_enable_boot_interface(bool enable, int boot_device, uint32_t boot_arg);
void __attribute__((noinline)) flash_nand_init();
void __attribute__((noinline)) *lookup_blockdev(const char *name);
void __attribute__((noinline)) *lookup_image_in_bdev(const char *name, uint32_t type);
int __attribute__((noinline)) nand_prep();
#define platform_get_boot_device_t          0x10000796c
#define platform_enable_boot_interface_t    0x100007a10
#define flash_nand_init_t                   0x100003a84
#define lookup_blockdev_t                   0x10000C648
#define lookup_image_in_bdev_t              0x100001a4c
//MACROS
//FUNCTIONS
int main(void) {
    int rv = -1;
    rv = nand_prep();
    return rv;
}

int __attribute__((noinline)) nand_prep() {
    __asm__ __volatile__("STP x29, x30, [SP, #0x20]");
    int boot_device = 0;
    uint32_t boot_flag = 0;
    uint32_t boot_arg = 0;
    bool rv = false;
    rv = platform_get_boot_device(0, &boot_device, &boot_flag, &boot_arg);
    if(rv == 0) {
        return -1;
    }
    platform_enable_boot_interface(true, boot_device, boot_arg);
    flash_nand_init();
    const char *bdev = "spi_nand0";
    void *rv2 = lookup_image_in_bdev(bdev, (uint32_t)0x696c6c62/*"illb"*/);
    if(rv2 == 0) {
        return -1;
    }
    __asm__ __volatile__("LDP x29, x30, [SP, #0x20]");
    return 0;
}

bool __attribute__((noinline)) platform_get_boot_device(int32_t index, int *boot_device, uint32_t *boot_flag, uint32_t *boot_arg) {
    __asm__ __volatile__("STP x29, x30, [SP, #0x30]");
    __asm__ __volatile__("MOV x0, %0" : : "r" ((int64_t)index));
    __asm__ __volatile__("MOV x1, %0" : : "r" (boot_device));
    __asm__ __volatile__("MOV x2, %0" : : "r" (boot_flag));
    __asm__ __volatile__("MOV x3, %0" : : "r" (boot_arg));
    bool rv = false;
    __asm__ __volatile__("MOV x8, %0" : : "r" (platform_get_boot_device_t) : );
    __asm__ __volatile__("BLR x8");
    __asm__ __volatile__("MOV x8, x0");
    __asm__ __volatile__("MOV %w0, w8" : "=r" (rv) : );
    __asm__ __volatile__("LDP x29, x30, [SP, #0x30]");
    return rv;
}

void __attribute__((noinline)) platform_enable_boot_interface(bool enable, int boot_device, uint32_t boot_arg) {
    __asm__ __volatile__("STP x29, x30, [SP, #0x40]");
    __asm__ __volatile__("MOV x0, %0" : : "r" ((int64_t)enable) : );
    __asm__ __volatile__("MOV x1, %0" : : "r" ((int64_t)boot_device) :);
    __asm__ __volatile__("MOV x2, %0" : : "r" ((uint64_t)boot_arg) : );
    __asm__ __volatile__("MOV x8, %0" : : "r" (platform_enable_boot_interface_t) : );
    __asm__ __volatile__("BLR x8");
    __asm__ __volatile__("LDP x29, x30, [SP, #0x40]");
    return;
}

void __attribute__((noinline)) flash_nand_init() {
    __asm__ __volatile__("STP x29, x30, [SP, #0x50]");
    __asm__ __volatile__("MOV x8, %0" : : "r" (flash_nand_init_t) : );
    __asm__ __volatile__("BLR x8");
    __asm__ __volatile__("LDP x29, x30, [SP, #0x50]");
    return;
}

void __attribute__((noinline)) *lookup_blockdev(const char *name) {
    __asm__ __volatile__("STP x29, x30, [SP, #0x60]");
    __asm__ __volatile__("MOV x0, %0" : : "r" (name) : );
    void *rv = NULL;
    __asm__ __volatile__("MOV x8, %0" : : "r" (lookup_blockdev_t) : );
    __asm__ __volatile__("BLR x8");
    __asm__ __volatile__("MOV x8, x0");
    __asm__ __volatile__("MOV %x0, x8" : "=r" (rv) : );
    __asm__ __volatile__("LDP x29, x30, [SP, #0x60]");
    return rv;
}

void __attribute__((noinline)) *lookup_image_in_bdev(const char *name, uint32_t type) {
    __asm__ __volatile__("STP x29, x30, [SP, #0x70]");
    __asm__ __volatile__("MOV x0, %0" : : "r" (name) : );
    __asm__ __volatile__("MOV x1, %0" : : "r" ((uint64_t)type) : );
    void *rv = NULL;
    __asm__ __volatile__("MOV x8, %0" : : "r" (lookup_image_in_bdev_t) : );
    __asm__ __volatile__("BLR x8");
    __asm__ __volatile__("MOV x8, x0");
    __asm__ __volatile__("MOV %x0, x8" : "=r" (rv) : );
    __asm__ __volatile__("LDP x29, x30, [SP, #0x70]");
    return rv;
}

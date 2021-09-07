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
int flash_nand_init(uint32_t boot_arg);
int nand_prep();
//void *lookup_blockdev(const char *name);
#define platform_get_boot_device_t          0x10000796c
#define platform_enable_boot_interface_t    0x100007a10
#define flash_nand_init_t                   0x100003a84
#define lookup_blockdev_t                   0x10000C648
#define lookup_image_in_bdev_t              0x100001a4c
#define flash_nand_init_gpio_t              0x1000075cc
#define calloc_t                            0x10000d238
#define free_t                              0x10000d2e4
#define strlen_t                            0x10000ee08
#define malloc_t                            0x10000d0d4
#define platform_get_spi_frequency_t        0x100007b28
#define flash_spi_read_wrapper_unknown_t    0x100003c8c
#define nand_readRange_t                    0x1000075cc
#define construct_blockdev_t                0x10000c7fc
#define nand_read_block_hook_t              0x100003e44
#define register_blockdev_t                 0x10000c690
#define spi_nand0_t                         0x100017246
//STRUCTS
struct blockdev {
    struct blockdev *next;
    uint32_t flags;
    uint32_t block_size;
    uint32_t block_count;
    uint32_t block_shift;
    uint64_t total_len;
    uint32_t alignment;
    uint32_t alignment_shift;
    int (*read_hook)(struct blockdev *, void * ptr, uint64_t offset, uint64_t len);
    int (*read_block_hook)(struct blockdev *, void * ptr, uint32_t block, uint32_t count);
    int (*write_hook)(struct blockdev *, const void * ptr, uint64_t offset, uint64_t len);
    int (*write_block_hook)(struct blockdev *, const void * ptr, uint32_t block, uint32_t count);
    int (*erase_hook)(struct blockdev *, uint64_t offset, uint64_t len);
    char name[16];
    uint64_t protect_start;
    uint64_t protect_end;
};

struct spi_blockdev {
    struct blockdev bdev;
    uint64_t *handle;
    int (*readRange)(struct spi_nanddev *handle, uint8_t *ptr, uint32_t offset, uint32_t length);
};

struct spi_nanddev {
    struct spi_blockdev sdev;
    uint32_t spiBus;
    uint32_t spiChipSelect;
    uint32_t spiFrequency;
    uint32_t spiMode;
    uint32_t flags;
    uint32_t blockSize;//I.E. We can determine this by comparing decompilation of flash_nor_init and flash_nand_init. Both fields were 0x1000
    uint32_t blockCount;
    uint32_t some_field5;
    uint32_t defaultTimeout;
    uint32_t some_field7;
};
//MACROS
//FUNCTIONS
int main(void) {
    return nand_prep();
}

int flash_nand_init(uint32_t boot_arg) {
    //func ptr init
    int (*flash_nand_init_gpio)() = flash_nand_init_gpio_t;
    void *(*calloc)(size_t a1, size_t a2) = calloc_t;
    void (*free)(void *a1) = free_t;
//    size_t (*strlen)(char const *s) = strlen_t;
//    size_t (*malloc)(size_t size) = malloc_t;
    uint32_t (*platform_get_spi_frequency)() = platform_get_spi_frequency_t;
    int (*flash_spi_read_wrapper_unknown)(struct spi_nanddev *dev, uint32_t *a2, uint32_t *a3) = flash_spi_read_wrapper_unknown_t;
    int (*nand_readRange)(struct spi_nanddev *, uint8_t *, uint32_t, uint32_t) = nand_readRange_t;
    int (*construct_blockdev)(struct blockdev *, char *, uint64_t, uint32_t) = construct_blockdev_t;
    int (*nand_read_block_hook)(struct spi_nanddev *, uint8_t *, uint32_t, uint32_t) = nand_read_block_hook_t;
    int (*register_blockdev)((struct blockdev *)) = register_blockdev_t;
    //
    char *platform_blockdev_name = spi_nand0_t;
    struct spi_nanddev *dev = NULL;
    int result = -1;
    uint32_t var1;
    uint32_t var2;
    unsigned int var3;
    dev = (struct spi_nanddev *)(*calloc)(1, 0xa8);
    if (boot_arg == 0 && dev != NULL) {
        dev->spiBus = 0;
        dev->spiFrequency = (*platform_get_spi_frequency)();
        dev->spiMode = 1;
        dev->defaultTimeout = 1000000;
        result = (*flash_nand_init_gpio)();
        if (result > -1) {
            var1 = 0;
            result = (*flash_spi_read_wrapper_unknown)(dev, &var1, &var2);
            if (result == 0) {
                dev->some_field5 = var2;
                var1 = 1;
                result = (*flash_spi_read_wrapper_unknown)(dev,&var1,&var2);
                if (result == 0) {
                    dev->blockSize = 0x1000;
                    dev->blockCount = var2;
                    dev->flags = 0;
                    (dev->sdev).handle = (uint64_t)dev;
                    (dev->sdev).readRange = (*nand_readRange);
                    if (platform_blockdev_name != NULL) {
                        (*construct_blockdev)((struct blockdev *)dev, platform_blockdev_name, (var2 << 0xc), 0x1000);
                        (dev->sdev).bdev.read_block_hook = (*nand_read_block_hook);
                        (*register_blockdev)((struct blockdev *)dev);
                        var3 = 0;
                        goto exit;
                    }
                }
            }
        }
    }
    if (dev) {
        (*free)(dev);
    }
    var3 = 0xffffffff;

exit:
    return var3 & var3 >> 0x1f;
}

int nand_prep() {
    int boot_device = 0;
    uint32_t boot_flag = 0;
    uint32_t boot_arg = 0;
    const char *platform_blockdev_name = (const char*)spi_nand0_t;
    bool (*platform_get_boot_device)(int32_t index, int *boot_device, uint32_t *boot_flag, uint32_t *boot_arg) = platform_get_boot_device_t;
    bool rv = (*platform_get_boot_device)(0, &boot_device, &boot_flag, &boot_arg);
    if(!rv) {
        return -1;
    }
    void (*platform_enable_boot_interface)(bool enable, int boot_device, uint32_t boot_arg) = platform_enable_boot_interface_t;
    (*platform_enable_boot_interface)(true, boot_device, boot_arg);
    flash_nand_init(boot_arg);
    uint32_t type = (uint32_t)"illb";
    void *(*lookup_image_in_bdev)(const char *name, uint32_t type) = lookup_image_in_bdev_t;
    void *rv2 = (*lookup_image_in_bdev)(platform_blockdev_name, type);
    if(rv2 == 0) {
        return -1;
    }
    return 0;
}
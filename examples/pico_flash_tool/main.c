#include "pico/stdio.h"
#include "pico/stdlib.h"

#include "boards/pico_ice.h"

#include "ice_flash.h"
#include "ice_sdk.h"
#include "ice_usb.h"

// address to work upon
uint32_t repl_address;

// for repl_ungetchar() to take back the last character from repl_getchar():
int repl_last_char;
bool repl_last_held;

static int repl_getchar(void)
{
    int c;

    if (repl_last_held) {
        repl_last_held = false;
        return repl_last_char;
    }

    // busy-wait with a slow delay: this is for interactive I/O, no need to be fast
    while ((c = getchar_timeout_us(10000)) == PICO_ERROR_TIMEOUT)
        // call tud_task() since we are blocking, similar to preemptive multitasking
        tud_task();
    if (c == '\r' || c == '\n')
        printf("\r\n");
    else
        putchar(c);
    return c;
}

static void repl_ungetchar(int c)
{
    assert(!repl_last_held);
    repl_last_char = c;
    repl_last_held = true;
}

static inline bool repl_parse_error(char *msg, char c)
{
    // reset whatever was being input
    repl_last_held = false;

    printf("\nerror: expected %s got '%c'\n", msg, c);
    return false;
}

static bool repl_expect(char *str)
{
    for (char *s = str; *s != '\0'; s++)
    return true;
}

static bool xdigit(uint8_t *nibble, int c)
{
    // if we could read a hex digit, append it
    if (c >= '0' && c <= '9') {
        *nibble = c - '0';
        return true;
    }
    if (c >= 'A' && c <= 'F') {
        *nibble = 10 + c - 'A';
        return true;
    }
    if (c >= 'a' && c <= 'f') {
        *nibble = 10 + c - 'a';
        return true;
    }

    // if not a hex digit, put it back onto the stream and stop here
    repl_ungetchar(c);
    return false;
}

static inline bool repl_parse_u32(uint32_t *u32)
{
    bool read_anything = false;
    int c;

    *u32 = 0;
    for (uint8_t u; xdigit(&u, c = repl_getchar()); *u32 = *u32 << 4 | u)
        read_anything = true;

    if (!read_anything)
            return repl_parse_error("hex digit", c);

    // At least one hex digit read, valid input
    return true;
}

static bool repl_parse_newline(void)
{
    int c;

    switch (c = repl_getchar()) {
    case '\r':
    case '\n':
    case EOF:
        return true;
    default:
        repl_ungetchar(c);
        return repl_parse_error("newline", c);
    }
}

static void repl_command_write(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};

    if (!repl_parse_newline())
        return;
    ice_flash_program_page(repl_address, buf);
    printf("%s 0x%08X done\r\n", __func__, repl_address);
}

static inline void memdump(uint8_t const *buf, size_t sz, uint32_t addr)
{
    while (sz > 0) {
        printf("0x%08X:", addr);
        for (size_t n = 0x20; sz > 0 && n > 0; sz--, buf++, n--, addr++)
            printf(" %02X", *buf);
        printf("\n");
    }
}

static void repl_command_read(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};

    if (!repl_parse_newline())
        return;
    ice_flash_read(repl_address, buf, sizeof buf);
    printf("%s 0x%08X done\r\n", __func__, repl_address);
    memdump(buf, sizeof buf, repl_address);
}

static void repl_command_erase(void)
{
    if (!repl_parse_newline())
        return;
    ice_flash_erase_sector(repl_address);
    printf("%s 0x%08X done\r\n", __func__, repl_address);
}

static void repl_command_zero(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};

    if (!repl_parse_newline())
        return;
    ice_flash_program_page(repl_address, buf);
    printf("%s 0x%08X done\r\n", __func__, repl_address);
}

static void repl_command_sleep(void)
{
    if (!repl_parse_newline())
        return;
    ice_flash_sleep();
    printf("%s done\r\n", __func__);
}

static void repl_command_wakeup(void)
{
    if (!repl_parse_newline())
        return;
    ice_flash_wakeup();
    printf("%s done\r\n", __func__);
}

static void repl_command_init(void)
{
    if (!repl_parse_newline())
        return;
    ice_flash_init();
    printf("%s done\r\n", __func__);
}

static void repl_set_address(void)
{
    uint8_t c;

    if ((c = repl_getchar()) != 'x') {
        repl_parse_error("x", c);
        return;
    }
    if (!repl_parse_u32(&repl_address))
        return;
    if (!repl_parse_newline())
        return;
}

static void repl_command_page(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};

    ice_flash_read(repl_address, buf, sizeof buf);
    memdump(buf, sizeof buf, repl_address);
    repl_address += 0x1000;
}

int main(void)
{
    // Let the FPGA boot up from flash
    ice_sdk_init();

    // Enable USB-UART #0 output
    stdio_init_all();

    for (;;) {
        tud_task();

        printf("0x%08X> ", repl_address);

        switch (repl_getchar()) {
        case '0':
            repl_set_address();
            break;
        case 'w':
            repl_command_write();
            break;
        case 'r':
            repl_command_read();
            break;
        case 'e':
            repl_command_erase();
            break;
        case 'z':
            repl_command_zero();
            break;
        case 's':
            repl_command_sleep();
            break;
        case 'u':
            repl_command_wakeup();
            break;
        case 'i':
            repl_command_init();
            break;
        case '\r':
        case '\n':
            repl_command_page();
            break;
        default:
            printf("\navailable commands: w r e z s u i +\n");
            printf("or an address: 0x00000000\n");
            break;
        }
    }

    return 0;
}

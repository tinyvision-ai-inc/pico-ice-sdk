#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "uf2.h"
#include "libuf2.h"

#define uf2_check(e) uf2_check_(e, #e)

bool uf2_exit_on_error = true;

static inline void uf2_check_(bool exp, char *text)
{
    if (!exp) {
        fprintf(stderr, "format error, this condition failed: %s\n", text);
        if (uf2_exit_on_error)
            exit(1);
    }
}

static inline bool is_little_endian(void)
{
    union { uint8_t u8[4]; uint32_t u32[1]; } u = { .u32 = { 0x00000001 } };
    return (u.u8[0] == 0x01);
}

static inline uint32_t bswap_32(uint32_t u32)
{
    return (((u32) & 0xFF000000) >> 24 | ((u32) & 0x00FF0000) >> 8 |
            ((u32) & 0x0000FF00) << 8  | ((u32) & 0x000000FF) << 24);
}

static inline uint32_t le32(uint32_t u32)
{
    return is_little_endian() ? u32 : bswap_32(u32);
}

void uf2_fatal(char const *msg)
{
    perror(msg);
    exit(1);
}

void uf2_convert_endianness(UF2_Block *uf2)
{
    uf2->magicStart0 = le32(uf2->magicStart0);
    uf2->magicStart1 = le32(uf2->magicStart1);
    uf2->flags       = le32(uf2->flags);
    uf2->targetAddr  = le32(uf2->targetAddr);
    uf2->payloadSize = le32(uf2->payloadSize);
    uf2->blockNo     = le32(uf2->blockNo);
    uf2->numBlocks   = le32(uf2->blockNo);
    uf2->reserved    = le32(uf2->reserved);
    uf2->magicEnd    = le32(uf2->magicEnd);
}

bool uf2_read_block(UF2_Block *uf2, FILE *in)
{
    size_t sz;

    // could fail if struct packing is wrong, unlikely
    assert(sizeof *uf2 == 512);

    sz = fread(uf2, 1, sizeof *uf2, in);
    if (feof(in))
        return false;
    if (ferror(in))
        uf2_fatal("reading UF2 data in");
    if (sz != sizeof *uf2)
        uf2_fatal("file size is not a multiple of 512 bytes");

    // convert endianness of each 32-bit fields
    uf2_convert_endianness(uf2);

    // check for format sanity
    uf2_check(uf2->magicStart0 == UF2_MAGIC_START0);
    uf2_check(uf2->magicStart1 == UF2_MAGIC_START1);
    uf2_check(uf2->payloadSize > 0);

    return true;
}

/*
 * Set the following fields:
 * - uf2.flags        (optional)
 * - uf2.targetAddr   (only on first call, updated by this function)
 * - uf2.payloadSize  (required)
 * - uf2.blockNo      (only on first call, updated by this function)
 * - uf2.data         (required)
 */
void uf2_write_block(UF2_Block *uf2, FILE *out)
{
    // check for library misuse
    assert(uf2->payloadSize > 0);

    // fill default values
    uf2->magicStart0 = UF2_MAGIC_START0;
    uf2->magicStart1 = UF2_MAGIC_START1;
    uf2->numBlocks = 0; // not implemented
    uf2->magicEnd = UF2_MAGIC_END;

    // prepare and write the UF2
    uf2_convert_endianness(uf2);
    assert(sizeof *uf2 == 512);
    fwrite(uf2, 1, sizeof *uf2, out);

    // convert the endianess back
    uf2_convert_endianness(uf2);

    // update the fields to keep track of file position
    uf2->targetAddr += UF2_PAYLOAD_SIZE;
    uf2->blockNo += UF2_PAYLOAD_SIZE;

    if (ferror(out))
        uf2_fatal("writing UF2 data out");
}

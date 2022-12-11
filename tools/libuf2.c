#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libuf2.h"
#include "uf2.h"

#define uf2_check(e) uf2_check_(e, #e)

bool uf2_exit_on_error = true;

static inline void uf2_check_(bool exp, char *text)
{
    if (!exp) {
        fprintf(stderr, "format error: expected %s\n", text);
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
    if (errno > 0)
        perror(msg);
    else
        fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void uf2_convert_endianness(UF2_Block *uf2)
{
    uf2->magicStart0 = le32(uf2->magicStart0);
    uf2->magicStart1 = le32(uf2->magicStart1);
    uf2->flags       = le32(uf2->flags);
    uf2->targetAddr  = le32(uf2->targetAddr);
    uf2->payloadSize = le32(uf2->payloadSize);
    uf2->blockNo     = le32(uf2->blockNo);
    uf2->numBlocks   = le32(uf2->numBlocks);
    uf2->reserved    = le32(uf2->reserved);
    uf2->magicEnd    = le32(uf2->magicEnd);
}

/// Read an UF2 block from a file.
/// @param uf2 Block structure to store the data.
/// @param in File pointer to read from.
/// @return True while end of file not reached.
bool uf2_read_block(UF2_Block *uf2, FILE *in)
{
    size_t sz;

    // could fail if struct packing is wrong, unlikely
    assert(sizeof *uf2 == 512);

    sz = fread(uf2, 1, sizeof *uf2, in);
    if (ferror(in))
        uf2_fatal("reading UF2 data in");
    if (sz == 0 && feof(in))
        return false;
    if (sz != sizeof *uf2)
        uf2_fatal("file size is not a multiple of 512 bytes");

    // convert endianness of each 32-bit fields
    uf2_convert_endianness(uf2);

    // check for format sanity
    uf2_check(uf2->magicStart0 == UF2_MAGIC_START0);
    uf2_check(uf2->magicStart1 == UF2_MAGIC_START1);
    uf2_check(uf2->payloadSize > 0);

    return !feof(in);
}

/// Set the numbmer of blocks according to the input file size.
/// @param uf2 Block to store the result into.
/// @param in File pointer to a seekable stream.
void uf2_set_numBlocks(UF2_Block *uf2, FILE *in)
{
    long sz;

    if (fseek(in, 0L, SEEK_END) == -1)
        uf2_fatal("ftell: searching the input file end to estimate size");
    if ((sz = ftell(in)) == -1)
        uf2_fatal("ftell: searching the input file end to estimate size");

    if (fseek(in, 0L, SEEK_SET) == -1)
        uf2_fatal("fseek: restoring input file position to the beginning");

    if (sz % 512 != 0)
        uf2_fatal("file size is not a multiple of 512");

    uf2->numBlocks = sz / UF2_PAYLOAD_SIZE;
}

/// Set the following fields:
/// - uf2.flags        (optional)
/// - uf2.targetAddr   (only on first call, updated by this function)
/// - uf2.payloadSize  (required)
/// - uf2.blockNo      (only on first call, updated by this function)
/// - uf2.data         (required)
/// @param uf2 Block structure to write.
/// @param out File pointer to write to.
void uf2_write_block(UF2_Block *uf2, FILE *out)
{
    // check for library misuse
    assert(uf2->payloadSize > 0);

    // fill default values
    uf2->magicStart0 = UF2_MAGIC_START0;
    uf2->magicStart1 = UF2_MAGIC_START1;
    uf2->magicEnd = UF2_MAGIC_END;

    // prepare and write the UF2
    uf2_convert_endianness(uf2);
    assert(sizeof *uf2 == 512);
    fwrite(uf2, 1, sizeof *uf2, out);

    // convert the endianess back
    uf2_convert_endianness(uf2);

    // update the fields to keep track of file position
    uf2->targetAddr += UF2_PAYLOAD_SIZE;
    uf2->blockNo++;

    if (ferror(out))
        uf2_fatal("writing UF2 data out");
}

static void uf2_data_dump(uint8_t *buf, size_t buf_sz, uint32_t base_address, FILE *fp)
{
    uint32_t addr = 0;

    while (buf_sz > 0) {
        size_t row_sz = buf_sz < 0x20 ? buf_sz : 0x20;

        printf("0x%08X:", base_address + addr);
        for (; row_sz > 0; row_sz--, addr++)
            printf(" %02X", *buf++, buf_sz--);
        printf("\r\n");
    }
}

/// Dump the content of an UF2 file in human-readable format.
/// @param uf2 Block structure to dump.
/// @param out File pointer to write to.
void uf2_dump(UF2_Block *uf2, FILE *out)
{
    fprintf(out, "\n");
    fprintf(out, "uint32_t magicStart0=0x%08X\n", uf2->magicStart0);
    fprintf(out, "uint32_t magicStart1=0x%08X\n", uf2->magicStart1);
    fprintf(out, "uint32_t flags=0x%08X\n", uf2->flags);
    fprintf(out, "uint32_t targetAddr=0x%08X\n", uf2->targetAddr);
    fprintf(out, "uint32_t payloadSize=0x%08X\n", uf2->payloadSize);
    fprintf(out, "uint32_t blockNo=0x%08X\n", uf2->blockNo);
    fprintf(out, "uint32_t numBlocks=0x%08X\n", uf2->numBlocks);
    fprintf(out, "uint32_t reserved=0x%08X\n", uf2->reserved);

    // raw data;
    uint8_t data[476];
    fprintf(out, "uint32_t data[476]=\n");
    uf2_data_dump(uf2->data, uf2->payloadSize, uf2->targetAddr, out);

    for (uint32_t i = uf2->payloadSize; i < sizeof uf2->data; i++)
        uf2_check(uf2->data[i] == 0x00);

    // store magic also at the end to limit damage from partial block reads
    fprintf(out, "uint32_t magicEnd=0x%08X\n", uf2->magicEnd);

}

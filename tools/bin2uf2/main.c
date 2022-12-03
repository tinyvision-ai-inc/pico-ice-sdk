#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "uf2.h"

static void fatal(char *msg)
{
    perror(msg);
    exit(1);
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

#define WRITTEN_BLOCK_SIZE 256

void elf2uf2(FILE *in, FILE *out, uint32_t blockNo, uint32_t targetAddr)
{
    do
    {
        UF2_Block uf2;

        memset(&uf2, 0, sizeof uf2);
        uf2.magicStart0 = le32(UF2_MAGIC_START0);
        uf2.magicStart1 = le32(UF2_MAGIC_START1);
        uf2.blockNo = le32(blockNo);
        uf2.targetAddr = le32(targetAddr);
        uf2.magicEnd = le32(UF2_MAGIC_END);
        uf2.payloadSize = le32(fread(uf2.data, 1, WRITTEN_BLOCK_SIZE, in));

        blockNo += 1;
        targetAddr += WRITTEN_BLOCK_SIZE;

        if (uf2.payloadSize == 0)
            break;

        assert(sizeof uf2 == 512);
        fwrite(&uf2, 1, sizeof uf2, out);

        if (ferror(out))
            fatal("writing UF2 data out");

    }
    while (!ferror(in) && !feof(in));
}

int main(void)
{
    elf2uf2(stdin, stdout, 0, 0);
    return (0);
}

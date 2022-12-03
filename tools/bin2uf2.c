#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "uf2.h"
#include "libuf2.h"

void bin2uf2(FILE *in, FILE *out, uint32_t blockNo, uint32_t targetAddr)
{
    UF2_Block uf2 = { .targetAddr = targetAddr };

    // fill the data payload from the input file and store its size
    while ((uf2.payloadSize = fread(uf2.data, 1, UF2_PAYLOAD_SIZE, in)) > 0)
        // encode it as UF2 and write it out
        uf2_write_block(&uf2, out);

    if (ferror(in))
        uf2_fatal("reading binary data in");
}

int main(void)
{
    bin2uf2(stdin, stdout, 0, 0);
    return (0);
}

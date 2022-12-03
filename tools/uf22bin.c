#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "uf2.h"
#include "libuf2.h"

void uf22bin(FILE *in, int fd_out, off_t start_address)
{
    UF2_Block uf2;
    size_t output_len = 0;

    // read UF2 blocks from input file
    while (uf2_read_block(&uf2, in))
    {
        off_t off;

        // adjust output file offset for the first byte to be at start_address
        if (uf2.targetAddr < start_address)
            uf2_fatal("data from UF2 before the base offset specified on command line");
        off = uf2.targetAddr - start_address;

        // write data out at the specified offset filling gaps with '\0'
        if (pwrite(fd_out, uf2.data, uf2.payloadSize, off) < uf2.payloadSize)
                perror("writing binary data out");
    }
}

int main(void)
{
    uf22bin(stdin, STDOUT_FILENO, 0);
    return (0);
}

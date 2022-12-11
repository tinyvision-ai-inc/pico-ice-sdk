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

void usage(char const *arg0)
{
    fprintf(stderr, "usage: %s [file.uf2]\n", arg0);
    exit(1);
}

int main(int argc, char **argv)
{
    char const *arg0 = *argv;
    FILE *in = stdin;

    if (argc > 2)
        usage(arg0);

    if (argc == 2) {
        if ((in = fopen(argv[1], "r")) == NULL)
            uf2_fatal(argv[1]);
    }

    uf22bin(in, STDOUT_FILENO, 0);
    return 0;
}

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "boards/pico_ice.h"
#include "libuf2.h"

void bin2uf2(FILE *in, FILE *out, uint32_t targetAddr, uint32_t familyID) {
    UF2_Block uf2 = { .targetAddr = targetAddr, .flags = UF2_FLAG_FAMILYID_PRESENT, .reserved = familyID };

    // compute the number of blocks in the input file, must be seekable
    uf2_set_numBlocks(&uf2, in);
    uf2.payloadSize = UF2_PAYLOAD_SIZE;

    // fill the data payload from the input file and store its size
    for (size_t sz; (sz = fread(uf2.data, 1, UF2_PAYLOAD_SIZE, in)) > 0;) {

        // fill the rest of the block with zeros
        memset(uf2.data + sz, '\0', sizeof uf2.data - sz);

        // encode it as UF2 and write it out
        uf2_write_block(&uf2, out);
    }

    if (ferror(in)) {
        uf2_fatal("reading binary data in");
    }
}

void usage(char const *arg0) {
    fprintf(stderr, "usage: %s [-f familyID] [-o file.uf2] file.bin\n", arg0);
    fprintf(stderr, "usage: %s [-f familyID] [-o file.uf2] [0x00000000 file.bin]...\n", arg0);
    exit(1);
}

int main(int argc, char **argv) {
    char const *arg0 = *argv;
    FILE *out = stdout;
    FILE *in;
    uint32_t familyID = UF2_DEFAULT_FAMILY_ID;
    char *p;

    arg0 = *argv;
    for (int c; (c = getopt(argc, argv, "f:o:")) != -1;) {
        switch (c) {
        case 'f':
            familyID = strtoul(optarg, &p, 0);
            if (*p != '\0')
                uf2_fatal("invalid family ID number format");
            break;
        case 'o':
            if ((out = fopen(optarg, "w")) == NULL)
                uf2_fatal(optarg);
            break;
        default:
            usage(arg0);
        }
    }
    argv += optind;
    argc -= optind;

    // By default, read from stdin
    if (argc == 0) {
        usage(arg0);

    // If only one argument, guess that the address is 0x00000000
    } else if (argc == 1) {
        if ((in = fopen(argv[0], "r")) == NULL)
            uf2_fatal(argv[0]);
        bin2uf2(in, out, 0x00000000, familyID);
        return 0;

    // If more than two, assume a mapping of multiple files and addresses
    } else if (argc % 2 != 0) {
        fprintf(stderr, "error: wrong number of arguments\n");
        usage(arg0);
    }

    // We loop through every address-file pair of argument and append them to the UF2 file
    for (; argc > 0; argc -= 2, argv += 2) {
        uint32_t targetAddr;

        fprintf(stderr, "addr=%s file=%s\n", argv[0], argv[1]);

        targetAddr = strtoul(argv[0], &p, 0);
        if (*p != '\0') {
            uf2_fatal("invalid targetAddr number format");
        }

        if (strcmp(argv[1], "-") == 0) {
            in = stdin;
        } else {
            if ((in = fopen(argv[1], "r")) == NULL) {
                uf2_fatal(argv[1]);
            }
        }
        bin2uf2(in, out, targetAddr, familyID);
    }
    return (0);
}

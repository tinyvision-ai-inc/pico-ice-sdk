#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libuf2.h"
#include "uf2.h"

void uf2dump(FILE *in, FILE *out) {
    UF2_Block uf2 = {0};

    while (uf2_read_block(&uf2, in)) {
        uf2_dump(&uf2, out);
    }
}

void usage(char const *arg0) {
    fprintf(stderr, "usage: %s [file.uf2]\n", arg0);
    exit(1);
}

int main(int argc, char **argv) {
    char const *arg0 = *argv;
    FILE *in = stdin;

    if (argc > 2)
        usage(arg0);

    if (argc == 2) {
        if ((in = fopen(argv[1], "r")) == NULL)
            uf2_fatal(argv[1]);
    }

    uf2dump(in, stdout);
    return 0;
}

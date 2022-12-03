#include <stddef.h>
#include "uf2.h"
#include "libuf2.h"

void uf2dump(FILE *in, FILE *out)
{
    UF2_Block uf2 = {0};

    while (uf2_read_block(&uf2, in)) {
        uf2_dump(&uf2, out);
    }
}

int main(void)
{
    uf2dump(stdin, stdout);
}

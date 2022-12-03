#ifndef LIBUF2_H
#define LIBUF2_H

#include <stdbool.h>

#define UF2_PAYLOAD_SIZE 256

extern bool uf2_exit_on_error;

void uf2_fatal(char const *msg);
bool uf2_read_block(UF2_Block *uf2, FILE *in);
void uf2_write_block(UF2_Block *uf2, FILE *out);

#endif

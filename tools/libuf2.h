#ifndef LIBUF2_H
#define LIBUF2_H

#include <stdio.h>
#include <stdbool.h>
#include "uf2.h"

// Generated at random for the pico-ice as advised by https://github.com/microsoft/uf2/
#define UF2_DEFAULT_FAMILY_ID 0x792e7263

#define UF2_PAYLOAD_SIZE 256

#define UF2_FLAG_NOT_MAIN_FLASH            0x00000001
#define UF2_FLAG_FILE_CONTAINER            0x00001000
#define UF2_FLAG_FAMILYID_PRESENT          0x00002000
#define UF2_FLAG_MD5_CHECKSUM_PRESENT      0x00004000
#define UF2_FLAG_EXTENSION_TAGS_PRESENT    0x00008000

extern bool uf2_exit_on_error;

void uf2_fatal(char const *msg);
void uf2_set_numBlocks(UF2_Block *uf2, FILE *in);
bool uf2_read_block(UF2_Block *uf2, FILE *in);
void uf2_write_block(UF2_Block *uf2, FILE *out);
void uf2_dump(UF2_Block *uf2, FILE *out);

#endif

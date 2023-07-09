#ifndef MTTSTR_H
#define MTTSTR_H

#include <stddef.h>
#include <limits.h>

void *mttstr_mem_rev(void *mem, size_t n);

#define VTF_MINUS_SIGN 1
#define VTF_PLUS_SIGN 2
#define VTF_UCASE 4
#define VTF_LEFT_ALN 8
#define VTF_PREP_ZEROS 16
#define VTF_NULL_TERM 32

#define IS_VAL_NEG(val) (val & (size_t)1 << (sizeof(val) * CHAR_BIT - 1))

size_t mttstr_val_to_fstr(char *fstr, size_t val, int base, size_t width, int fs);
size_t mttstr_val_to_fstr_s(char *fstr, size_t c, size_t val, int base, size_t width, int fs);

#define FTV_SKIP_BLNKS 1
#define FTV_MINUS_SIGN 2
#define FTV_PLUS_SIGN 4
#define FTV_MCASE 8
#define FTV_UCASE 16

size_t mttstr_fstr_to_val(char *fstr, char **last, int base, int fs);
size_t mttstr_fstr_to_val_s(char *fstr, size_t n, char **last, int base, int fs);

#endif
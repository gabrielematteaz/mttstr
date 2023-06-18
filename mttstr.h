#ifndef MTTSTR_H
#define MTTSTR_H

#include <stddef.h>
#include <limits.h>

void *mttstr_mem_rev(void *mem, size_t n);

#define VTS_NULL_TERM 1

#define UVTS_LCASE 2

size_t mttstr_uval_to_str(char *str, size_t uval, int base, int fs);
size_t mttstr_uval_to_str_s(char *str, size_t size, size_t uval, int base, int fs);

#define IVTS_PSIGN 2

#define IS_UVAL_NEG(uval) (uval & 1ULL << (sizeof(uval) * CHAR_BIT - 1))

size_t mttstr_ival_to_str(char *str, size_t ival, int fs);
size_t mttstr_ival_to_str_s(char *str, size_t size, size_t ival, int fs);

#define VTFS_LEFT_ALN 4
#define VTFS_PREP_ZEROS 8

size_t mttstr_uval_to_fstr(char *fstr, size_t uval, int base, size_t width, int fls);
size_t mttstr_uval_to_fstr_s(char *fstr, size_t size, size_t uval, int base, size_t width, int fls);

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, size_t width, int fls);
size_t mttstr_ival_to_fstr_s(char *fstr, size_t size, size_t ival, size_t width, int fls);

#define STV_SKIP_BLNKS 1

#define STUV_MCASE 2
#define STUV_LCASE 4

size_t mttstr_str_to_uval(char *str, char **last, int base, int fs);
size_t mttstr_strn_to_uval(char *str, size_t n, char **last, int base, int fs);

#define STIV_PSIGN 2

size_t mttstr_str_to_ival(char *str, char **last, int fs);
size_t mttstr_strn_to_ival(char *str, size_t n, char **last, int fs);

#endif
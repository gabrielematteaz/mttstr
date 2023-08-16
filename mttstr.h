#ifndef MTTSTR_H
#define MTTSTR_H

#include <stdlib.h>

#define FMT_FS_UCASE 0x00
#define FMT_FS_LCASE 0x01
#define FMT_FS_MCASE 0x02
#define FMT_FS_LEFT_FILL 0x00
#define FMT_FS_INT_FILL 0x04
#define FMT_FS_RIGHT_FILL 0x08
#define FMT_FS_DO_NOT_NULL_TERM 0x00
#define FMT_FS_NULL_TERM 0x10

#define FMT_DEF_DEC { '+', '-', ' ', 10, FMT_FS_LEFT_FILL | FMT_FS_NULL_TERM, 0 }
#define FMT_DEF_HEX { 0, 0, ' ', 16, FMT_FS_MCASE | FMT_FS_LEFT_FILL | FMT_FS_NULL_TERM, 0 }

#define WFMT_DEF_DEC { L'+', L'-', L' ', 10, FMT_FS_LEFT_FILL | FMT_FS_NULL_TERM, 0 }
#define WFMT_DEF_HEX { 0, 0, L' ', 16, FMT_FS_MCASE | FMT_FS_LEFT_FILL | FMT_FS_NULL_TERM, 0 }

#define IS_VAL_NEG(val) (val & (size_t)1 << (sizeof(val) * CHAR_BIT - 1))

void *mttstr_mem_rev(void *mem, size_t n);
void *mttstr_wmem_rev(void *wmem, size_t n);

struct mttstr_fmt_t
{
	char plus, minus, fill;
	int base;
	int fs;
	size_t width;
};

struct mttstr_wfmt_t
{
	wchar_t plus, minus, fill;
	int base;
	int fs;
	size_t width;
};

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt);
char *mttstr_ival_to_alloc_fstr(size_t ival, struct mttstr_fmt_t fmt);

size_t mttstr_ival_to_wfstr(wchar_t *wfstr, size_t ival, struct mttstr_wfmt_t wfmt);
wchar_t *mttstr_ival_to_alloc_wfstr(size_t ival, struct mttstr_wfmt_t wfmt);

size_t mttstr_fstr_to_ival(const char *fstr, const char **last, struct mttstr_fmt_t fmt);

size_t mttstr_wfstr_to_ival(const wchar_t *wfstr, const wchar_t **wlast, struct mttstr_wfmt_t wfmt);

#endif
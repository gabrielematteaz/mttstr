#ifndef MTTSTR_H
#define MTTSTR_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

void *mttstr_mem_rev(void *mem, size_t n);
void *mttstr_wmem_rev(void *wmem, size_t n);

struct mttstr_fmt_t
{
	uint8_t base;
	char plus, minus, fill;
	uint8_t flags;
	uint8_t width;
};

struct mttstr_wfmt_t
{
	uint8_t base;
	wchar_t wplus, wminus, wfill;
	uint8_t flags;
	uint8_t width;
};

#define FMT_FLAGS_UCASE 0
#define FMT_FLAGS_LCASE 1
#define FMT_FLAGS_MCASE 2
#define FMT_FLAGS_LEFT_FILL 0
#define FMT_FLAGS_INT_FILL 4
#define FMT_FLAGS_RIGHT_FILL 8
#define FMT_FLAGS_DO_NOT_NULL_TERM 0
#define FMT_FLAGS_NULL_TERM 16
#define FMT_DEF_DEC { 10, '+', '-', ' ', FMT_FLAGS_LEFT_FILL | FMT_FLAGS_NULL_TERM, 0 }
#define FMT_DEF_HEX { 16, 0, 0, ' ', FMT_FLAGS_MCASE | FMT_FLAGS_LEFT_FILL | FMT_FLAGS_NULL_TERM, 0 }
#define WFMT_DEF_DEC { 10, L'+', L'-', L' ', FMT_FLAGS_LEFT_FILL | FMT_FLAGS_NULL_TERM, 0 }
#define WFMT_DEF_HEX { 16, 0, 0, L' ', FMT_FLAGS_MCASE | FMT_FLAGS_LEFT_FILL | FMT_FLAGS_NULL_TERM, 0 }

#define IS_VAL_NEG(val) (val & (size_t)1 << (sizeof(val) * CHAR_BIT - 1))

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt);
char *mttstr_ival_to_fstr_alloc(size_t ival, struct mttstr_fmt_t fmt);
size_t mttstr_ival_to_wfstr(wchar_t *wfstr, size_t ival, struct mttstr_wfmt_t wfmt);
wchar_t *mttstr_ival_to_wfstr_alloc(size_t ival, struct mttstr_wfmt_t wfmt);

size_t mttstr_fstr_to_ival(const char *fstr, const char **last, struct mttstr_fmt_t fmt);
size_t mttstr_wfstr_to_ival(const wchar_t *wfstr, const wchar_t **wlast, struct mttstr_wfmt_t wfmt);

#endif
#ifndef MTTSTR_H
#define MTTSTR_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

void *mttstr_mem_rev(void *mem, size_t n);

struct mttstr_fmt_t
{
	char plus, minus, fill;
	uint8_t base, fill_mode, flags;
	uint16_t width;
};

enum mttstr_fmt_fill_mode_t
{
	NONE,
	UNKNOWN,
	LEFT,
	INTERNAL,
	RIGHT,
};

enum mttstr_fmt_flags_t
{
	UCASE = 0,
	NO_NULL_TERM = 0,
	LCASE = 1,
	MCASE = 2,
	NULL_TERM = 4,
};

#define IS_VAL_NEG(val) (val & (size_t)1 << (sizeof(val) * CHAR_BIT - 1))

uint16_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt);

size_t mttstr_fstr_to_ival(char *fstr, char **last, struct mttstr_fmt_t fmt);

#endif
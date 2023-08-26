#ifndef MTTSTR_H
#define MTTSTR_H

#include <stddef.h>
#include <limits.h>

#define IS_VAL_NEG(val) (val & (size_t)1 << (sizeof(val) * CHAR_BIT - 1))

enum mttstr_fmt_ltrcase_t
{
	MIXED,
	UPPER,
	LOWER
};

enum mttstr_fmt_fillmode_t
{
	LEFT,
	INTERNAL,
	RIGHT
};

struct mttstr_fmt_t
{
	char plus, minus, fill;
	int base;
	enum mttstr_fmt_ltrcase_t ltrcase;
	enum mttstr_fmt_fillmode_t fillmode;
	int nonullterm;
	size_t width;
};

void *mttstr_mem_rev(void *mem, size_t n);

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt);

size_t mttstr_fstr_to_ival(const char *fstr, const char **last, struct mttstr_fmt_t fmt);

#endif
# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Structs
- mttstr_fmt_t
- mttstr_wfmt_t

# Macros
- FMT_FLAGS_UCASE
- FMT_FLAGS_LCASE
- FMT_FLAGS_MCASE
- FMT_FLAGS_LEFT_FILL
- FMT_FLAGS_INT_FILL
- FMT_FLAGS_RIGHT_FILL
- FMT_FLAGS_DO_NOT_NULL_TERM
- FMT_FLAGS_NULL_TERM
- FMT_DEF_DEC
- FMT_DEF_HEX
- WFMT_DEF_DEC
- WFMT_DEF_HEX
- IS_VAL_NEG(val)

# Functions
- mttstr_mem_rev
- mttstr_ival_to_fstr
- mttstr_ival_to_fstr_alloc
- mttstr_ival_to_wfstr
- mttstr_ival_to_wfstr_alloc
- mttstr_fstr_to_ival
- mttstr_wfstr_to_ival

# Example
```c
#include "mttstr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	char **av = argv + 1, **avc = argv + argc, fstr[32];
	struct mttstr_fmt_t from = FMT_DEF_DEC, to = FMT_DEF_HEX;
	size_t ival;

	while (av < avc)
	{
		ival = mttstr_fstr_to_ival(*av, NULL, from);
		printf("%zu '%s'\n", mttstr_ival_to_fstr(fstr, ival, to), fstr);
		av++;
	}

	return 0;
}
```

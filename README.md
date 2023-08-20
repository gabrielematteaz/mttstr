# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Structs
- mttstr_fmt_t

# Macros
- FMT_FS_MCASE
- FMT_FS_UCASE
- FMT_FS_LCASE
- FMT_FS_LEFT_FILL
- FMT_FS_INT_FILL
- FMT_FS_RIGHT_FILL
- FMT_FS_NULL_TERM
- FMT_FS_DO_NOT_NULL_TERM
- IS_VAL_NEG(val)

# Functions
- mttstr_mem_rev
- mttstr_ival_to_fstr
- mttstr_ival_to_fstr_alloc
- mttstr_fstr_to_ival

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

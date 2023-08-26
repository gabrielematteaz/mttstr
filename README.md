# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Macros
- IS_VAL_NEG(val)

# Enums
- mttstr_fmt_ltrcase_t
- mttstr_fmt_fillmode_t

# Structs
- mttstr_fmt_t

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
	char **av = argv + 1, **avc = argv + argc;
	struct mttstr_fmt_t from = { '+', '-', ' ', 10, .fillmode = LEFT }, to = { 0, 0, .base = 16, LOWER, LEFT, 0, 0 };

	while (av < avc)
	{
		size_t ival = mttstr_fstr_to_ival(*av, NULL, from);

		av++;

		char fstr[32];

		printf("%zu '%s'\n", mttstr_ival_to_fstr(fstr, ival, to), fstr);
	}

	return 0;
}
```

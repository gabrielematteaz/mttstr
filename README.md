# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Structs
- mttstr_fmt_t

# Enums
- mttstr_fmt_fill_mode_t

# Macros
- IS_VAL_NEG(val)

# Flags
- FMT_FLAGS_LCASE
- FMT_FLAGS_MCASE
- FMT_FLAGS_NULL_TERM

# Functions
- mttstr_mem_rev
- mttstr_ival_to_fstr
- mttstr_fstr_to_ival

# Example
```c
#include "mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *arg, **av = argv + 1, *fstr;
	struct mttstr_fmt_t ftivfmt = { '+', '-', ' ', 10, left_fill, 0, 0 };
	size_t ival, fstrsize;
	struct mttstr_fmt_t ivtffmt = { 0, 0, '0', 16, int_fill, FMT_FLAGS_LCASE | FMT_FLAGS_NULL_TERM, 16 };

	while (1)
	{
		arg = *av;
		
		if (arg == NULL) break;

		ival = mttstr_fstr_to_ival(arg, NULL, ftivfmt);
		fstrsize = mttstr_ival_to_fstr(NULL, ival, ivtffmt);
		fstr = malloc(fstrsize + 1);

		if (fstr != NULL)
		{
			mttstr_ival_to_fstr(fstr, ival, ivtffmt);
			puts(fstr);
			free(fstr);
		}

		av++;
	}

	return 0;
}
```

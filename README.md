# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Enums
- mttstr_fillmode_t
- mttstr_flags_t

# Macros
- IS_VAL_NEG(val)

# Functions
- mttstr_mem_rev
- mttstr_ival_to_fstr
- mttstr_fstr_to_ival

# Example
```c
#include "mttlib/mttstr/mttstr.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	size_t width = mttstr_ival_to_fstr(NULL, ~0, 16, 0, 0, 0, 0, 0, 0), ival, len;
	char *fstr = malloc(width + 1), **av, *arg;

	if (fstr)
	{
		av = argv + 1;
		arg = *av;

		while (arg != NULL)
		{
			ival = mttstr_fstr_to_ival(arg, NULL, 10, '+', '-', ' ', LEFT, 0);
			mttstr_ival_to_fstr(fstr, ival, 16, 0, 0, ' ', LEFT, width, NULL_TERM);
			puts(fstr);
			av++;
			arg = *av;
		}

		free(fstr);
	}

	return 0;
}
```

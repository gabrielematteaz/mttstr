# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Structs
- mttstr_fmt_t

# Enums
- mttstr_fmt_fill_mode_t
- mttstr_fmt_flags_t

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
	struct mttstr_fmt_t fmt = { '+', '-', ' ', 10, LEFT, NULL_TERM };
	char *fstr, **args, *arg;
	size_t ival;

	fmt.width = mttstr_ival_to_fstr(NULL, ~0, fmt);
	fstr = malloc(fmt.width + 1);

	if (fstr != NULL)
	{
		args = argv + 1;

		while (1)
		{
			arg = *args;

			if (arg == NULL) break;

			args++;
			ival = mttstr_fstr_to_ival(arg, NULL, fmt);
			mttstr_ival_to_fstr(fstr, ival, fmt);
			puts(fstr);
		}

		free(fstr);
	}

	return 0;
}
```

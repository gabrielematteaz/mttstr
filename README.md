# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Enums
- mttstr_fmt_fillmode_t
- mttstr_fmt_flags_t

# Structs
- mttstr_fmt_t

# Macros
- IS_VAL_NEG(val)

# Functions
- mttstr_mem_rev
- mttstr_ival_to_fstr
- mttstr_fstr_to_ival

# Example
```c
#include "mttlib/mttstr/mttstr.h"
#include <stdio.h>

int main(void)
{
	char fstr[32];
	struct mttstr_fmt_t fmt = { 0, 0, '0', 16, LEFT, NULL_TERM, 16 };

	mttstr_ival_to_fstr(fstr, -648022, fmt);
	puts(fstr);

	return 0;
}
```

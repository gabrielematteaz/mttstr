# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Macros
- IS_VAL_NEG(val)

# Flags
- VTF_MINUS_SIGN
- VTF_PLUS_SIGN
- VTF_UCASE
- VTF_LEFT_ALN
- VTF_PREP_ZEROS
- VTF_NULL_TERM
- FTV_SKIP_BLNKS
- FTV_MINUS_SIGN
- FTV_PLUS_SIGN
- FTV_MCASE
- FTV_UCASE

# Functions
- mttstr_mem_rev
- mttstr_val_to_str
- mttstr_val_to_str_s
- mttstr_str_to_val
- mttstr_str_to_val_s

# Example
```c
#include "mttstr.h"

int main()
{
  char fstr[8];

  if (mttstr_val_to_fstr_s(fstr, sizeof(fstr), 9034, 16, VTF_UCASE | VTF_NULL_TERM))
  {
    /* ... */
  }
}
```

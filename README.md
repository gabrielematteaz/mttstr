# mttstr
My personal C library which provides various utility functions for handling string manipulation and conversion operations.

# Macros
- IS_UVAL_NEG(uval)

# Flags
- VTS_NULL_TERM
- UVTS_LCASE
- IVTS_PSIGN
- VTFS_LEFT_ALN
- VTFS_PREP_ZEROS
- STV_SKIP_BLNKS
- STUV_MCASE
- STUV_LCASE
- STIV_PSIGN

# Functions
- mttstr_mem_rev
- mttstr_uval_to_str
- mttstr_uval_to_str_s
- mttstr_ival_to_str
- mttstr_ival_to_str_s
- mttstr_uval_to_fstr
- mttstr_uval_to_fstr_s
- mttstr_ival_to_fstr
- mttstr_ival_to_fstr_s
- mttstr_str_to_uval
- mttstr_strn_to_uval
- mttstr_str_to_ival
- mttstr_strn_to_ival

# Example
```c
#include "mttstr.h"

int main()
{
  char str[10];

  if (mttstr_uval_to_str_s(str, 10, 9034, 16, VTS_NULL_TERM | UVTS_LCASE))
  {
    /* ... */
  }
}
```

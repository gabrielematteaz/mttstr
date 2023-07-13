#include "mttstr.h"

void *mttstr_mem_rev(void *mem, size_t n)
{
	char *m, *mn, mc;

	if (mem != NULL)
	{
		m = mem, mn = m + n;

		while (m < mn)
		{
			mn--;
			mc = *m;
			*m = *mn;
			m++;
			*mn = mc;
		}
	}

	return mem;
}

uint16_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt)
{
	size_t len, i;
	char *f, a, rem, *fw;

	while (2 <= fmt.base && fmt.base <= 36)
	{
		if (fstr == NULL)
		{
			if (fmt.minusc && IS_VAL_NEG(ival))
			{
				ival = -ival;
				len = 1;
			}
			else if (fmt.plusc) len = 1;
			else len = 0;

			do
			{
				ival /= fmt.base;
				len++;
			} while (ival);

			if (len < fmt.width) len = fmt.width;
		}
		else
		{
			if (fmt.minusc && IS_VAL_NEG(ival))
			{
				i = ival;
				ival = -ival;
			}
			else i = 0;

			f = fstr;

			if (fmt.base > 10)
			{
				a = fmt.flags & FMT_FLAGS_LCASE ? 87 : 55;

				do
				{
					rem = ival % fmt.base;
					ival /= fmt.base;
					*f = (rem < 10 ? '0' : a) + rem;
					f++;
				} while (ival);
			}
			else
			{
				do
				{
					*f = '0' + ival % fmt.base;
					ival /= fmt.base;
					f++;
				} while (ival);
			}

			switch (fmt.fill_mode)
			{
			default:
				if IS_VAL_NEG(i)
				{
					*f = fmt.minusc;
					f++;
				}
				else if (fmt.plusc)
				{
					*f = fmt.plusc;
					f++;
				}

				fw = fstr + fmt.width;

				while (f < fw)
				{
					*f = fmt.fillc;
					f++;
				}

				len = f - fstr;
				mttstr_mem_rev(fstr, len);

				break;
			case right_fill:
				if IS_VAL_NEG(i)
				{
					*f = fmt.minusc;
					f++;
				}
				else if (fmt.plusc)
				{
					*f = fmt.plusc;
					f++;
				}

				mttstr_mem_rev(fstr, f - fstr);
				fw = fstr + fmt.width;

				while (f < fw)
				{
					*f = fmt.fillc;
					f++;
				}

				len = f - fstr;

				break;
			case int_fill:
				fw = fstr + fmt.width - 1;

				while (f < fw)
				{
					*f = fmt.fillc;
					f++;
				}

				if IS_VAL_NEG(i)
				{
					*f = fmt.minusc;
					f++;
				}
				else if (fmt.plusc)
				{
					*f = fmt.plusc;
					f++;
				}
				else if (f == fw)
				{
					*f = fmt.fillc;
					f++;
				}

				len = f - fstr;
				mttstr_mem_rev(fstr, len);

				break;
			}

			if (fmt.flags) *f = 0;
		}

		return len;
	}

	return 0;
}

size_t mttstr_fstr_to_ival(char *fstr, char **last, struct mttstr_fmt_t fmt)
{
	size_t sign, ival;
	char ucasemax, lcasemax, fc, min, max;

	if (fstr != NULL && 2 <= fmt.base && fmt.base <= 36)
	{
		ival = 0;

		switch (fmt.fill_mode)
		{
		default:
			fc = *fstr;

			if (fmt.minusc && fc == '-')
			{
				fstr++;
				fc = *fstr;
				sign = -1;
			}
			else
			{
				if (fmt.plusc && fc == '+')
				{
					fstr++;
					fc = *fstr;
				}

				sign = 1;
			}

	nofill:
			if (fmt.base > 10)
			{
				if (fmt.flags & FMT_FLAGS_MCASE)
				{
					ucasemax = 'A' + fmt.base - 10;
					lcasemax = ucasemax + 32;

					while (1)
					{
						if ('0' <= fc && fc <= '9') ival = ival * fmt.base + fc - '0';
						else if ('A' <= fc && fc < ucasemax) ival = ival * fmt.base + fc - 55;
						else if ('a' <= fc && fc < lcasemax) ival = ival * fmt.base + fc - 87;
						else break;

						fstr++;
						fc = *fstr;
					}
				}
				else
				{
					min = fmt.flags & FMT_FLAGS_LCASE ? 'a' : 'A';
					max = min + fmt.base - 10;

					while (1)
					{
						if ('0' <= fc && fc <= '9') ival = ival * fmt.base + fc - '0';
						else if (min <= fc && fc < max) ival = ival * fmt.base + fc - min + 10;
						else break;

						fstr++;
						fc = *fstr;
					}
				}
			}
			else
			{
				max = '0' + fmt.base;

				while ('0' <= fc && fc < max)
				{
					ival = ival * fmt.base + fc - '0';
					fstr++;
					fc = *fstr;
				}
			}

			break;
		case unk_fill:
			fc = *fstr;

			if (fc == fmt.fillc)
			{
				fstr++;

				goto leftfill;
			}
			else goto intfill;
		case left_fill:
	leftfill:
			fc = *fstr;

			while (fc == fmt.fillc)
			{
				fstr++;
				fc = *fstr;
			}

			if (fmt.minusc && fc == '-')
			{
				fstr++;
				fc = *fstr;
				sign = -1;
			}
			else
			{
				if (fmt.plusc && fc == '+')
				{
					fstr++;
					fc = *fstr;
				}

				sign = 1;
			}

			goto nofill;
		case int_fill:
			fc = *fstr;

	intfill:
			if (fmt.minusc && fc == '-')
			{
				fstr++;
				fc = *fstr;
				sign = -1;
			}
			else
			{
				if (fmt.plusc && fc == '+')
				{
					fstr++;
					fc = *fstr;
				}

				sign = 1;
			}

			while (fc == fmt.fillc)
			{
				fstr++;
				fc = *fstr;
			}

			goto nofill;
		}

		if (last != NULL) *last = fstr;

		return sign * ival;
	}

	if (last != NULL) *last = NULL;

	return 0;
}
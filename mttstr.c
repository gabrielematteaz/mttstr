#include "mttstr.h"

void *mttstr_mem_rev(void *mem, size_t len)
{
	char *m, *mn, mc;

	if (mem)
	{
		m = mem, mn = m + len;

		while (m < mn) mc = *m, *m++ = *--mn, *mn = mc;
	}

	return mem;
}

size_t mttstr_val_to_fstr(char *fstr, size_t val, int base, size_t width, int fs)
{
	size_t v, len;
	char *f, a, rem, *fw;

	if (2 <= base && base <= 36)
	{
		if (fstr)
		{		
			if (fs & VTF_MINUS_SIGN && IS_VAL_NEG(val)) v = val, val = -val;
			else v = 0;

			f = fstr;

			if (base > 10)
			{
				a = fs & VTF_UCASE ? 55 : 87;

				do rem = val % base, val /= base, *f++ = (rem < 10 ? '0' : a) + rem; while (val);
			}
			else do *f++ = '0' + val % base, val /= base; while (val);

			if (fs & VTF_LEFT_ALN)
			{
				if IS_VAL_NEG(v) *f++ = '-';
				else if (fs & VTF_PLUS_SIGN) *f++ = '+';

				mttstr_mem_rev(fstr, f - fstr), fw = fstr + width;

				while (f < fw) *f++ = ' ';

				len = f - fstr;
			}
			else
			{
				if (fs & VTF_PREP_ZEROS)
				{
					fw = fstr + width - 1;

					while (f < fw) *f++ = '0';

					if IS_VAL_NEG(v) *f++ = '-';
					else if (fs & VTF_PLUS_SIGN) *f++ = '+';
					else if (f == fw) *f++ = '0';
				}
				else
				{
					if IS_VAL_NEG(v) *f++ = '-';
					else if (fs & VTF_PLUS_SIGN) *f++ = '+';

					fw = fstr + width;

					while (f < fw) *f++ = ' ';
				}

				len = f - fstr, mttstr_mem_rev(fstr, len);
			}

			if (fs & VTF_NULL_TERM) *f = 0;
		}
		else
		{
			len = fs & VTF_MINUS_SIGN || fs & VTF_PLUS_SIGN ? 1 : 0;

			do val /= base, len++; while (val);

			if (len < width) len = width;
		}

		return len;
	}

	return 0;
}

size_t mttstr_val_to_fstr_s(char *fstr, size_t n, size_t val, int base, size_t width, int fs)
{
	size_t v, len;
	char *f, *fn, a, rem, *fw;

	if (2 <= base && base <= 36 && width <= n)
	{
		if (fstr)
		{		
			if (fs & VTF_MINUS_SIGN && IS_VAL_NEG(val)) v = val, val = -val;
			else v = 0;

			f = fstr, fn = f + n;

			if (base > 10)
			{
				a = fs & VTF_UCASE ? 55 : 87;

				do
				{
					if (f == fn) return 0;

					rem = val % base, val /= base, *f++ = (rem < 10 ? '0' : a) + rem;
				} while (val);
			}
			else
			{
				do
				{
					if (f == fn) return 0;

					*f++ = '0' + val % base, val /= base;
				} while (val);
			}

			if (fs & VTF_LEFT_ALN)
			{
				if IS_VAL_NEG(v) *f++ = '-';
				else if (fs & VTF_PLUS_SIGN) *f++ = '+';

				mttstr_mem_rev(fstr, f - fstr), fw = fstr + width;

				while (f < fw) *f++ = ' ';

				len = f - fstr;
			}
			else
			{
				if (fs & VTF_PREP_ZEROS)
				{
					fw = fstr + width - 1;

					while (f < fw) *f++ = '0';

					if IS_VAL_NEG(v)
					{
						if (f == fn) return 0;

						*f++ = '-';
					}
					else if (fs & VTF_PLUS_SIGN)
					{
						if (f == fn) return 0;

						*f++ = '+';
					}
					else if (f == fw) *f++ = '0';
				}
				else
				{
					if IS_VAL_NEG(v)
					{
						if (f == fn) return 0;

						*f++ = '-';
					}
					else if (fs & VTF_PLUS_SIGN)
					{
						if (f == fn) return 0;

						*f++ = '+';
					}

					fw = fstr + width;

					while (f < fw) *f++ = ' ';
				}

				len = f - fstr, mttstr_mem_rev(fstr, len);
			}

			if (fs & VTF_NULL_TERM && f < fn) *f = 0;
		}
		else
		{
			len = fs & VTF_MINUS_SIGN || fs & VTF_PLUS_SIGN ? 1 : 0;

			do val /= base, len++; while (val);

			if (len < width) len = width;
		}

		return len;
	}

	return 0;
}

size_t mttstr_fstr_to_val(char *fstr, char **last, int base, int fs)
{
	char fc, lmax, umax, min, max;
	size_t sign, val;

	if (fstr && 2 <= base && base <= 36)
	{
		if (fs & FTV_SKIP_BLNKS) while (*fstr == ' ') fstr++;

		fc = *fstr;

		if (fs & FTV_MINUS_SIGN && fc == '-') fc = *++fstr, sign = -1;
		else
		{
			if (fs & FTV_PLUS_SIGN && fc == '+') fc = *++fstr;

			sign = 1;
		}

		val = 0;

		if (base > 10)
		{
			if (fs & FTV_MCASE)
			{
				lmax = 'a' + base - 10, umax = lmax - 32;

				while (1)
				{
					if ('0' <= fc && fc <= '9') val = val * base + fc - '0';
					else if ('a' <= fc && fc < lmax) val = val * base + fc - 87;
					else if ('A' <= fc && fc < umax) val = val * base + fc - 55;
					else break;

					fc = *++fstr;
				}
			}
			else
			{
				min = fs & FTV_UCASE ? 'A' : 'a', max = min + base - 10;

				while (1)
				{
					if ('0' <= fc && fc <= '9') val = val * base + fc - '0';
					else if (min <= fc && fc < max) val = val * base + fc - min + 10;
					else break;

					fc = *++fstr;
				}
			}
		}
		else
		{
			max = '0' + base;

			while ('0' <= fc && fc < max) val = val * base + fc - '0', fc = *++fstr;
		}

		if (last) *last = fstr;

		return sign * val;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_fstr_to_val_s(char *fstr, size_t n, char **last, int base, int fs)
{
	return 0;
}
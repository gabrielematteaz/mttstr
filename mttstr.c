#include "mttstr.h"

void *mttstr_mem_rev(void *mem, size_t n)
{
	if (mem)
	{
		char *m = mem, *mn = m + n, mc;

		while (m < mn) mc = *m, *m++ = *--mn, *mn = mc;
	}

	return mem;
}

size_t mttstr_uval_to_str(char *str, size_t uval, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char *s = str;
		size_t n;

		if (base > 10)
		{
			char a = fs & UVTS_LCASE ? 87 : 55;

			do
			{
				char rm = uval % base;

				uval /= base, *s++ = (rm < 10 ? '0' : a) + rm;
			} while (uval);
		}
		else do *s++ = '0' + uval % base, uval /= base; while (uval);

		n = s - str, mttstr_mem_rev(str, n);

		if (fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_uval_to_str_s(char *str, size_t size, size_t uval, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char *s = str, *ss = s + size;
		size_t n;

		if (base > 10)
		{
			char a = fs & UVTS_LCASE ? 87 : 55;

			do
			{
				char rm;

				if (s == ss) return 0;
				
				rm = uval % base;

				uval /= base, *s++ = (rm < 10 ? '0' : a) + rm;
			} while (uval);
		}
		else
		{
			do
			{
				if (s == ss) return 0;

				*s++ = '0' + uval % base, uval /= base;
			} while (uval);
		}

		n = s - str, mttstr_mem_rev(str, n);

		if (s < ss && fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_str(char *str, size_t ival, int fs)
{
	if (str)
	{
		size_t iv = ival, n;
		char *s = str;

		if IS_UVAL_NEG(ival) ival = -ival;

		do *s++ = '0' + ival % 10, ival /= 10; while (ival);

		if IS_UVAL_NEG(iv) *s++ = '-';
		else if (fs & IVTS_PSIGN) *s++ = '+';

		n = s - str, mttstr_mem_rev(str, n);

		if (fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_str_s(char *str, size_t size, size_t ival, int fs)
{
	if (str)
	{
		size_t iv = ival, n;
		char *s = str, *ss = s + size;

		if IS_UVAL_NEG(ival) ival = -ival;

		do
		{
			if (s == ss) return 0;

			*s++ = '0' + ival % 10, ival /= 10;
		} while (ival);

		if (s == ss) return 0;

		if IS_UVAL_NEG(iv) *s++ = '-';
		else if (fs & IVTS_PSIGN) *s++ = '+';

		n = s - str, mttstr_mem_rev(str, n);

		if (s < ss && fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_uval_to_fstr(char *fstr, size_t uval, int base, size_t width, int fls)
{
	if (fstr && 2 <= base && base <= 36)
	{
		char *fs = fstr, *fsw = fs + width;
		size_t n;

		if (base > 10)
		{
			char a = fls & UVTS_LCASE ? 87 : 55;

			do
			{
				char rm = uval % base;

				uval /= base, *fs++ = (rm < 10 ? '0' : a) + rm;
			} while (uval);
		}
		else do *fs++ = '0' + uval % base, uval /= base; while (uval);

		if (fls & VTFS_LEFT_ALN)
		{
			mttstr_mem_rev(fstr, fs - fstr);

			while (fs < fsw) *fs++ = ' ';

			n = fs - fstr;
		}
		else
		{
			char c = fls & VTFS_PREP_ZEROS ? '0' : ' ';

			while (fs < fsw) *fs++ = c;

			n = fs - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fls & VTS_NULL_TERM) *fs = 0;

		return n;
	}

	return 0;
}

size_t mttstr_uval_to_fstr_s(char *fstr, size_t size, size_t uval, int base, size_t width, int fls)
{
	if (fstr && 2 <= base && base <= 36 && width <= size)
	{
		char *fs = fstr, *fss = fs + size, *fsw = fs + width;
		size_t n;

		if (base > 10)
		{
			char a = fls & UVTS_LCASE ? 87 : 55;

			do
			{
				char rm;

				if (fs == fss) return 0;
				
				rm = uval % base;

				uval /= base, *fs++ = (rm < 10 ? '0' : a) + rm;
			} while (uval);
		}
		else
		{
			do
			{
				if (fs == fss) return 0;

				*fs++ = '0' + uval % base, uval /= base;
			} while (uval);
		}

		if (fls & VTFS_LEFT_ALN)
		{
			mttstr_mem_rev(fstr, fs - fstr);

			while (fs < fsw) *fs++ = ' ';

			n = fs - fstr;
		}
		else
		{
			char c = fls & VTFS_PREP_ZEROS ? '0' : ' ';

			while (fs < fsw) *fs++ = c;

			n = fs - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fs < fss && fls & VTS_NULL_TERM) *fs = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, size_t width, int fls)
{
	if (fstr)
	{
		size_t iv = ival, n;
		char *fs = fstr, *fsw = fs + width;

		if IS_UVAL_NEG(ival) ival = -ival;

		do *fs++ = '0' + ival % 10, ival /= 10; while (ival);

		if (fls & VTFS_LEFT_ALN)
		{
			if IS_UVAL_NEG(ival) *fs++ = '-';
			else if (fls & IVTS_PSIGN) *fs++ = '+';

			mttstr_mem_rev(fstr, fs - fstr);

			while (fs < fsw) *fs++ = ' ';

			n = fs - fstr;
		}
		else
		{
			if (fls & VTFS_PREP_ZEROS)
			{
				if IS_UVAL_NEG(iv)
				{
					fsw--;

					while (fs < fsw) *fs++ = '0';

					*fs++ = '-';
				}
				else if (fls & IVTS_PSIGN)
				{
					fsw--;

					while (fs < fsw) *fs++ = '0';

					*fs++ = '+';
				}
				else while (fs < fsw) *fs++ = '0';
			}
			else
			{
				if IS_UVAL_NEG(ival) *fs++ = '-';
				else if (fls & IVTS_PSIGN) *fs++ = '+';

				while (fs < fsw) *fs++ = ' ';
			}

			n = fs - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fls & VTS_NULL_TERM) *fs = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_fstr_s(char *fstr, size_t size, size_t ival, size_t width, int fls)
{
	if (fstr && width <= size)
	{
		size_t iv = ival, n;
		char *fs = fstr, *fss = fs + size, *fsw = fs + width;

		if IS_UVAL_NEG(ival) ival = -ival;

		do
		{
			if (fs == fss) return 0;

			*fs++ = '0' + ival % 10, ival /= 10;
		} while (ival);

		if (fls & VTFS_LEFT_ALN)
		{
			if IS_UVAL_NEG(ival)
			{
				if (fs == fss) return 0;

				*fs++ = '-';
			}
			else if (fls & IVTS_PSIGN)
			{
				if (fs == fss) return 0;

				*fs++ = '+';
			}

			mttstr_mem_rev(fstr, fs - fstr);

			while (fs < fsw) *fs++ = ' ';

			n = fs - fstr;
		}
		else
		{
			if (fls & VTFS_PREP_ZEROS)
			{
				if IS_UVAL_NEG(iv)
				{
					fsw--;

					while (fs < fsw) *fs++ = '0';

					if (fs == fss) return 0;

					*fs++ = '-';
				}
				else if (fls & IVTS_PSIGN)
				{
					fsw--;

					while (fs < fsw) *fs++ = '0';

					if (fs == fss) return 0;

					*fs++ = '+';
				}
				else while (fs < fsw) *fs++ = '0';
			}
			else
			{
				if IS_UVAL_NEG(ival)
				{
					if (fs == fss) return 0;

					*fs++ = '-';
				}
				else if (fls & IVTS_PSIGN)
				{
					if (fs == fss) return 0;

					*fs++ = '+';
				}

				while (fs < fsw) *fs++ = ' ';
			}

			n = fs - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fs < fss && fls & VTS_NULL_TERM) *fs = 0;

		return n;
	}

	return 0;
}

size_t mttstr_str_to_uval(char *str, char **last, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char sc;
		size_t uval = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (base > 10)
		{
			if (fs & STUV_MCASE)
			{
				char umx = 55 + base, lmx = umx + 32;

				while (1)
				{
					sc = *str;

					if ('0' <= sc && sc <= '9') uval = uval * base + sc - '0';
					else if ('A' <= sc && sc < umx) uval = uval * base + sc - 55;
					else if ('a' <= sc && sc < lmx) uval = uval * base + sc - 87;
					else break;

					str++;
				}
			}
			else
			{
				char min = fs & STUV_LCASE ? 'a' : 'A', max = min + base - 10;

				while (1)
				{
					sc = *str;

					if ('0' <= sc && sc <= '9') uval = uval * base + sc - '0';
					else if (min <= sc && sc < max) uval = uval * base + sc - min + 10;
					else break;

					str++;
				}
			}
		}
		else
		{
			char max = '0' + base;

			while (sc = *str, '0' <= sc && sc < max) str++, uval = uval * base + sc - '0';
		}

		if (last) *last = str;

		return uval;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_strn_to_uval(char *str, size_t n, char **last, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char sc, *sn = str + n;
		size_t uval = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (base > 10)
		{
			if (fs & STUV_MCASE)
			{
				char umx = 55 + base, lmx = umx + 32;

				while (1)
				{
					if (str == sn) break;

					sc = *str;

					if ('0' <= sc && sc <= '9') uval = uval * base + sc - '0';
					else if ('A' <= sc && sc < umx) uval = uval * base + sc - 55;
					else if ('a' <= sc && sc < lmx) uval = uval * base + sc - 87;
					else break;

					str++;
				}
			}
			else
			{
				char min = fs & STUV_LCASE ? 'a' : 'A', max = min + base - 10;

				while (1)
				{
					if (str == sn) break;

					sc = *str;

					if ('0' <= sc && sc <= '9') uval = uval * base + sc - '0';
					else if (min <= sc && sc < max) uval = uval * base + sc - min + 10;
					else break;

					str++;
				}
			}
		}
		else
		{
			char max = '0' + base;

			while (1)
			{
				if (str == sn) break;

				sc = *str;

				if ('0' <= sc && sc < max) uval = uval * base + sc - '0';
				else break;

				str++;
			}
		}

		if (last) *last = str;

		return uval;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_str_to_ival(char *str, char **last, int fs)
{
	if (str)
	{
		char sc;
		size_t s, ival = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (sc = *str, sc == '-') sc = *++str, s = -1;
		else
		{
			if (fs & STIV_PSIGN && sc == '+') sc = *++str;

			s = 1;
		}

		while ('0' <= sc && sc <= '9') ival = ival * 10 + sc - '0', sc = *++str;

		if (last) *last = str;

		return s * ival;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_strn_to_ival(char *str, size_t n, char **last, int fs)
{
	if (str && n)
	{
		char sc, *sn = str + n;
		size_t s, ival = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (sc = *str, sc == '-') sc = *++str, s = -1;
		else
		{
			if (fs & STIV_PSIGN && sc == '+') sc = *++str;

			s = 1;
		}

		while (1)
		{
			if (str == sn) break;
			else if ('0' <= sc && sc <= '9') ival = ival * 10 + sc - '0';
			else break;

			sc = *++str;
		}

		if (last) *last = str;

		return s * ival;
	}

	if (last) *last = NULL;

	return 0;
}
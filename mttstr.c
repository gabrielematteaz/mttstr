#include "mttstr.h"

void *mttstr_mem_rev(void *mem, size_t n)
{
	if (mem)
	{
		char *m = mem, *mn = m + n;

		while (m < mn)
		{
			char mc = *m;

			*m++ = *--mn, *mn = mc;
		}
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
				char r = uval % base;

				uval /= base, *s++ = (r < 10 ? '0' : a) + r;
			} while (uval);
		}
		else do *s++ = '0' + uval % base, uval /= base; while (uval);

		n = s - str, mttstr_mem_rev(str, n);

		if (fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_uval_to_str_s(char *str, size_t c, size_t uval, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char *s = str, *sc = s + c;

		if (base > 10)
		{
			char a = fs & UVTS_LCASE ? 87 : 55;

			do
			{
				if (s == sc) return 0;

				{
					char r = uval % base;

					uval /= base, *s++ = (r < 10 ? '0' : a) + r;
				}
			} while (uval);
		}
		else
		{
			do
			{
				if (s == sc) return 0;

				*s++ = '0' + uval % base, uval /= base;
			} while (uval);
		}

		{
			size_t n = s - str;

			mttstr_mem_rev(str, n);

			if (fs & VTS_NULL_TERM && s < sc) *s = 0;

			return n;
		}
	}

	return 0;
}

size_t mttstr_ival_to_str(char *str, size_t ival, int fs)
{
	if (str)
	{
		size_t i = ival, n;
		char *s = str;

		if IS_VAL_NEG(ival) ival = -ival;

		do *s++ = '0' + ival % 10, ival /= 10; while (ival);

		if IS_VAL_NEG(i) *s++ = '-';
		else if (fs & IVTS_PLUS_SIGN) *s++ = '+';

		n = s - str, mttstr_mem_rev(str, n);

		if (fs & VTS_NULL_TERM) *s = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_str_s(char *str, size_t c, size_t ival, int fs)
{
	if (str)
	{
		size_t i = ival;
		char *s = str, *sc = s + c;

		if IS_VAL_NEG(ival) ival = -ival;

		do
		{
			if (s == sc) return 0;

			*s++ = '0' + ival % 10, ival /= 10;
		} while (ival);

		if IS_VAL_NEG(i)
		{
			if (s == sc) return 0;

			*s++ = '-';
		}
		else if (fs & IVTS_PLUS_SIGN)
		{
			if (s == sc) return 0;

			*s++ = '+';
		}

		{
			size_t n = s - str;

			mttstr_mem_rev(str, n);

			if (fs & VTS_NULL_TERM && s < sc) *s = 0;

			return n;
		}
	}

	return 0;
}

size_t mttstr_uval_to_fstr(char *fstr, size_t uval, int base, size_t width, int fs)
{
	if (fstr && 2 <= base && base <= 36)
	{
		char *f = fstr, *fw = f + width;
		size_t n;

		if (base > 10)
		{
			char a = fs & UVTS_LCASE ? 87 : 55;

			do
			{
				char r = uval % base;

				uval /= base, *f++ = (r < 10 ? '0' : a) + r;
			} while (uval);
		}
		else do *f++ = '0' + uval % base, uval /= base; while (uval);

		if (fs & VTFS_LEFT_ALN)
		{
			mttstr_mem_rev(fstr, f - fstr);

			while (f < fw) *f++ = ' ';

			n = f - fstr;
		}
		else
		{
			char p = fs & VTFS_PREP_ZEROS ? '0' : ' ';

			while (f < fw) *f++ = p;

			n = f - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fs & VTS_NULL_TERM) *f = 0;

		return n;
	}

	return 0;
}

size_t mttstr_uval_to_fstr_s(char *fstr, size_t c, size_t uval, int base, size_t width, int fs)
{
	if (fstr && 2 <= base && base <= 36 && width <= c)
	{
		char *f = fstr, *fc = f + c;

		if (base > 10)
		{
			char a = fs & UVTS_LCASE ? 87 : 55;

			do
			{
				if (f == fc) return 0;

				{
					char r = uval % base;

					uval /= base, *f++ = (r < 10 ? '0' : a) + r;
				}
			} while (uval);
		}
		else
		{
			do
			{
				if (f == fc) return 0;

				*f++ = '0' + uval % base, uval /= base;
			} while (uval);
		}

		{
			char *fw = fstr + width;
			size_t n;

			if (fs & VTFS_LEFT_ALN)
			{
				mttstr_mem_rev(fstr, f - fstr);

				while (f < fw) *f++ = ' ';

				n = f - fstr;
			}
			else
			{
				char p = fs & VTFS_PREP_ZEROS ? '0' : ' ';

				while (f < fw) *f++ = p;

				n = f - fstr, mttstr_mem_rev(fstr, n);
			}

			if (fs & VTS_NULL_TERM && f < fc) *f = 0;

			return n;
		}
	}

	return 0;
}

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, size_t width, int fs)
{
	if (fstr)
	{
		size_t i = ival, n;
		char *f = fstr, *fw = f + width;

		if IS_VAL_NEG(ival) ival = -ival;

		do *f++ = '0' + ival % 10, ival /= 10; while (ival);

		if (fs & VTFS_LEFT_ALN)
		{
			if IS_VAL_NEG(i) *f++ = '-';
			else if (fs & IVTS_PLUS_SIGN) *f++ = '+';

			mttstr_mem_rev(fstr, f - fstr);

			while (f < fw) *f++ = ' ';

			n = f - fstr;
		}
		else
		{
			if (fs & VTFS_PREP_ZEROS)
			{
				fw--;

				while (f < fw) *f++ = '0';

				if IS_VAL_NEG(i) *f++ = '-';
				else if (fs & IVTS_PLUS_SIGN) *f++ = '+';
				else if (f == fw) *f++ = '0';
			}
			else
			{
				if IS_VAL_NEG(i) *f++ = '-';
				else if (fs & IVTS_PLUS_SIGN) *f++ = '+';

				while (f < fw) *f++ = ' ';
			}

			n = f - fstr, mttstr_mem_rev(fstr, n);
		}

		if (fs & VTS_NULL_TERM) *f = 0;

		return n;
	}

	return 0;
}

size_t mttstr_ival_to_fstr_s(char *fstr, size_t c, size_t ival, size_t width, int fs)
{
	if (fstr && width <= c)
	{
		size_t i = ival;
		char *f = fstr, *fc = f + c;

		if IS_VAL_NEG(ival) ival = -ival;

		do
		{
			if (f == fc) return 0;

			*f++ = '0' + ival % 10, ival /= 10;
		} while (ival);

		{
			if (fs & VTFS_LEFT_ALN)
			{
				if IS_VAL_NEG(i)
				{
					if (f == fc) return 0;

					*f++ = '-';
				}
				else if (fs & IVTS_PLUS_SIGN)
				{
					if (f == fc) return 0;

					*f++ = '+';
				}

				mttstr_mem_rev(fstr, f - fstr);

				{
					char *fw = fstr + width;

					while (f < fw) *f++ = ' ';

					if (fs & VTS_NULL_TERM) *f = 0;

					return f - fstr;
				}
			}
			else
			{
				if (fs & VTFS_PREP_ZEROS)
				{
					char *fw = fstr + width - 1;

					while (f < fw) *f++ = '0';

					if IS_VAL_NEG(i)
					{
						if (f == fc) return 0;

						*f++ = '-';
					}
					else if (fs & IVTS_PLUS_SIGN)
					{
						if (f == fc) return 0;

						*f++ = '+';
					}
					else if (f == fw) *f++ = '0';
				}
				else
				{
					if IS_VAL_NEG(i)
					{
						if (f == fc) return 0;

						*f++ = '-';
					}
					else if (fs & IVTS_PLUS_SIGN)
					{
						if (f == fc) return 0;

						*f++ = '+';
					}

					{
						char *fw = fstr + width;

						while (f < fw) *f++ = ' ';
					}
				}

				{
					size_t n = f - fstr;
					
					mttstr_mem_rev(fstr, n);

					if (fs & VTS_NULL_TERM) *f = 0;

					return n;
				}
			}
		}
	}

	return 0;
}

size_t mttstr_str_to_uval(char *str, char **last, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char c;
		size_t u = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (base > 10)
		{
			if (fs & STUV_MCASE)
			{
				char um = 'A' + base - 10, lm = um + 32;

				while (1)
				{
					c = *str;

					if ('0' <= c && c <= '9') u = u * base + c - '0';
					else if ('A' <= c && c < um) u = u * base + c - 55;
					else if ('a' <= c && c < lm) u = u * base + c - 87;
					else break;

					str++;
				}
			}
			else
			{
				char mn = fs & STUV_LCASE ? 'a' : 'A', mx = mn + base - 10;

				while (1)
				{
					c = *str;

					if ('0' <= c && c <= '9') u = u * base + c - '0';
					else if (mn <= c && c < mx) u = u * base + c - mn + 10;
					else break;

					str++;
				}
			}
		}
		else
		{
			char m = '0' + base;

			while (c = *str, '0' <= c && c < m) str++, u = u * base + c - '0';
		}

		if (last) *last = str;

		return u;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_strn_to_uval(char *str, size_t n, char **last, int base, int fs)
{
	if (str && 2 <= base && base <= 36)
	{
		char *sn = str + n;

		if (fs & STV_SKIP_BLNKS)
		{
			while (1)
			{
				if (str == sn)
				{
					if (last) *last = str;

					return 0;
				}

				if (*str == ' ') str++;
				else break;
			}
		}

		{
			size_t u = 0;

			if (base > 10)
			{
				if (fs & STUV_MCASE)
				{
					char um = 'A' + base - 10, lm = um + 32;

					while (1)
					{
						if (str == sn) break;

						{
							char c = *str;

							if ('0' <= c && c <= '9') u = u * base + c - '0';
							else if ('A' <= c && c < um) u = u * base + c - 55;
							else if ('a' <= c && c < lm) u = u * base + c - 87;
							else break;

							str++;
						}
					}
				}
				else
				{
					char mn = fs & STUV_LCASE ? 'a' : 'A', mx = mn + base - 10;

					while (1)
					{
						if (str == sn) break;

						{
							char c = *str;

							if ('0' <= c && c <= '9') u = u * base + c - '0';
							else if (mn <= c && c < mx) u = u * base + c - mn + 10;
							else break;

							str++;
						}
					}
				}
			}
			else
			{
				char m = '0' + base;

				while (1)
				{
					if (str == sn) break;

					{
						char c = *str;
					
						if (c < '0' || m <= c) break;

						str++, u = u * base + c - '0';
					}
				}
			}

			if (last) *last = str;

			return u;
		}
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_str_to_ival(char *str, char **last, int fs)
{
	if (str)
	{
		char c;
		size_t s, i = 0;

		if (fs & STV_SKIP_BLNKS) while (*str == ' ') str++;

		if (c = *str, c == '-') c = *++str, s = -1;
		else
		{
			if (fs & STIV_PLUS_SIGN && c == '+') c = *++str;

			s = 1;
		}

		while ('0' <= c && c <= '9') i = i * 10 + c - '0', c = *++str;

		if (last) *last = str;

		return s * i;
	}

	if (last) *last = NULL;

	return 0;
}

size_t mttstr_strn_to_ival(char *str, size_t n, char **last, int fs)
{
	if (str)
	{
		char *sn = str + n;

		if (fs & STV_SKIP_BLNKS)
		{
			while (1)
			{
				if (str == sn)
				{
					if (last) *last = str;

					return 0;
				}

				if (*str == ' ') str++;
				else break;
			}
		}

		if (str < sn)
		{
			char c;
			size_t s, i = 0;

			if (c = *str, c == '-') c = *++str, s = -1;
			else
			{
				s = 1;

				if (fs & STIV_PLUS_SIGN && c == '+') c = *++str;
			}

			while (1)
			{
				if (str == sn) break;

				{
					if (c < '0' || c > '9') break;

					i = i * 10 + c - '0', c = *++str;
				}
			}

			if (last) *last = str;

			return s * i;
		}
	}

	if (last) *last = NULL;

	return 0;
}
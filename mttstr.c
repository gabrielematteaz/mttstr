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

void *mttstr_wmem_rev(void *wmem, size_t n)
{
	wchar_t *wm, *wmn, wmc;

	if (wmem != NULL)
	{
		wm = wmem, wmn = wm + n;

		while (wm < wmn)
		{
			wmn--;
			wmc = *wm;
			*wm = *wmn;
			wm++;
			*wmn = wmc;
		}
	}

	return wmem;
}

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt)
{
	size_t len, i;
	char *f, a, rem, *fw;

	if (2 <= fmt.base && fmt.base <= 36)
	{
		if (fstr == NULL)
		{
			if (fmt.minus && IS_VAL_NEG(ival))
			{
				ival = -ival;
				len = 1;
			}
			else len = fmt.plus ? 1 : 0;

			do
			{
				ival /= fmt.base;
				len++;
			} while (ival);

			if (len < fmt.width) len = fmt.width;
		}
		else
		{
			if (fmt.minus && IS_VAL_NEG(ival))
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

			if (fmt.flags & FMT_FLAGS_INT_FILL)
			{
				fw = fstr + fmt.width - 1;

				while (f < fw)
				{
					*f = fmt.fill;
					f++;
				}

				if IS_VAL_NEG(i)
				{
					*f = fmt.minus;
					f++;
				}
				else if (fmt.plus)
				{
					*f = fmt.plus;
					f++;
				}
				else if (f == fw)
				{
					*f = fmt.fill;
					f++;
				}

				len = f - fstr;
				mttstr_mem_rev(fstr, len);
			}
			else if (fmt.flags & FMT_FLAGS_RIGHT_FILL)
			{
				if IS_VAL_NEG(i)
				{
					*f = fmt.minus;
					f++;
				}
				else if (fmt.plus)
				{
					*f = fmt.plus;
					f++;
				}

				mttstr_mem_rev(fstr, f - fstr);

				fw = fstr + fmt.width;

				while (f < fw)
				{
					*f = fmt.fill;
					f++;
				}

				len = f - fstr;
			}
			else
			{
				if IS_VAL_NEG(i)
				{
					*f = fmt.minus;
					f++;
				}
				else if (fmt.plus)
				{
					*f = fmt.plus;
					f++;
				}

				fw = fstr + fmt.width;

				while (f < fw)
				{
					*f = fmt.fill;
					f++;
				}

				len = f - fstr;
				mttstr_mem_rev(fstr, len);

			}

			if (fmt.flags & FMT_FLAGS_NULL_TERM) *f = 0;
		}

		return len;
	}

	return 0;
}

char *mttstr_ival_to_fstr_alloc(size_t ival, struct mttstr_fmt_t fmt)
{
	size_t fstrsize = mttstr_ival_to_fstr(NULL, ival, fmt);
	char *fstr;

	if (fmt.flags & FMT_FLAGS_NULL_TERM) fstrsize++;

	fstrsize = fstrsize * sizeof(*fstr);
	fstr = malloc(fstrsize);

	if (fstr != NULL) mttstr_ival_to_fstr(fstr, ival, fmt);

	return fstr;
}

size_t mttstr_ival_to_wfstr(wchar_t *wfstr, size_t ival, struct mttstr_wfmt_t wfmt)
{
	size_t len, i;
	wchar_t *wf, wa, wrem, *wfw;

	if (2 <= wfmt.base && wfmt.base <= 36)
	{
		if (wfstr == NULL)
		{
			if (wfmt.wminus && IS_VAL_NEG(ival))
			{
				ival = -ival;
				len = 1;
			}
			else len = wfmt.wplus ? 1 : 0;

			do
			{
				ival /= wfmt.base;
				len++;
			} while (ival);

			if (len < wfmt.width) len = wfmt.width;
		}
		else
		{
			if (wfmt.wminus && IS_VAL_NEG(ival))
			{
				i = ival;
				ival = -ival;
			}
			else i = 0;

			wf = wfstr;

			if (wfmt.base > 10)
			{
				wa = wfmt.flags & FMT_FLAGS_LCASE ? 87 : 55;

				do
				{
					wrem = ival % wfmt.base;
					ival /= wfmt.base;
					*wf = (wrem < 10 ? L'0' : wa) + wrem;
					wf++;
				} while (ival);
			}
			else
			{
				do
				{
					*wf = L'0' + ival % wfmt.base;
					ival /= wfmt.base;
					wf++;
				} while (ival);
			}

			if (wfmt.flags & FMT_FLAGS_INT_FILL)
			{
				wfw = wfstr + wfmt.width - 1;

				while (wf < wfw)
				{
					*wf = wfmt.wfill;
					wf++;
				}

				if IS_VAL_NEG(i)
				{
					*wf = wfmt.wminus;
					wf++;
				}
				else if (wfmt.wplus)
				{
					*wf = wfmt.wplus;
					wf++;
				}
				else if (wf == wfw)
				{
					*wf = wfmt.wfill;
					wf++;
				}

				len = wf - wfstr;
				mttstr_wmem_rev(wfstr, len);
			}
			else if (wfmt.flags & FMT_FLAGS_RIGHT_FILL)
			{
				if IS_VAL_NEG(i)
				{
					*wf = wfmt.wminus;
					wf++;
				}
				else if (wfmt.wplus)
				{
					*wf = wfmt.wplus;
					wf++;
				}

				mttstr_wmem_rev(wfstr, wf - wfstr);

				wfw = wfstr + wfmt.width;

				while (wf < wfw)
				{
					*wf = wfmt.wfill;
					wf++;
				}

				len = wf - wfstr;
			}
			else
			{
				if IS_VAL_NEG(i)
				{
					*wf = wfmt.wminus;
					wf++;
				}
				else if (wfmt.wplus)
				{
					*wf = wfmt.wplus;
					wf++;
				}

				wfw = wfstr + wfmt.width;

				while (wf < wfw)
				{
					*wf = wfmt.wfill;
					wf++;
				}

				len = wf - wfstr;
				mttstr_wmem_rev(wfstr, len);

			}

			if (wfmt.flags & FMT_FLAGS_NULL_TERM) *wf = 0;
		}

		return len;
	}

	return 0;
}

wchar_t *mttstr_ival_to_wfstr_alloc(size_t ival, struct mttstr_wfmt_t wfmt)
{
	size_t wfstrsize = mttstr_ival_to_wfstr(NULL, ival, wfmt);
	wchar_t *wfstr;

	if (wfmt.flags & FMT_FLAGS_NULL_TERM) wfstrsize++;

	wfstrsize = wfstrsize * sizeof(*wfstr);
	wfstr = malloc(wfstrsize);

	if (wfstr != NULL) mttstr_ival_to_wfstr(wfstr, ival, wfmt);

	return wfstr;
}

size_t mttstr_fstr_to_ival(const char *fstr, const char **last, struct mttstr_fmt_t fmt)
{
	char fc, umax, lmax, min, max;
	size_t s, ival;

	if (fstr != NULL && 2 <= fmt.base && fmt.base <= 36)
	{
		fc = *fstr;

		if (fmt.flags & FMT_FLAGS_INT_FILL)
		{
			if (fc == fmt.minus)
			{
				fstr++;
				fc = *fstr;
				s = -1;
			}
			else
			{
				if (fc == fmt.plus)
				{
					fstr++;
					fc = *fstr;
				}

				s = 1;
			}

			while (fc == fmt.fill)
			{
				fstr++;
				fc = *fstr;
			}
		}
		else
		{
			if ((fmt.flags & FMT_FLAGS_RIGHT_FILL) == 0)
			{
				while (fc == fmt.fill)
				{
					fstr++;
					fc = *fstr;
				}
			}

			if (fc == fmt.minus)
			{
				fstr++;
				fc = *fstr;
				s = -1;
			}
			else
			{
				if (fc == fmt.plus)
				{
					fstr++;
					fc = *fstr;
				}

				s = 1;
			}
		}

		ival = 0;

		if (fmt.base > 10)
		{
			if (fmt.flags & FMT_FLAGS_MCASE)
			{
				umax = 'A' + fmt.base - 10;
				lmax = umax + 32;

				while (1)
				{
					if ('0' <= fc && fc <= '9') ival = ival * fmt.base + fc - '0';
					else if ('A' <= fc && fc < umax) ival = ival * fmt.base + fc - 55;
					else if ('a' <= fc && fc < lmax) ival = ival * fmt.base + fc - 87;
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
				fstr++;
				ival = ival * fmt.base + fc - '0';
				fc = *fstr;
			}
		}

		if (last != NULL) *last = fstr;

		return s * ival;
	}

	if (last != NULL) *last = NULL;

	return 0;
}

size_t mttstr_wfstr_to_ival(const wchar_t *wfstr, const wchar_t **wlast, struct mttstr_wfmt_t wfmt)
{
	wchar_t wfc, wumax, wlmax, wmin, wmax;
	size_t s, ival;

	if (wfstr != NULL && 2 <= wfmt.base && wfmt.base <= 36)
	{
		wfc = *wfstr;

		if (wfmt.flags & FMT_FLAGS_INT_FILL)
		{
			if (wfc == wfmt.wminus)
			{
				wfstr++;
				wfc = *wfstr;
				s = -1;
			}
			else
			{
				if (wfc == wfmt.wplus)
				{
					wfstr++;
					wfc = *wfstr;
				}

				s = 1;
			}

			while (wfc == wfmt.wfill)
			{
				wfstr++;
				wfc = *wfstr;
			}
		}
		else
		{
			if ((wfmt.flags & FMT_FLAGS_RIGHT_FILL) == 0)
			{
				while (wfc == wfmt.wfill)
				{
					wfstr++;
					wfc = *wfstr;
				}
			}

			if (wfc == wfmt.wminus)
			{
				wfstr++;
				wfc = *wfstr;
				s = -1;
			}
			else
			{
				if (wfc == wfmt.wplus)
				{
					wfstr++;
					wfc = *wfstr;
				}

				s = 1;
			}
		}

		ival = 0;

		if (wfmt.base > 10)
		{
			if (wfmt.flags & FMT_FLAGS_MCASE)
			{
				wumax = L'A' + wfmt.base - 10;
				wlmax = wumax + 32;

				while (1)
				{
					if (L'0' <= wfc && wfc <= L'9') ival = ival * wfmt.base + wfc - L'0';
					else if (L'A' <= wfc && wfc < wumax) ival = ival * wfmt.base + wfc - 55;
					else if (L'a' <= wfc && wfc < wlmax) ival = ival * wfmt.base + wfc - 87;
					else break;

					wfstr++;
					wfc = *wfstr;
				}
			}
			else
			{
				wmin = wfmt.flags & FMT_FLAGS_LCASE ? L'a' : L'A';
				wmax = wmin + wfmt.base - 10;

				while (1)
				{
					if (L'0' <= wfc && wfc <= L'9') ival = ival * wfmt.base + wfc - L'0';
					else if (wmin <= wfc && wfc < wmax) ival = ival * wfmt.base + wfc - wmin + 10;
					else break;

					wfstr++;
					wfc = *wfstr;
				}
			}
		}
		else
		{
			wmax = L'0' + wfmt.base;

			while (L'0' <= wfc && wfc < wmax)
			{
				wfstr++;
				ival = ival * wfmt.base + wfc - L'0';
				wfc = *wfstr;
			}
		}

		if (wlast != NULL) *wlast = wfstr;

		return s * ival;
	}

	if (wlast != NULL) *wlast = NULL;

	return 0;	
}
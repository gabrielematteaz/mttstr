#include "mttstr.h"

void *mttstr_mem_rev(void *mem, size_t n)
{
	if (mem == NULL) return NULL;

	char *m = mem, *mn = m + n;

	while (m < mn)
	{
		mn--;

		char mc = *m;

		*m = *mn;
		m++;
		*mn = mc;
	}

	return mem;
}

void *mttstr_wmem_rev(void *wmem, size_t n)
{
	if (wmem == NULL) return NULL;

	wchar_t *wm = wmem, *wmn = wm + n;

	while (wm < wmn)
	{
		wmn--;

		wchar_t wmc = *wm;

		*wm = *wmn;
		wm++;
		*wmn = wmc;
	}

	return wmem;
}

size_t mttstr_ival_to_fstr(char *fstr, size_t ival, struct mttstr_fmt_t fmt)
{
	if (fmt.base < 2 || fmt.base > 36) return 0;

	size_t len;

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
		size_t i;

		if (fmt.minus && IS_VAL_NEG(ival))
		{
			i = ival;
			ival = -ival;
		}
		else i = 0;

		char *f = fstr;

		if (fmt.base > 10)
		{
			char a = fmt.fs & FMT_FS_LCASE ? 87 : 55;

			do
			{
				char rem = ival % fmt.base;

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

		char *fw;

		if (fmt.fs & FMT_FS_INT_FILL)
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
		else if (fmt.fs & FMT_FS_RIGHT_FILL)
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

		if (fmt.fs & FMT_FS_NULL_TERM) *f = 0;
	}

	return len;
}

char *mttstr_ival_to_alloc_fstr(size_t ival, struct mttstr_fmt_t fmt)
{
	size_t fstrsize = mttstr_ival_to_fstr(NULL, ival, fmt);

	if (fmt.fs & FMT_FS_NULL_TERM) fstrsize++;

	char *fstr = malloc(fstrsize * sizeof(char));

	if (fstr == NULL) return NULL;

	mttstr_ival_to_fstr(fstr, ival, fmt);

	return fstr;
}

size_t mttstr_ival_to_wfstr(wchar_t *wfstr, size_t ival, struct mttstr_wfmt_t wfmt)
{
	if (wfmt.base < 2 || wfmt.base > 36) return 0;

	size_t len;

	if (wfstr == NULL)
	{
		if (wfmt.minus && IS_VAL_NEG(ival))
		{
			ival = -ival;
			len = 1;
		}
		else len = wfmt.plus ? 1 : 0;

		do
		{
			ival /= wfmt.base;
			len++;
		} while (ival);

		if (len < wfmt.width) len = wfmt.width;
	}
	else
	{
		size_t i;

		if (wfmt.minus && IS_VAL_NEG(ival))
		{
			i = ival;
			ival = -ival;
		}
		else i = 0;

		wchar_t *wf = wfstr;

		if (wfmt.base > 10)
		{
			wchar_t wa = wfmt.fs & FMT_FS_LCASE ? 87 : 55;

			do
			{
				wchar_t wrem = ival % wfmt.base;

				ival /= wfmt.base;
				*wf = (wrem < 10 ? '0' : wa) + wrem;
				wf++;
			} while (ival);
		}
		else
		{
			do
			{
				*wf = '0' + ival % wfmt.base;
				ival /= wfmt.base;
				wf++;
			} while (ival);
		}

		wchar_t *wfw;

		if (wfmt.fs & FMT_FS_INT_FILL)
		{
			wfw = wfstr + wfmt.width - 1;

			while (wf < wfw)
			{
				*wf = wfmt.fill;
				wf++;
			}

			if IS_VAL_NEG(i)
			{
				*wf = wfmt.minus;
				wf++;
			}
			else if (wfmt.plus)
			{
				*wf = wfmt.plus;
				wf++;
			}
			else if (wf == wfw)
			{
				*wf = wfmt.fill;
				wf++;
			}

			len = wf - wfstr;
			mttstr_wmem_rev(wfstr, len);
		}
		else if (wfmt.fs & FMT_FS_RIGHT_FILL)
		{
			if IS_VAL_NEG(i)
			{
				*wf = wfmt.minus;
				wf++;
			}
			else if (wfmt.plus)
			{
				*wf = wfmt.plus;
				wf++;
			}

			mttstr_wmem_rev(wfstr, wf - wfstr);
			wfw = wfstr + wfmt.width;

			while (wf < wfw)
			{
				*wf = wfmt.fill;
				wf++;
			}

			len = wf - wfstr;
		}
		else
		{
			if IS_VAL_NEG(i)
			{
				*wf = wfmt.minus;
				wf++;
			}
			else if (wfmt.plus)
			{
				*wf = wfmt.plus;
				wf++;
			}

			wfw = wfstr + wfmt.width;

			while (wf < wfw)
			{
				*wf = wfmt.fill;
				wf++;
			}

			len = wf - wfstr;
			mttstr_wmem_rev(wfstr, len);
		}

		if (wfmt.fs & FMT_FS_NULL_TERM) *wf = 0;
	}

	return len;
}

wchar_t *mttstr_ival_to_alloc_wfstr(size_t ival, struct mttstr_wfmt_t wfmt)
{
	size_t wfstrsize = mttstr_ival_to_wfstr(NULL, ival, wfmt);

	if (wfmt.fs & FMT_FS_NULL_TERM) wfstrsize++;

	wchar_t *wfstr = malloc(wfstrsize * sizeof(wchar_t));

	if (wfstr == NULL) return NULL;

	mttstr_ival_to_wfstr(wfstr, ival, wfmt);

	return wfstr;
}

size_t mttstr_fstr_to_ival(const char *fstr, const char **last, struct mttstr_fmt_t fmt)
{
	if (fstr == NULL || fmt.base < 2 || fmt.base > 36)
	{
		if (last != NULL) *last = NULL;

		return 0;
	}

	char fc = *fstr;
	size_t s;

	if (fmt.fs & FMT_FS_INT_FILL)
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
		if ((fmt.fs & FMT_FS_RIGHT_FILL) == 0x00)
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

	size_t ival = 0;

	if (fmt.base > 10)
	{
		if (fmt.fs & FMT_FS_MCASE)
		{
			char umax = 'A' + fmt.base - 10, lmax = umax + 32;

			while (1)
			{
				if (fc < '0' || fc > '9')
				{
					if (fc < 'A' || umax <= fc)
					{
						if (fc < 'a' || lmax <= fc) break;

						ival = ival * fmt.base + fc - 87;
					}
					else ival = ival * fmt.base + fc - 55;
				}
				else ival = ival * fmt.base + fc - '0';

				fstr++;
				fc = *fstr;
			}
		}
		else
		{
			char min = fmt.fs & FMT_FS_LCASE ? 'a' : 'A', max = min + fmt.base - 10;

			while (1)
			{
				if (fc < '0' || fc > '9')
				{
					if (fc < min || max <= fc) break;

					ival = ival * fmt.base + fc - min + 10;
				}
				else ival = ival * fmt.base + fc - '0';

				fstr++;
				fc = *fstr;
			}
		}
	}
	else
	{
		char max = '0' + fmt.base;

		while (1)
		{
			if (fc < '0' || max <= fc) break;

			fstr++;
			ival = ival * fmt.base + fc - '0';
			fc = *fstr;
		}
	}

	if (last != NULL) *last = fstr;

	return s * ival;
}

size_t mttstr_wfstr_to_ival(const wchar_t *wfstr, const wchar_t **wlast, struct mttstr_wfmt_t wfmt)
{
	if (wfstr == NULL || wfmt.base < 2 || wfmt.base > 36)
	{
		if (wlast != NULL) *wlast = NULL;

		return 0;
	}

	wchar_t wfc = *wfstr;
	size_t s;

	if (wfmt.fs & FMT_FS_INT_FILL)
	{
		if (wfc == wfmt.minus)
		{
			wfstr++;
			wfc = *wfstr;
			s = -1;
		}
		else
		{
			if (wfc == wfmt.plus)
			{
				wfstr++;
				wfc = *wfstr;
			}

			s = 1;
		}

		while (wfc == wfmt.fill)
		{
			wfstr++;
			wfc = *wfstr;
		}
	}
	else
	{
		if ((wfmt.fs & FMT_FS_RIGHT_FILL) == 0x00)
		{
			while (wfc == wfmt.fill)
			{
				wfstr++;
				wfc = *wfstr;
			}
		}

		if (wfc == wfmt.minus)
		{
			wfstr++;
			wfc = *wfstr;
			s = -1;
		}
		else
		{
			if (wfc == wfmt.plus)
			{
				wfstr++;
				wfc = *wfstr;
			}

			s = 1;
		}
	}

	size_t ival = 0;

	if (wfmt.base > 10)
	{
		if (wfmt.fs & FMT_FS_MCASE)
		{
			wchar_t wumax = L'A' + wfmt.base - 10, wlmax = wumax + 32;

			while (1)
			{
				if (wfc < L'0' || wfc > L'9')
				{
					if (wfc < L'A' || wumax <= wfc)
					{
						if (wfc < L'a' || wlmax <= wfc) break;

						ival = ival * wfmt.base + wfc - 87;
					}
					else ival = ival * wfmt.base + wfc - 55;
				}
				else ival = ival * wfmt.base + wfc - L'0';

				wfstr++;
				wfc = *wfstr;
			}
		}
		else
		{
			wchar_t wmin = wfmt.fs & FMT_FS_LCASE ? L'a' : L'A', wmax = wmin + wfmt.base - 10;

			while (1)
			{
				if (wfc < L'0' || wfc > L'9')
				{
					if (wfc < wmin || wmax <= wfc) break;

					ival = ival * wfmt.base + wfc - wmin + 10;
				}
				else ival = ival * wfmt.base + wfc - L'0';

				wfstr++;
				wfc = *wfstr;
			}
		}
	}
	else
	{
		wchar_t wmax = L'0' + wfmt.base;

		while (1)
		{
			if (wfc < L'0' || wmax <= wfc) break;

			wfstr++;
			ival = ival * wfmt.base + wfc - L'0';
			wfc = *wfstr;
		}
	}

	if (wlast != NULL) *wlast = wfstr;

	return s * ival;
}
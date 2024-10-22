#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
static void mul_mat(const int n, const int m, const int k, const double* const mat1, const double* const mat2, double* const res)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < k; j++)
		{
			res[i * k + j] = 0;
			for (int l = 0; l < n; l++)
			{
				res[i * k + j] += mat1[i * m + l] * mat2[l * n + j];
			}
		}
	}
}
static void pow_mat(const int n, const int k, const double* const mat, double* res1, double* res2)
{
	mul_mat(n, n, n, mat, mat, res1);
	for (int i = 1; i < k - 1; i++)
	{
		if (i % 2)
		{
			mul_mat(n, n, n, res1, mat, res2);
		}
		else
		{
			mul_mat(n, n, n, res2, mat, res1);
		}
	}
	if (k % 2)
	{
		double* tmp;
		tmp = res1;
		res1 = res2;
		res2 = tmp;
	}
}
static void out_mat(const int n, const int m, const double* const mat)
{
	int maxlen = INT32_MIN;
	for (int i = 0; i < n * m; i++)
	{
		int len = std::snprintf(nullptr, 0, "%.2f", mat[i]);
		if (len > maxlen)
		{
			maxlen = len;
		}
	}
	const int ALIGN_W = maxlen;
	std::wcout << '|';
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (j < m - 1)
			{
				std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << mat[i * m + j];
			}
			else
			{
				std::wcout << mat[i * m + j] << "|\n";
				if (i < n - 1)
				{
					std::wcout << "|";
				}
			}
		}
	}
}
static void out_mat_autoui(const int n, const int m, const double* const mat)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m - 1; j++)
		{
			std::wcout << mat[i * m + j] << ' ';
		}
		std::wcout << mat[i * m + m - 1] << '\n';
	}
}
static void in_mat(const int n, const int m, double* const mat)
{
	for (int i = 0; i < n * m; i++)
	{
		std::wcin >> mat[i];
	}
}
int wmain(int argc, wchar_t* argv[])
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U8TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	bool autoui = true;
	if (argc <= 1 || std::wcsncmp(argv[1], L"false", sizeof(L"false") - 1) != 0)
	{
		autoui = false;
	}
	int n, m;
	std::wcin >> n >> m;
	double* a1 = new double[n * m];
	in_mat(n, m, a1);
	int cmd = 1, k = 0;
	while (cmd != 0)
	{
		std::wcin >> cmd;
		switch (cmd)
		{
		case 0:
			break;
		case 1:
		{
			if (autoui)
			{
				out_mat_autoui(n, m, a1);
			}
			else
			{
				out_mat(n, m, a1);
			}
			break;
		}
		case 2:
		{
			std::wcin >> k;
			double* a2 = new double[m * k];
			double* res = new double[n * k] {};
			in_mat(m, k, a2);
			mul_mat(n, m, k, a1, a2, res);
			delete[] a1;
			a1 = res;
			delete[] a2;
			m = k;
			break;
		}
		case 3:
		{
			if (n == m)
			{
				std::wcin >> k;
				double* res1 = new double[n * n] {};
				double* res2 = new double[n * n] {};
				pow_mat(n, k, a1, res1, res2);
				delete[] a1;
				a1 = res2;
				delete[] res1;
			}
			else
			{
				std::wcout << "NO\n";
			}
			break;
		}
		default:
		{
			std::wcerr << "Invalid Input";
			return 1;
		}
		}
	}
	return 0;
}
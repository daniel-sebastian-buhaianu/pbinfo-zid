#include <stdio.h>

#define MIN_N 2
#define MAX_N 250
#define MIN_M 2
#define MAX_M 250
#define MIN_CMAX 1
#define MAX_CMAX 9

int main()
{
	unsigned short n, m, i, ii, j, jj, L, nr, cmax, c, LMax, imax, jmax, frec;
	char ok;

	FILE *fin = fopen("zid.in", "r");

	if (!fin) {
		printf("Eroare fisier zid.in\n");
		return 1;
	}

	fscanf(fin, "%hu %hu %hu", &n, &m, &cmax);

	if (n < MIN_N || n > MAX_N) {
		printf("Eroare valoare n\n");
		return 2;
	}

	if (m < MIN_M || m > MAX_M) {
		printf("Eroare valoare m\n");
		return 3;
	}

	if (cmax < MIN_CMAX || cmax > MAX_CMAX) {
		printf("Eroare valoare cmax\n");
		return 4;
	}

	unsigned short f[n+1][m+1][n+1][cmax+1], a[n+1][m+1];

	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			for (L = 1; L <= n; L++)
				for (c = 1; c <= cmax; c++)
					f[i][j][L][c] = 0;

	for (L = i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) {
			fscanf(fin, "%hu", &a[i][j]);

			f[i][j][L][a[i][j]] = 1;
		}

	for (imax = jmax = LMax = i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			for (L = 2; L <= n-i+1; L++) {
				for (c = 1; c <= cmax; c++)
					f[i][j][L][c] = f[i][j][L-1][c];

				for (ii = i; ii <= i+L-1 && ii <= n; ii++)
					c = a[ii][j+L-1], f[i][j][L][c]++;

				for (jj = j; jj < j+L-1 && jj <= m; jj++)
					c = a[i+L-1][jj], f[i][j][L][c]++;

				for (frec = nr = 0, ok = c = 1; c <= cmax && ok; c++)
					if (f[i][j][L][c] > 0)
						if (frec == 0)
							frec = f[i][j][L][c];
						else
							if (f[i][j][L][c] != frec)
								ok = 0;
				
				if (ok == 1)
					if (L > LMax)
						LMax = L, imax = i, jmax = j;
			}

	FILE *fout = fopen("zid.out", "w");

	fprintf(fout, "%hu %hu %hu", LMax*LMax, imax, jmax);

	fclose(fin);
	fclose(fout);

	return 0;
}
// scor 12/100

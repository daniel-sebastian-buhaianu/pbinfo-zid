#include <stdio.h>
#include <stdlib.h>

#define MIN_N 2
#define MAX_N 250
#define MIN_M 2
#define MAX_M 250
#define MIN_CMAX 1
#define MAX_CMAX 9

int main()
{
	unsigned short n, m, cmax, ***fr, **a, i, j, cif, c, L, LMax, imax, jmax, frec, fru, ii, jj;
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

	fr = (unsigned short***)calloc(n+1, sizeof(unsigned short**));

	for (i = 0; i <= n; i++) {
		fr[i] = (unsigned short**)calloc(m+1, sizeof(unsigned short*));

		for (j = 0; j <= m; j++) {
			fr[i][j] = (unsigned short*)calloc(cmax+1, sizeof(unsigned short));
		}
	}

	a = (unsigned short**)calloc(n+1, sizeof(unsigned short*));

	for (i = 1; i <= n; i++) {
		a[i] = (unsigned short*)calloc(m+1, sizeof(unsigned short));

		for (j = 1; j <= m; j++) {
			fscanf(fin, "%hu", &cif);
			
			a[i][j] = cif;

			for (c = MIN_CMAX; c <= cmax; c++)
				fr[i][j][c] = fr[i][j-1][c] + fr[i-1][j][c] - fr[i-1][j-1][c];

			fr[i][j][cif] += 1;
		}
	}

	for (LMax = jmax = imax = i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			for (L = n-i+1; L >= 1 && L > LMax && j+L-1 <= m; L--) {
				ii = i+L-1, jj = j+L-1;

				for (ok = 1, fru = 0, c = MIN_CMAX; c <= cmax && ok; c++) {
					frec = fr[ii][jj][c] - fr[ii][jj-L][c] - fr[i-1][jj][c] + fr[i-1][j-1][c];

					if (frec && !fru)
						fru = frec;

					if (frec && fru && frec != fru)
						ok = 0;	
				}

				if (ok && L > LMax)
					LMax = L, imax = i, jmax = j;
			}
		}
	}
	
	FILE *fout = fopen("zid.out", "w");

	fprintf(fout, "%hu %hu %hu", LMax*LMax, imax, jmax);

	fclose(fin);
	fclose(fout);

	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++)
			free(fr[i][j]);
		
		free(fr[i]);
		free(a[i]);
	}

	free(fr);
	free(a);

	return 0;
}
// scor 49

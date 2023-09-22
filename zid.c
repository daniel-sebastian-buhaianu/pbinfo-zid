#include <stdio.h>
#include <stdlib.h>

#define MIN_N 2
#define MAX_N 250
#define MIN_M 2
#define MAX_M 250
#define MIN_CMAX 1
#define MAX_CMAX 9

int min(int a, int b);

int main()
{
	FILE *fin = fopen("zid.in", "r");

	if (!fin) {
		printf("Eroare fisier zid.in\n");
		return 1;
	}

	unsigned short n, m, cmax;

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

	unsigned short ***fr, i, **a, c, j;

	fr = (unsigned short***)calloc(n+1, sizeof(unsigned short**));

	if (!fr) {
		printf("Eroare alocare memorie *fr\n");
		return 5;
	}

	for (i = 0; i <= n; i++) {
		fr[i] = (unsigned short**)calloc(m+1, sizeof(unsigned short*));

		if (!fr[i]) {
			printf("Eroare alocare memorie *fr\n");
			return 5;
		}

		for (j = 0; j <= m; j++) {
			fr[i][j] = (unsigned short*)calloc(cmax+1, sizeof(unsigned short)); 
			
			if (!fr[i][j]) {
				printf("Eroare alocare memorie *fr\n");
				return 5;
			}
		}
	}

	a = (unsigned short**)calloc(n+1, sizeof(unsigned short*));

	if (!a) {
		printf("Eroare alocare memorie *a\n");
		return 6;
	}

	for (i = 1; i <= n; i++) {
		a[i] = (unsigned short*)calloc(m+1, sizeof(unsigned short));

		if (!a[i]) {
			printf("Eroare alocare memorie *a\n");
			return 6;
		}

		for (j = 1; j <= m; j++) {
			fscanf(fin, "%hu", &a[i][j]);

			for (c = MIN_CMAX; c <= cmax; c++)
				fr[i][j][c] = fr[i][j-1][c] + fr[i-1][j][c] - fr[i-1][j-1][c];

			fr[i][j][a[i][j]] += 1;
		}
	}

	unsigned short LMax, jmax, imax, L, ii, jj, *frec, cate;

	frec = (unsigned short*)calloc(cmax+1, sizeof(unsigned short));

	if (!frec) {
		printf("Eroare alocare memorie *frec\n");
		return 7;
	}

	for (LMax = jmax = imax = i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			for (L = min(n-i+1, m-j+1); L > LMax; L--) {
				ii = i+L-1, jj = j+L-1;

				for (c = MIN_CMAX; c <= cmax; c++)
					frec[c] = fr[ii][jj][c] - fr[ii][j-1][c] - fr[i-1][jj][c] + fr[i-1][j-1][c];

				for (c = MIN_CMAX; c < cmax && !frec[c]; c++);

				cate = frec[c];

				for (; c <= cmax; c++)
					if (frec[c] && frec[c] != cate)
						break;

				if (c == cmax+1)
					if (L > LMax)
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
	free(frec);

	return 0;
}

int min(int a, int b)
{
	return a < b ? a : b;
}
// scor 85

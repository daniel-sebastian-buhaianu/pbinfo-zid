#include <stdio.h>
#include <stdlib.h>

#define NMAX 300
#define CMAX 12

int min(int a, int b);

int n, m, c, Lmax, imax, jmax;
int Z[NMAX][NMAX], F[NMAX][NMAX][CMAX];
int uz[CMAX];

int main()
{
	int i, j, k, ii, jj, L, cate;

	FILE *fin = fopen("zid.in", "r");

	if (!fin) {
		printf("Eroare fisier zid.in\n");
		return 1;
	}

	fscanf(fin, "%d %d %d", &n, &m, &c);

	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			fscanf(fin, "%d", &Z[i][j]);

	// determinarea tabloului de frecvente
	
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			for (k = 0; k <= c; k++)
				F[i][j][k] = F[i-1][j][k] + F[i][j-1][k] - F[i-1][j-1][k] + (Z[i][j] == k);

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			for (L = min(n-i+1, m-j+1); L > Lmax; L--) {
				ii = i+L-1, jj = j+L-1;

				for (k = 0; k <= c; k++)
					uz[k] = F[ii][jj][k] - F[ii][j-1][k] - F[i-1][jj][k] + F[i-1][j-1][k];

				
				for (k = 0; !uz[k]; k++);

				cate = uz[k];

				for (; k <= c; k++)
					if (uz[k] && uz[k] != cate)
						break;

				if (k == c+1)
					if (L > Lmax)
						Lmax = L, imax = i, jmax = j;
			}
		}
	}
	
	FILE *fout = fopen("zid.out", "w");

	fprintf(fout, "%d %d %d", Lmax*Lmax, imax, jmax);

	fclose(fin);
	fclose(fout);

	return 0;
}

int min(int a, int b)
{
	return a < b ? a : b;
}
// scor 100 - sol oficiala

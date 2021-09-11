#include <stdio.h>
#include <stdlib.h>

void dim_init(int n, int dim[1000][10][10], int page){
	int		i,j;

	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			dim[page][i][j] = 0;
		}
	}
}

int	mk_dim2(int row, int col, int n, int dim[1000][10][10], int *page){
	int		dat;
	int		i;
	int		err;
	int		next_row, next_col;

	/*----- scan other row & column -----*/
	for(dat = 1; dat <= n; ++dat){
		for(i = 0; i < n; ++i){
			if((i != col) && (dim[*page][row][i] == dat)) break;
			if((i != row) && (dim[*page][i][col] == dat)) break;
		}
		if(i < n) continue; /* can not put degit */

		/*----- recursive call for next colmun -----*/
		dim[*page][row][col] = dat;
		next_row = row;
		next_col = col + 1;
		if(next_col >= n) {next_row = row + 1; next_col = 0;}
		if(next_row >= n) {
			/*----- success to make page -----*/
			++*page;
//			*(dim + *page) = (int **)malloc(sizeof(int) * n * n);
			dim_init(n, dim, *page);
			return(0);
			}
		err = mk_dim2(next_row, next_col, n, dim, page);
	}
	return(1);
}

int mk_dim3(int n, int dim[1000][10][10]){
	int		page;
	
	page = 0;
//	dim = (int ***)malloc(sizeof(int) * n * n);
	dim_init(n, dim, page);
	mk_dim2(0, 0, n, dim, &page);
	return(page);
}

int main(int argc, char **argv){
	int		n;
	int		p;
	int		i, j, k;
	int		dim3[1000][10][10];

	n = atoi(*(argv + 1));
	p = 0;
	p = mk_dim3(n, dim3);

	for(k = 0; k < p; ++k){
		for(i = 0; i < n; ++i){
			for(j = 0; j < n; ++j){
				printf(" %2d", dim3[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}


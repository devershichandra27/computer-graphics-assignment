
#include <stdio.h>


void matrixMultiplication(int a[3], int b[3][3], int prod[3])
{
	prod[0] = a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0];
	prod[1] = a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1];
	prod[2] = a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2];
}

int main(int argc, char const *argv[])
{
	int a[3] = {1,2,1};
	int b[3][3] = {{1,0,0}, {0,1,0}, {2	,4,1}};
	int prod[3] = {0,0,0};
	matrixMultiplication(a, b, prod);
	for (int i = 0; i < 3; ++i)
	{
		printf("%d\n", -prod[i] );
	}
	return 0;
}
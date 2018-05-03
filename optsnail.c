#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main()
{

	int size;
	int sum = 0;
	int x, y, i, j;
	int sw = 1;

  int **snail;
  
	x = y = 0;

	printf("input of snail size: ");
	scanf("%d", &size);

	snail = (int **)malloc(size*sizeof(int));


	for(i = 0; i<size; i++)
	{
		snail[i] = (int *)malloc(size*sizeof(int));
		
    for(j=0; j < size; j++){
     	snail[i][j] = 0;
		}

	}


	while(sum != size*size)

	{
		for(i=0; i<size; i++)
		{
			snail[y][x] = sum;
     	x += sw;
    	sum += 1;
		}

		x -= sw;
		y += sw;
		size--;

	
		for(i = 0; i<size; i++)
		{
			snail[y][x] = sum;
			y += sw;
			sum += 1;
		}
		y -= sw;
		sw *= -1;
		x += sw;
	}

	//print

	for(x=0; x<5; x++)
	{
		for(y=0; y<5; y++)
		{
			printf("%3d ", snail[x][y]);
		}
		printf("\n");
	}

}


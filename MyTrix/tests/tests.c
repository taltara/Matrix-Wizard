#include <stdio.h>
#include <stdlib.h>

float *smallCopyKat(float *matrix, int size, int current);
float *copyKat(float *matrix, int size);
float deter(float *matrix, int size);



float *copyKat(float *matrix, int size)
{
	float *meTemp;
	meTemp = (float *)calloc(size*size, sizeof(float));

	for (int i = 0; i < size*size; i++) meTemp[i] = matrix[i];

	return meTemp;
}

float *smallCopyKat(float *matrix, int size, int current)
{
	float *sMatrix = (float *)calloc((size - 1)*(size - 1), sizeof(float));

	int index = 0;

	for (int j = 1; j < size; j++)
	{
	
		for (int i = 0; i < size; i++)
		{

			if (((j * size) + i) != (j * size) + current)
			{
				sMatrix[index] = matrix[(j * size) + i];

				index += 1;
			}
			
		}

	}

	return sMatrix;
}


float deter(float *matrix, int size)
{
	// calculating determinant for base case 2x2
	if (size == 2)
	{
		float deterBase = 0;
		deterBase = (matrix[0] * matrix[3]) - (matrix[1] * matrix[2]);

		return deterBase;
	}


	// operations for NxN matrices (N>2)
	float deterTemp = 0;
	//                            get it?
	for (int c = 0; c < size; c++)
	{

		float *nextMat = smallCopyKat(matrix, size, c);
		if (c % 2 != 0) 
		{
			deterTemp += (((-1) * matrix[c]) * (deter(nextMat, size - 1)));
		}
		else
		{
			deterTemp += (matrix[c] * deter(nextMat, size - 1));
		}
		
		printf("#%d Det: %.2f", c + 1, deterTemp);
		printf("\n");
	}

	return deterTemp;

}

// 'getNum' function for translating char input of numbers/fractions for accuracy
float getNum(char * num)
{
	puts("here @getNum");
	//for (int p = 0; num[p] != '\0'; p++) printf("%.2f ", num[p]);
	int starter = 0;
	int wanOrTwo = 2;
	int nummy1 = 0;
	int nummy2 = 0;

	for (int i = 0; i < 2; i++)
	{
		nummy1 = 0;
		int digit = 0;
		int *feed = (int *)calloc(1, sizeof(int));

		// shortned if for differenciating before '/' and after
		for (int ii = starter; (i == 0) ? (num[ii] != '\\' && num[ii] != '/') : (num[ii] != '\0'); ii++)
		{
			printf("-%d\n", feed[ii]);
			printf("\n");
			if (ii != 0)
			{
				int *feed = (int *)realloc(ii + 1, sizeof(int));
			}

			feed[digit] = num[ii];

			if (num[ii + 1] == '\0' && i == 0)
			{
				i = 1;
				wanOrTwo = 1;
				break;
			}

			starter = ii + 2;
			digit += 1;
		}

		// converting digits to correct values

		int temp = 0;

		for (int k = (digit - 1); k >= 0; k--)
		{
			nummy1 += feed[temp] * pow(10, k);
			//printf("-%d\n", feed[temp]);
			//printf("\n");
			temp += 1;

		}

		if (i == 0 && wanOrTwo == 2) nummy2 = nummy1;

		if (i == 1)
		{
			if (wanOrTwo == 1)
			{
				return nummy1;
			}
			else if (wanOrTwo == 2)
			{
				return (float)(nummy2 / nummy1);
			}

		}

	}
}



int main()
{
	char test[100];

	int choice = 0;
	printf("Choose: ");
	scanf_s("%d", &choice);
	printf("\n");

	fgets(test, 100, stdin);









	/*
	int row = 0;
	int column = 0;
	int newLine = 0;
	int input = 0;

	printf("Please enter matrix row length: ");
	scanf_s("%d", &row);
	printf("\n");
	printf("Please enter matrix column length: ");
	scanf_s("%d", &column);
	printf("\n");

	int size = (row * column);

	// main matrix without solutions
	float * matrix;
	matrix = (float *)calloc(size, sizeof(float));


	printf("Please enter matrix values (top left -> bottom right):\n\n");

	for (int i = 0; i < size; i++)
	{

		if (newLine == column)
		{

			//printf("Solution %d: ", input + 1);
			//scanf_s("%f", &matrixSolution[input]);
			printf("\n");
			newLine = 0;
			//input += 1;
		}
		newLine += 1;

		scanf_s("%f", &matrix[i]);

		if (i == size - 1)
		{

			//printf("Solution %d: ", input + 1);
			//scanf_s("%f", &matrixSolution[input]);
			printf("\n");
		}
	}

	for (int i = 0; i < size; i++)

	{
		printf("%.2f ", matrix[i]);

		if (((i + 1) % row == 0) && (i / row) != (i + 1 / row)) printf("\n");

	}
		
	float *testMat = smallCopyKat(matrix, row, 2);
	printf("\n");


	for (int i = 0; i < (row-1)*(row-1); i++)

	{
		printf("%.2f ", testMat[i]);

		if (((i + 1) % row-1 == 0) && ((i / row - 1) != (i + 1 / row - 1))) printf("\n");

	}

	printf("Determinant for 2x2 mat is: %.2f", deter(matrix, row));
	*/

}
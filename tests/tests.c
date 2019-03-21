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





int main()
{

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

}
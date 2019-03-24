#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//===================================================================================================
/// structs

typedef struct answerNode
{
	int level;
	struct answerNode * next;

}answerNode;

typedef struct nList
{
	answerNode * head;
	answerNode * butt;

}nLIST;

//==================================================================================================
/// function declerations

// main functions
void paintMatrix(int row, int column, float *matrix, float *matrixSolution, int mode);
float gaussush(int row, int column, float *matrix, float *matrixSolution, float *matrixInverted, int *isHole);
float deter(float *matrix, int size);
float *copyMat(float *matrix, int size);
float *deterCopyMat(float *matrix, int size, int current);
float getNum(char * num, int * isHole);


// nodes / list functions
answerNode * createNewNode(int level, answerNode * next);
nLIST * createNewList();
int isListEmpty(nLIST * list);
void listPrint(nLIST * list);
int searchList(nLIST * list, int ohiMark);
int sizeList(nLIST * list);

//===================================================================================================
///functions

// 'createNewNode' function creates new 'answerNode', returns pointer to node
answerNode * createNewNode (int level, answerNode * next)
{
	answerNode * newNode = (answerNode *)calloc(1, sizeof(answerNode));

	newNode->level = level;

	newNode->next = next;

	return newNode;
}

// 'createNewList' function creates a new nullified list, returns pointer to list
nLIST * createNewList()
{
	nLIST * newList = (nLIST *)calloc(1, sizeof(nLIST));

	newList->butt = newList->head = NULL;

	return newList;
}

// 'isListEmpty' function for determining list emptyness, returns (1 - empty, 0 - not empty)
int isListEmpty(nLIST * list)
{
	return (list->head == NULL ? 1 : 0);
}

// 'listPrint' function for printing lists
void listPrint(nLIST * list)
{
	answerNode * fart = list->head;

	while (fart != NULL)
	{
		printf("X%d", fart->level);
		fart = fart->next;
		if (fart != NULL) printf(", ");
	}
}


// 'node2Butt' function for adding a node to the butt of the list
void node2Butt(nLIST * list, int level)
{
	answerNode * buttNode = createNewNode(level, NULL);

	if (isListEmpty(list) == 1) 
	{
		list->head = list->butt = buttNode;
	}
	else
	{
		list->butt->next = buttNode;
		list->butt = buttNode;

	}
}

// 'sizeList' function returns lists size 
int sizeList(nLIST * list)
{
	answerNode * muchos = list->head;
	int size = 0;

	while (muchos != NULL)
	{
		muchos = muchos->next;
		size += 1;
	}

	return size;
}



// 'searchList' bool function for finding data in lists, returns (1 - present, 0 - doesn't exist)
int searchList(nLIST * list, int ohiMark)
{
	answerNode * crawler = list->head;

	while (crawler != NULL)
	{
		if (ohiMark == crawler->level) return 1;

		crawler = crawler->next;
	}

	return 0;
}


// 'printMatrix' function for printing (a) main matrix & solutions (mode 1) (b) inverted matrix (mode 2)
void paintMatrix(int row, int column, float *matrix, float *matrixSolution, int mode) 
{
	int newLine = 1;

	for (int i = 0; i < row*column; i++) {

		printf("%.3f\t", matrix[i]);

		if (newLine == column) {

			if		(mode == 1) printf("| %.3f\n", matrixSolution[(i / column)]);
			else if (mode == 2) printf("\n");
			newLine = 0;
		}
		newLine += 1;
	}
	printf("\n\n");
}

// function for copying matrices, returns pointer to array
float *copyMat(float *matrix, int size)
{
	float *meTemp;
	meTemp = (float *)calloc(size*size, sizeof(float));

	for (int i = 0; i < size*size; i++) meTemp[i] = matrix[i];

	return meTemp;
}


// intelligently creates a correct minar matrix for next determinant calculation, returns pointer to array
float *deterCopyMat(float *matrix, int size, int current)
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

// 'deter' function for determining the determinant of a matrix, returns determinant
float deter(float *matrix, int size)
{
	// calculating determinant for base case 2x2
	if (size == 2)
	{
		float deterBase = 0;
		deterBase = (matrix[0] * matrix[3]) - (matrix[1] * matrix[2]);

		//printf("#%d Det: %.2f", size, deterBase);
		//printf("\n");

		return deterBase;
	}

	// operations for NxN matrices (N>2)
	float deterTemp = 0;
	//                            get it?
	for (int c = 0; c < size; c++)
	{
		
		float *nextMat = deterCopyMat(matrix, size, c);

		// simulating correct signage by (i + j) syrome
		if (((c + 1) + 1) % 2 != 0)
		{
			deterTemp += (((-1) * matrix[c]) * (deter(nextMat, size - 1)));
		}
		else
		{
			deterTemp += (matrix[c] * deter(nextMat, size - 1));
		}

		//printf("#%d Det: %.2f", c + 1, deterTemp);
		//printf("\n");
	}

	return deterTemp;

}


// 'gaussush' function for gaussin' around and stuff
float gaussush(int row, int column, float *matrix, float *matrixSolution, float *matrixInverted, int *isHole)
{
	float determinant = 0;
	if (isHole == 0)
	{
		if (row == column)
		{
			float *deterMat = copyMat(matrix, row);
			determinant = deter(deterMat, row);
		}

	}
	// calculating the determinant if matrix is square
	
	printf("\n\n");
	paintMatrix(row, column, matrix, matrixSolution, 1);

	int doneDone = 0;
	int rowwer = 0;
	int rowwerCheck = 0;
	int rowSwap = 0;
	int done = 0;
	int move = 1;

	//-----------------------------------------------------------------------------------------------------------------------------------

	// stage 1
	// row reduction logic

	for (int i = 0; i < row; i++) {

		done = 0;

		// row check
		int currentRow = 0;
		int targetRow = 1;

		if (matrix[(i * column) + i] != 1 && matrix[(i * column) + i] != 0) 
		{

			// current row
			currentRow = i;

			// swap mechanism loop
			for (int j = i + 1; j < row; j++) 
			{

				// first checking if 1 in a different row exists for swapping

				if (matrix[(j * column) + i] == 1 && done == 0) 
				{
					//printf("here1\n");
					// row to swap with
					targetRow = j;

					float * swap;
					swap = (float *)calloc(column, sizeof(float));

					// swap mechanism main matrix
					for (int s = 0; s < column; s++) swap[s] = matrix[(currentRow * column) + s];
					for (int s = 0; s < column; s++) matrix[(currentRow * column) + s] = matrix[(targetRow * column) + s];
					for (int s = 0; s < column; s++) matrix[(targetRow * column) + s] = swap[s];

					for (int format = 0; format < column; format++) swap[format] = 0;

					// swap mechanism inverted matrix
					for (int s = 0; s < column; s++) swap[s] = matrixInverted[(currentRow * column) + s];
					for (int s = 0; s < column; s++) matrixInverted[(currentRow * column) + s] = matrixInverted[(targetRow * column) + s];
					for (int s = 0; s < column; s++) matrixInverted[(targetRow * column) + s] = swap[s];

					// swap mechanism for solutions
					float solutionSwap = matrixSolution[j];
					matrixSolution[j] = matrixSolution[i];
					matrixSolution[i] = solutionSwap;

					printf("R%d <-> R%d\n\n\n", j + 1, i + 1);
					paintMatrix(row, column, matrix, matrixSolution, 1);
					free(swap);
					move += 1;
					done = 1;
				}

			}

			if (done == 0) 
			{
				//printf("here11\n");
				targetRow = currentRow;

				// difference for zero-ing in values under main diagonal
				float diff = matrix[(currentRow * column) + i];

				for (int s = 0; s < column; s++) 
				{

					// main matrix division
					matrix[(targetRow * column) + s] *= pow(diff, -1);

					// inverted matrix division
					matrixInverted[(targetRow * column) + s] *= pow(diff, -1);

					done = 1;

				}// solution matrix division
				matrixSolution[targetRow] *= pow(diff, -1);

				printf("R%d <- (%.2f * R%d)\n\n\n", targetRow + 1, (float)pow(diff, -1), targetRow + 1);
				paintMatrix(row, column, matrix, matrixSolution, 1);
				done = 1;
				move += 1;
			}

		}
		else if (matrix[(i * column) + i] == 1) 
		{
			//printf("here2\n");
			currentRow = i;

			for (int j = i + 1; j < row; j++) 
			{

				float diff = matrix[(j * column) + i];

				if (matrix[(j * column) + i] != 0) 
				{
					//printf("here22\n");
					targetRow = j;
					// difference for zero-ing in values under main diagonal
					
					for (int s = 0; s < column; s++) 
					{

						if (diff > 0) 
						{

							// main matrix
							matrix[(targetRow * column) + s] -= (diff * matrix[(currentRow * column) + s]);

							// inverted matrix
							matrixInverted[(targetRow * column) + s] -= (diff * matrixInverted[(currentRow * column) + s]);
						}

						if (diff < 0) 
						{

							// main matrix
							matrix[(targetRow * column) + s] += (-diff * matrix[(currentRow * column) + s]);

							// inverted matrix
							matrixInverted[(targetRow * column) + s] += (-diff * matrixInverted[(currentRow * column) + s]);
						}
					}
					
					if (diff > 0) 
					{

						printf("R%d <- R%d - (%.2f * R%d)\n\n\n", j + 1, j + 1, diff, i + 1);

						// solution matrix
						matrixSolution[targetRow] -= (diff * matrixSolution[currentRow]);

						paintMatrix(row, column, matrix, matrixSolution, 1);

					}
					else if (diff < 0) 
					{

						printf("R%d <- R%d + -(%.2f * R%d)\n\n\n", j + 1, j + 1, diff, i + 1);

						// solution matrix
						matrixSolution[targetRow] += (-diff * matrixSolution[currentRow]);

						paintMatrix(row, column, matrix, matrixSolution, 1);
					}

					done = 1;
					move += 1;
				}
			}

		}
		else if (matrix[(i * column) + i] == 0) 
{
			//printf("here3\n");
			// current row
			currentRow = i;

			for (int j = i + 1; j < row; j++) 
			{

				// first checking if 1 in a different row exists for swapping
				if (done == 0) 
				{

					if (matrix[(j * column) + i] != 0) 
					{
						//printf("here33\n");
						// row to swap with
						targetRow = j;

						float * swap;
						swap = (float *)calloc(column, sizeof(float));
						int digit = 0;

						// swap mechanism main matrix
						for (int s = 0; s < column; s++) swap[s] = matrix[(currentRow * column) + s];
						for (int s = 0; s < column; s++) matrix[(currentRow * column) + s] = matrix[(targetRow * column) + s];
						for (int s = 0; s < column; s++) matrix[(targetRow * column) + s] = swap[s];

						for (int format = 0; format < column; format++) swap[format] = 0;

						// swap mechanism inverted matrix
						for (int s = 0; s < column; s++) swap[s] = matrixInverted[(currentRow * column) + s];
						for (int s = 0; s < column; s++) matrixInverted[(currentRow * column) + s] = matrixInverted[(targetRow * column) + s];
						for (int s = 0; s < column; s++) matrixInverted[(targetRow * column) + s] = swap[s];

						// swap mechanisem for solutions
						float solutionSwap = matrixSolution[j];
						matrixSolution[j] = matrixSolution[i];
						matrixSolution[i] = solutionSwap;

						printf("R%d <-> R%d\n\n\n", j + 1, i + 1);
						paintMatrix(row, column, matrix, matrixSolution, 1);
						free(swap);

						done = 1;
						move += 1;
					}

				}
				else 
				{


				}

			}

		}


		if (done == 1) i -= 1;
		if (((i + 1) * column) + (i + 1) > (row * column - 1)) break;

	}
	//-----------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------

	// stage 2
	// upper row reduction logic

	// across main loop
	for (int across = column - 1; across > 0; across--) 
	{

		//making sure subtracting is even available
		if (matrix[(across * column) + across] == 1) 
		{

			// current column zero-ing space
			for (int up = across - 1; up >= 0; up--) 
			{

				// if value above current across position isn't 0 - zero it
				if (matrix[(up * column) + across] != 0) 
				{

					float diff = matrix[(up * column) + across];

					// line change calculator
					for (int s = 0; s < column; s++) 
					{

						if (diff >= 0) 
						{

							// main matrix
							matrix[(up * column) + s] -= (diff * matrix[(across * column) + s]);

							// inverted matrix
							matrixInverted[(up * column) + s] -= (diff * matrixInverted[(across * column) + s]);

						}
						else if (diff < 0) 
						{

							// main matrix
							matrix[(up * column) + s] += (-diff * matrix[(across * column) + s]);

							// inverted matrix
							matrixInverted[(up * column) + s] -= (diff * matrixInverted[(across * column) + s]);

						}
						

					}

					if (diff >= 0) 
					{

						printf("R%d <- R%d - (%.2f * R%d)\n\n\n", up + 1, up + 1, diff, across + 1);
						matrixSolution[up] -= (diff * matrixSolution[across]);
					}
					else if (diff < 0) 
					{

						printf("R%d <- R%d + -(%.2f * R%d)\n\n\n", up + 1, up + 1, diff, across + 1);
						matrixSolution[up] -= (diff * matrixSolution[across]);
					}

					move += 1;
					paintMatrix(row, column, matrix, matrixSolution, 1);
				}
			}
		}
		
	}
	
	//-----------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------

	// step 3
	// matrix solutions and conclusions


	// solutions:

	// dynamicly build array for storing known free elements
	int * freeAnStore;
	freeAnStore = (int *)calloc(column, sizeof(int));

	nLIST * answerList = createNewList();


	int zeRow = 0;
	int zeRowCount = 0;

	for (int Q = 0; Q < row; Q++) 
	{

		for (int QQ = 0; QQ < column; QQ++) 
		{

			if (matrix[(Q * column) + QQ] == 0) zeRowCount += 1;
		}

		if (zeRowCount == column && matrixSolution[Q] != 0) zeRow += 1;
		zeRowCount = 0;
	}

	if (zeRow == 0) 
	{
		printf("===============================================");
		printf("\n\nYour solution set is:\n\n");
		printf("S = { ");

		// loop for each row calculation (row length)
		for (int s = 0; s < row; s++) 
		{

			if (matrixSolution[s] != 0) printf("%.3f", matrixSolution[s]);

			// nested loop for scanning the whole row (column length)
			for (int ss = 0; ss < column; ss++) 
			{

				// making sure across values aren't printed (as solutions are per column)
				if ((s * column) + ss != (s * column) + s) 
				{

					// printing only for non 0 elements
					if (matrix[(s * column) + ss] != 0) 
					{

						// marking free elements

						freeAnStore[ss] = 1;
						
						if (isListEmpty(answerList) == 1)
						{
							//printf("hi1\n");
							answerList->head = createNewNode(ss + 1, NULL);
							//printf("hi2\n");
							
						}
						else
						{
							if (answerList->butt == NULL)
							{
								if (answerList->head->level != ss + 1)
								{
									answerList->butt = createNewNode(ss + 1, NULL);
									answerList->head->next = answerList->butt;

								}
								
								//listPrint(answerList);
							}
							else
							{
								if(searchList(answerList, ss + 1) == 0) node2Butt(answerList, ss + 1);
							}

						}


						if (matrix[(s * column) + ss] > 0) 
						{

							if (matrix[(s * column) + ss] != 1) printf(" - %.3f*X%d", matrix[(s * column) + ss], ss + 1);
							else							   printf(" + X%d", ss + 1);
						}
						else 
						{

							if (matrix[(s * column) + ss] != 1) printf(" + %.3f*X%d", (-1 * matrix[(s * column) + ss]), ss + 1);
							else							   printf(" + X%d", ss + 1);

						}
					}
				}
			}

			// exit notes (like free elements)
			if (s != row - 1) 
			{
				
				//for (int i = 0; i < column; i++) 
				//{

				//	if (freeAnStore[i] == 1) printf(", X%d", i + 1);
				//}

				printf(", ");
			}
			else 
			{
				if(isListEmpty(answerList) == 0) printf(", ");
			}

		}
		listPrint(answerList);
		if (isListEmpty(answerList) == 0)
		{
			printf("  [ ");
			listPrint(answerList);
			printf(" in R ]");
		}
			
		printf(" }\n");
	}
	else 
	{

		printf("===============================================");
		printf("\n\nNo solution available.\n");
	}

	//-----------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------
	// reversability check

	int acrossCheck1 = column;
	int acrossCheck0 = 0;
	int triZero = (row * (row - 1)) / 2;

	for (int i = 0; i < column; i++) 
	{

		// across values
		if (matrix[(i * column) + i] == 1) 
		{

			acrossCheck1 -= 1;
			// searching for zeros (not including you)
			for (int j = i + 1; j < row; j++) 
			{

				if ((matrix[(j * column) + i]) == 0) triZero -= 1;

			}

		}
		else if (matrix[(i * column) + i] == 0) 
		{

			acrossCheck0 += 1;
		}
	}

	printf("\n===============================================\n\n");

	if (row == column && isHole == 0) printf("The determinant of your original matrix is: %.2f\n", determinant);

	printf("\n===============================================\n\n");

	// determining reversability type
	if (triZero == 0 && row == column) 
	{

		if (acrossCheck1 == 0 && row == column) 
		{

			printf("Your matrix is reversable - ");

			if (acrossCheck1 == 0) 
			{

				if (row == column) printf("'Identity Matrix (I%d)':\n\n", row);
				else			  printf("'Diagonal Matrix':\n\n");

			}
			else printf("'Upper Triangular':\n");

			paintMatrix(row, column, matrixInverted, matrixSolution, 2);
		}
		
	}
	// reversableness notes
	if (((row == column) && (acrossCheck0 != 0 || acrossCheck1 != 0)) || (row != column))															  printf("Your matrix is NOT reversable ");

	if (row != column)																																  printf("(%d x %d - not square)\n\n", row, column);
	if (((row == column) && (acrossCheck0 != 0 || acrossCheck1 != 0)))																				  printf("(determinant = %.1f)\n\n", determinant);

	printf("===============================================\n");

	return 0;
}


// 'getNum' function for translating char input of numbers/fractions for accuracy
float getNum(char * num, int *isHole)
{

	int starter = 0;
	int wanOrTwo = 2;
	float nummy1 = 0;
	float nummy2 = 0;
	float sign = 1;

	for (int i = 0; i < 2; i++)
	{
		nummy1 = 0;
		int digit = 0;
		float *feed = (float *)calloc(100, sizeof(float));


		// shortned if for differenciating before '/' and after
		for (int ii = starter; (i == 0) ? (num[ii] != '\\' && num[ii] != '/') : (num[ii] != '\0'); ii++)
		{

			if (ii == 0 && i == 0)
			{
				if (num[0] == '-')
				{
					sign = -1;
					ii += 1;
				}
				
			}

			feed[digit] = (float)(num[ii] - 48);
			


			if (num[ii + 1] == '\0' && i == 0)
			{
				i = 1;
				wanOrTwo = 1;
				break;
			}

			if((num[ii + 1] == '\\' || num[ii + 1] == '/') && wanOrTwo == 2) starter = ii + 2;
			if(num[ii + 1] != '\0') digit += 1;
		}

		// converting digits to correct values

		int temp = 0;

		for (int k = digit - 1; k >= 0; k--)
		{
			nummy1 += feed[temp] * pow(10, k);
			temp += 1;
			
		}

		if (i == 0 && wanOrTwo == 2) nummy2 = nummy1;

		if (i == 1)
		{
			if (wanOrTwo == 1)
			{
				return nummy1 * sign;
			}
			else if (wanOrTwo == 2)
			{
				if (*isHole == 0) if ((int)(nummy2 / nummy1) != (nummy2 / nummy1)) *isHole = 1;

				return (float)((nummy2 / nummy1) * sign);
			}

		}

	}
}



//=======================================================================================================================================================================================================

/// main

int main() {

	printf("----------------------------------------\n");
	printf("|            Matrix Wizard             |\n");
	printf("----------------------------------------\n");


		int row = 0;
		int column = 0;
		int newLine = 0;
		int input = 0;
		int choice = 0;

		int * isHole;
		isHole = 0;

		printf("-----------------------------------\n");
		printf("| What would you like to do?:     |\n");
		printf("-----------------------------------\n");
		printf("| [1] Gaussian Rating             |\n");
		printf("| [2] Operations On Matrices      |\n");
		printf("-----------------------------------\n\n");

		scanf_s("%d", &choice);

		if (choice == 1) 
		{

			printf("Please enter matrix row length: ");
			scanf_s("%d", &row);
			printf("\n");
			printf("Please enter matrix column length: ");
			scanf_s("%d", &column);

			getchar();
			printf("\n");

			printf("Please enter matrix values (top left -> bottom right):\n\n");

			int size = (row * column);

			// main matrix without solutions
			float * matrix = (float *)calloc(size, sizeof(float));

			// matrix solution array
			float * matrixSolution = (float *)calloc(row, sizeof(float));

			// fully rated matrix for finding the opposite matrix (if one exists)
			float * matrixInverted = (float *)calloc(size, sizeof(float));
			for (int i = 0; i < row; i++) matrixInverted[(i * column) + i] = 1;


			for (int i = 0; i < size; i++) 
			{
				// initial input array initialized every loop
				char *chariZard = (char *)calloc(200, sizeof(char));

				if (newLine == column) 
				{
					printf("Solution %d: ", input + 1);
					fgets(chariZard, 200, stdin);
					matrixSolution[input] = getNum(chariZard, &isHole);
					printf("\n");

					newLine = 0;
					input += 1;
				}
				newLine += 1;

				//for (int p = 0; p < size; p++) printf("%.2f ", matrix[p]);
				//chariZard[0] = '\0';


				fgets(chariZard, 200, stdin);
				matrix[i] = getNum(chariZard, &isHole);

				//scanf_s("%f", &matrix[i]);

				if (i == size - 1) 
				{

					printf("Solution %d: ", input + 1);
					fgets(chariZard, 200, stdin);
					matrixSolution[input] = getNum(chariZard, &isHole);
					printf("\n");
				}
			}
			printf("\n\n");
			printf("Gauss Elimination Steps:\n");
			printf("===============================================\n\n");
			gaussush(row, column, matrix, matrixSolution, matrixInverted, isHole);


			free(matrix);
			free(matrixSolution);
			free(matrixInverted);

		}



	system("pause");

	return (0);
}
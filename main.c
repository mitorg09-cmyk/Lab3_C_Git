#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** CreateMatrix(size_t row, size_t col, int rangeA, int rangeB);
void ClearMatrix(int*** matrix, size_t row);
int PrintMatrix(int** matrix, size_t row, size_t col);
int TranspsMx(int*** ptrMatrix, size_t* row, size_t* col);
int** SumMx(int** mx1, int** mx2, size_t row1, size_t col1, size_t row2, size_t col2);

int main()
{
    srand(time(0));

    // For create matrix and print matrix test
    // int** matrix = CreateMatrix(10, 10, -10, 10);
    // PrintMatrix(matrix, 10, 10);
    // ClearMatrix(&matrix, 10);

    // int** matrix1 = CreateMatrix(999999999999, 10, -10, 10); // Creating err from row create
    // PrintMatrix(matrix1, 999999999999, 10);
    // ClearMatrix(&matrix1, 999999999999);

    // int** matrix1 = CreateMatrix(99, 99999999999999, -10, 10); // Creating err from col create (matrix cleared)
    // PrintMatrix(matrix1, 99, 99999999999999);
    // ClearMatrix(&matrix1, 99);
    // <--



    // For simple sum matrix test
    // int** matrix = CreateMatrix(10, 10, -10, 10);
    // int** matrix2 = CreateMatrix(10, 10, -10, 10);

    // PrintMatrix(matrix, 10, 10);
    // PrintMatrix(matrix2, 10, 10);

    // int** smMx = SumMx(matrix, matrix2, 10, 10, 10, 10);

    // PrintMatrix(smMx, 10, 10);
    // ClearMatrix(&matrix, 10);
    // ClearMatrix(&matrix2, 10);
    // ClearMatrix(&smMx, 10);
    // <--



    // For sum sparsed matrix test
    // int** matrix = CreateMatrix(10, 10, -10, 10);
    // int** matrix2 = CreateMatrix(10, 10, -10, 10);

    // free(matrix[0]);
    // matrix[0] = NULL;
    // free(matrix2[0]);
    // matrix2[0] = NULL;

    // free(matrix[1]);
    // matrix[1] = NULL;
    // free(matrix2[2]);
    // matrix2[2] = NULL;

    // PrintMatrix(matrix, 10, 10);
    // PrintMatrix(matrix2, 10, 10);

    // int** smMx = SumMx(matrix, matrix2, 10, 10, 10, 10);

    // PrintMatrix(smMx, 10, 10);
    // ClearMatrix(&matrix, 10);
    // ClearMatrix(&matrix2, 10);
    // ClearMatrix(&smMx, 10);
    // <--



    // For full sparsed matrix sum test
    // int** matrix = CreateMatrix(10, 10, -10, 10);
    // int** matrix2 = CreateMatrix(10, 10, -10, 10);

    // for(int i = 0; i < 10; i++)
    // {
    //   free(matrix[i]);
    //   matrix[i] = NULL;
    //   free(matrix2[i]);
    //   matrix2[i] = NULL;
    // }

    // PrintMatrix(matrix, 10, 10);
    // PrintMatrix(matrix2, 10, 10);

    // int** smMx = SumMx(matrix, matrix2, 10, 10, 10, 10);

    // PrintMatrix(smMx, 10, 10);
    // ClearMatrix(&matrix, 10);
    // ClearMatrix(&matrix2, 10);
    // ClearMatrix(&smMx, 10);
    // <--



    // For simple transpose test
    // size_t row = 5, col = 10;
    // int** matrix = CreateMatrix(row, col, -10, 10);

    // PrintMatrix(matrix, row, col);

    // TranspsMx(&matrix, &row, &col);

    // PrintMatrix(matrix, row, col);
    // ClearMatrix(&matrix, row);
    // <--



    // For transpose sparsed matrix test
    // size_t row = 5, col = 10;
    // int** matrix = CreateMatrix(row, col, -10, 10);

    // free(matrix[0]);
    // matrix[0] = NULL;
    // free(matrix[1]);
    // matrix[1] = NULL;
    // free(matrix[2]);
    // matrix[2] = NULL;
    // free(matrix[3]);
    // matrix[3] = NULL;

    // PrintMatrix(matrix, row, col);

    // TranspsMx(&matrix, &row, &col);

    // PrintMatrix(matrix, row, col);
    // ClearMatrix(&matrix, row);
    // <--

    return 0;
}

int** CreateMatrix(size_t row, size_t col, int rangeA, int rangeB)
{
  if(rangeA > rangeB)
  {
    int tmp = rangeA;
    rangeA = rangeB;
    rangeB = tmp;
  }

  int** matrix = (int**)calloc(row, sizeof(int*));
  if(matrix)
  {
    for(int i = 0; (size_t)i < row; i++)
    {
      matrix[i] = (int*)calloc(col, sizeof(int));
      if(!matrix[i])
      {
        ClearMatrix(&matrix, i);
        return  NULL;
      }

      for(int j = 0; (size_t)j < col; j++)
      {
        matrix[i][j] = rand() % (rangeB - rangeA + 1) + rangeA;
      }
    }
  }
  else // For debug
  {
    printf("From row create");
  }

  return matrix;
}

void ClearMatrix(int*** ptrMatrix, size_t row)
{
  if(ptrMatrix && *ptrMatrix)
  {
    for(int i = 0; (size_t)i < row; i++)
    {
      free((*ptrMatrix)[i]);
      (*ptrMatrix)[i] = NULL;
    }
    free(*ptrMatrix);
    *ptrMatrix = NULL;
    printf("Cleared \n"); // For debug
  }
}

int PrintMatrix(int** matrix, size_t row, size_t col)
{
  if(matrix)
  {
    for(int i = 0; (size_t)i < row; i++)
    {
      if(matrix[i])
      {
        for(int j = 0; (size_t)j < col; j++)
        {
          printf("%d ", matrix[i][j]);
        }
        printf("\n");
      }
      else
      {
        printf("NULL \n");
      }
    }
    printf("\n");
    return 0;
  }
  return -1;
}

int TranspsMx(int*** ptrMatrix, size_t* row, size_t* col)
{
  if(!ptrMatrix || !*ptrMatrix || !row || !col)
  {
    return -1;
  }

  int** trspsMx = CreateMatrix(*col, *row, 0, 0);
  if(!trspsMx)
  {
    return 1;
  }

  for(int i = 0; (size_t)i < *row; i++)
  {
    if(!(*ptrMatrix)[i]) for(int j = 0; (size_t)j < *col; j++) trspsMx[j][i] = 0;
    else
    {
      for(int j = 0; (size_t)j < *col; j++) trspsMx[j][i] = (*ptrMatrix)[i][j];
    }
  }

  size_t tmp = *row;
  *row = *col;
  *col = tmp;
  ClearMatrix(ptrMatrix, *col);
  *ptrMatrix = trspsMx;
  return 0;
}

int** SumMx(int** mx1, int** mx2, size_t row1, size_t col1, size_t row2, size_t col2)
{
  if(!mx1 || !mx2)
  {
    return NULL;
  }
  if(row1 != row2 || col1 != col2)
  {
    return NULL;
  }

  int** smMx = CreateMatrix(row1, col1, 0, 0);
  if(!smMx)
  {
    return NULL;
  }

  for(int i = 0; (size_t)i < row1; i++)
  {
    if(mx1[i] && mx2[i])
      for(int j = 0; (size_t)j < col1; j++)
        smMx[i][j] = mx1[i][j] + mx2[i][j];
    else if(mx1[i])
      for(int j = 0; (size_t)j < col1; j++)
        smMx[i][j] = mx1[i][j];
    else if(mx2[i])
      for(int j = 0; (size_t)j < col1; j++)
        smMx[i][j] = mx2[i][j];
    else
      {
        free(smMx[i]);
        smMx[i] = NULL;
      }
  }

  return smMx;
}

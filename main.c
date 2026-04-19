#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** CreateMatrix(size_t row, size_t col, int rangeA, int rangeB);
void ClearMatrix(int*** matrix, size_t row);
int PrintMatrix(int** matrix, size_t row, size_t col);
int TranspsMx(int*** ptrMatrix, size_t row, size_t col);
int** SumMx(int** mx1, int** mx2, size_t row1, size_t col1, size_t row2, size_t col2);

int main()
{
    srand(time(0));

    int** matrix = CreateMatrix(10, 10, -10, 10);
    int** matrix2 = CreateMatrix(10, 10, -10, 10);

    PrintMatrix(matrix, 10, 10);
    PrintMatrix(matrix2, 10, 10);

    int** smMx = SumMx(matrix, matrix2, 10, 10, 10, 10);

    PrintMatrix(smMx, 10, 10);

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

int TranspsMx(int*** ptrMatrix, size_t row, size_t col)
{
  if(!ptrMatrix || !*ptrMatrix)
  {
    return -1;
  }

  int** trspsMx = CreateMatrix(col, row, 0, 0);
  if(!trspsMx)
  {
    return 1;
  }

  for(int i = 0; (size_t)i < row; i++)
  {
    if(!(*ptrMatrix)[i]) for(int j = 0; (size_t)j < col; j++) trspsMx[j][i] = 0;
    else
    {
      for(int j = 0; (size_t)j < col; j++) trspsMx[j][i] = (*ptrMatrix)[i][j];
    }
  }

  ClearMatrix(ptrMatrix, row);
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
  }

  return smMx;
}

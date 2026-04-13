#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** CreateMatrix(size_t row, size_t col, int rangeA, int rangeB);
void clearMatrix(int*** matrix, size_t row);
int printMatrix(int** matrix, size_t row, size_t col);

int main()
{
    srand(time(0));
    int** matrix = CreateMatrix(999, 999999, -10, 10);

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
    for(int i = 0; i < row; i++)
    {
      matrix[i] = (int*)calloc(col, sizeof(int));
      if(!matrix[i])
      {
        clearMatrix(&matrix, i);
        return  NULL;
      }

      for(int j = 0; j < col; j++)
      {
        matrix[i][j] = rand() % (rangeB - rangeA + 1) + rangeA;
      }
    }
  }

  return matrix;
}

void clearMatrix(int*** matrix, size_t row)
{
  if(matrix && *matrix)
  {
    for(int i = 0; i < row; i++)
    {
      free((*matrix)[i]);
      (*matrix)[i] = NULL;
    }
    free(*matrix);
    *matrix = NULL;
    printf("Cleared"); // For debug
  }
}

int printMatrix(int** matrix, size_t row, size_t col)
{
  if(matrix)
  {
    for(int i = 0; i < row; i++)
    {
      if(matrix[i])
      {
        for(int j = 0; j < col; j++)
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
    return 0;
  }
  return 1;
}

#include <stdio.h>
#include <stdlib.h>

int verif(int mat[9][9], int l, int c, int num)
{
    for (int i = 0; i < 9; i++)
        if (mat[l][i] == num)
            return 0;

    for (int i = 0; i < 9; i++)
        if (mat[i][c] == num)
            return 0;

    int ll = l - l % 3;
    int cc = c - c % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (mat[i + ll][j + cc] == num)
                return 0;

    return 1;
}

int sudoku(int mat[9][9], int l, int c)
{

    if (l == 8 && c == 9)
        return 1;

    if (c == 9)
    {
        l++;
        c = 0;
    }

    if (mat[l][c] > 0)
        return sudoku(mat, l, c + 1);

    for (int num = 1; num <= 9; num++)
    {

        if (verif(mat, l, c, num) == 1)
        {
            mat[l][c] = num;

            if (sudoku(mat, l, c + 1) == 1)
                return 1;
        }

        mat[l][c] = 0;
    }
    return 0;
}

int main()
{
    int mat[9][9] = { {5, 3, 0, 0, 7, 0, 0, 0, 0},
                      {6, 0, 0, 1, 9, 5, 0, 0, 0},
                      {0, 9, 8, 0, 0, 0, 0, 6, 0},
                      {8, 0, 0, 0, 6, 0, 0, 0, 3},
                      {4, 0, 0, 8, 0, 3, 0, 0, 1},
                      {7, 0, 0, 0, 2, 0, 0, 0, 6},
                      {0, 6, 0, 0, 0, 0, 2, 8, 0},
                      {0, 0, 0, 4, 1, 9, 0, 0, 5},
                      {0, 0, 0, 0, 8, 0, 0, 7, 9} };
    sudoku(mat, 0, 0);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

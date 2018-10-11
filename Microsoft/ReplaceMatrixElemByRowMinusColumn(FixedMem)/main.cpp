/**
 * An array "int **arr" is given. Implement a function that replaces each element of the
 * array by sum of all elements in the same row minus sum of all elements in the same
 * column: arr[i][j] = Sum(arr[i][k]) - Sum(arr[k][j]) (the summation index is "k")
 *
 * The solution implemented below requires only fixed amount of additional memory
 *
 * The algorithm is the following:
 * 1. calculate the first row:
 *     1) sum up elements of the first row and store the result to variable t1
 *     2) loop through columns:
 *         - sum up elements of the i-th column
 *         - store the result to variable t2
 *         - assign (t1 - t2) to arr[0, i]
 * 2. loop through the remaining rows (assume the loop index is "i"):
 *     1) sum up elements of the i-th row
 *     2) store the result to variable t2
 *     3) variable t1 keeps the sum of the elements of the previous row
 *     4) loop through columns (assume the loop index is "j"):
 *         arr[i, j] = t2 - (t1 - arr[i - 1, j])
 *     5) t1 = t2
 *
 * Clarification: (t1 - arr[i - 1, j]) is equal to the sum of all elements in the j-th
 * row. That's because t1 is equal to the sum of all elements in the row (i - 1), and
 * arr[i - 1, j] was previously calculated to keep (t1 - sum_of_elements_in_row_j)
 */
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

void printMatrix( int **matrix, int m, int n)
{
    if ( !matrix ) return;

    for ( int i = 0; i < m; i++ )
    {
        for ( int j = 0; j < n; j++ )
            cout << setw( 3) << matrix[i][j];

        cout << "\n";
    }
}

void replaceByRowMinusColumn( int **arr, int m, int n)
{
    int t1 = 0, t2 = 0;

    if ( !arr ) return;

    /* Sum up elements of the first row */
    for ( int i = 0; i < n; i++ ) t1 += arr[0][i];

    /* Calculate the first row of the resulting matrix */
    for ( int i = 0; i < n; i++ )
    {
        t2 = 0;

        for ( int j = 0; j < m; j++ ) t2 += arr[j][i];

        arr[0][i] = t1 - t2;
    }

    /* Calculate the remaining rows */
    for ( int i = 1; i < m; i++ )
    {
        t2 = 0;

        for ( int j = 0; j < n; j++ ) t2 += arr[i][j];

        for ( int j = 0; j < n; j++ ) arr[i][j] = t2 - (t1 - arr[i - 1][j]);

        t1 = t2;
    }
}

int main()
{
    const int m = 5, n = 6;
    int matrix[m][n] = {{1, 2 ,3 ,4 ,5, 6},
                        {0, 2, 1, 0, 7, 0},
                        {5, 0, 1, 0, 1, 1},
                        {2, 1, 3, 5, 2, 1},
                        {6, 3, 7, 0, 2, 3}};
    int **mtx = new int*[m];

    for ( int i = 0; i < m; i++ )
    {
        mtx[i] = new int[n];

        for ( int j = 0; j < n; j++ )
            mtx[i][j] = matrix[i][j];
    }

    printMatrix( mtx, m, n);
    replaceByRowMinusColumn( mtx, m, n);
    cout << "After replacement: \n";
    printMatrix( mtx, m, n);

    for ( int i = 0; i < m; i++ ) delete[] mtx[i];

    delete[] mtx;

    return 0;
}

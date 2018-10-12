/**
 * An array "int **arr" is given. Implement a function that replaces each element of the
 * array by sum of all elements in the same row minus sum of all elements in the same
 * column: arr[i][j] = Sum(arr[i][k]) - Sum(arr[k][j]) (the summation index is "k")
 *
 * The solution implemented below requires O(M + N) of additional memory, where M is the
 * number of rows and N is the number of columns of the array
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
    if ( !arr ) return;

    int *rowSumm = new int[m];
    int *columnSumm = new int[n];

    memset( rowSumm, 0, sizeof( int) * m);
    memset( columnSumm, 0, sizeof( int) * n);

    for ( int i = 0; i < m; i++ )
        for ( int j = 0; j < n; j++ )
        {
            rowSumm[i] += arr[i][j];
            columnSumm[j] += arr[i][j];
        }

    for ( int i = 0; i < m; i++ )
        for ( int j = 0; j < n; j++ )
            arr[i][j] = rowSumm[i] - columnSumm[j];

    delete[] rowSumm;
    delete[] columnSumm;
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

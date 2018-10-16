/**
 * Two strings A and B are given. Calculate the minimal cost of transforming A into B by
 * means of Insertion, Deletion, and Substitution of individual symbols. The operations
 * have costs CI, CD, and CS respectively.
 *
 * A good question to an interviewer:
 *     is it also required to calculate the minimal edit sequence (the cheapest sequence
 *     of operations that transforms A into B)?
 */
#include <iostream>
#include <vector>

using namespace std;

int calcDistance( const string A, const string B, int CI, int CD, int CS)
{
    int **dist = new int*[A.size() + 1];

    for ( unsigned i = 0; i < A.size() + 1; i++ )
        dist[i] = new int[B.size() + 1];

    dist[0][0] = 0;

    for ( unsigned j = 1; j <= B.size(); j++ )
        dist[0][j] = dist[0][j - 1] + CI;

    for ( unsigned i = 1; i <= A.size(); i++ )
    {
        dist[i][0] = dist[i - 1][0] + CD;

        for ( unsigned j = 1; j <= B.size(); j++ )
        {
            /* Assume, first "i" symbols of A were converted to first "j" symbols of "B".
               What was the destiny of i-th symbol of A?
                   1) it might have been deleted (and in this case first (i-1) symbols of
                      A were converted to first j symbols of B somehow)
                   2) it might have been converted to j-th symbol of B (and in this case
                      first (i-1) symbols of A were converted to (j-1) symbols of B
                      somehow)
                   3) it might have been converted to one of (j-1) first symbols of B (and
                      in this case j-th symbol of B must have been inserted for sure) */
            dist[i][j] = min( dist[i - 1][j] + CD, dist[i][j - 1] + CI);

            int scost = A[i - 1] == B[j - 1] ? 0 : CS;

            dist[i][j] = min( dist[i][j], dist[i - 1][j - 1] + scost);
        }
    }

    int result = dist[A.size()][B.size()];

    for ( unsigned i = 0; i < A.size() + 1; i++ )
        delete[] dist[i];

    delete[] dist;

    return result;
}

int main()
{
    string A, B;

    cout << "Enter source string: ";
    cin >> A;
    cout << "Enter target string: ";
    cin >> B;
    cout << "Cost of the transformation: " << calcDistance( A, B, 1, 1, 1) << '\n';

    return 0;
}

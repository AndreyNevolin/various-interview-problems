/**
 * An array of numbers is given. Also two numbers T1 < T2 are given. Elements of the array
 * must be reordered (by means of pairwise swapping) in such a way that:
 *     1) first come elements that are smaller than T1
 *     2) then come elements that are bigger or equal to T1 but smaller than T2
 *     3) and finally come elements that are bigger or equal to T2
 * In other words, after reordering the array must consist of three successive groups of
 * numbers: (<T1) (>=T1 && <T2) (>=T2)
 * Restriction: reordering must be done in a single pass through the array
 */
#include <iostream>

using namespace std;

void printArray( int *arr, int size)
{
    if ( !arr ) return;

    for ( int i = 0; i < size; i++ )
        cout << arr[i] << " ";

    cout << "\n";
}

/**
 * The algorithm is the following:
 *     1) traverse the array from left to right
 *     2) the following view of the array is maintained:
 *          - first come elements that are smaller than T1
 *          - next come elements that are bigger of equal to T1 but smaller than T2
 *          - next come elements that were not seen yet
 *          - and finally come elements that are bigger or equal to T2
 *        In other words, the array always looks like this:
 *          (<T1) (>=T1 && <T2) (not seen) (>=T2)
 *     3) in the very beginning all the elements belong to "not seen" group
 *     4) at each traversal step the first element from "not seen" group is taken and put
 *        into one of the other three groups. Moving the element to the second and fourth
 *        groups is trivial. Here is how the element is moved to the first group:
 *          - the element (which is the first element in "not seen" group) is swapped with
 *            the first element of the second group
 *          - the right bound of the first group is moved one element to the right (and
 *            thus the group becomes one element bigger)
 *          - both bounds of the second group are moved one element to the right (and thus
 *            the group remains the same size, but its first element became its last
 *            element)
 */
void reorderArrayElems( int *arr, int size, int T1, int T2)
{
    int firstBEQThanT1 = 0;
    int lastNotSeen = size - 1;
    int current = 0;

    if ( !arr ) return;

    while ( lastNotSeen >= current )
    {
        if ( arr[current] < T1 )
        {
            int temp = arr[firstBEQThanT1];

            arr[firstBEQThanT1++] = arr[current];
            arr[current++] = temp;
        } else if ( arr[current] >= T2 )
        {
            int temp = arr[lastNotSeen];
            arr[lastNotSeen--] = arr[current];
            arr[current] = temp;
        } else
            current++;
    }
}

int main()
{
    const int size = 10;
    int arr[] = {3, 7, 5, 1, 9, 4, 4, 8, 0, 12};
    int T1 = 4, T2 = 7;

    cout << "Initial array: ";
    printArray( arr, size);
    cout << "T1: " << T1 << ", T2: " << T2 << '\n';
    reorderArrayElems( arr, size, T1, T2);
    cout << "After reordering: ";
    printArray( arr, size);

    return 0;
}

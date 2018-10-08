/**
 * Implement a function that searches a value in a sorted rotated array:
 *      int findIndex(int arr[], int length, int val) {}
 * "Sorted rotated" means that the array was first sorted in ascending order and then
 * rotated. For exmaple: [7 11 13 17 23 1 3 5]
 *
 * A good question to the interviewer: can there be duplicates in the array?
 * The solution below assumes there are no duplicates.
 */
#include <iostream>

using namespace std;

int findInBounds( int *arr, int left, int right, int val)
{
    if ( left == right )
        if ( arr[left] != val )
            return -1;
        else
            return left;

    /* Need to be careful here. Calculating "middle" as "(left + right) / 2"
       may result in overflow */
    int middle = left + (right - left) / 2;
    /* Bounds of monotonic half */
    int mono_left = -1, mono_right = -1;
    /* Bounds of the other half (which can also be monotonic) */
    int other_left = -1, other_right = -1;

    if ( arr[left] < arr[middle] )
    {
        mono_left = left; mono_right = middle;
        other_left = middle + 1; other_right = right;
    } else
    {
        mono_left = middle + 1; mono_right = right;
        other_left = left; other_right = middle;
    }

    if ( val >= arr[mono_left] && val <= arr[mono_right] )
        return findInBounds( arr, mono_left, mono_right, val);
    else
        return findInBounds( arr, other_left, other_right, val);
}

int findIndex( int *arr, int sz, int val)
{
    if ( !arr )
        return -1;

    return findInBounds( arr, 0, sz - 1, val);
}

int main()
{
    int arr[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};

    cout << "Index: " << findIndex( arr, 12, 5) << '\n';
}

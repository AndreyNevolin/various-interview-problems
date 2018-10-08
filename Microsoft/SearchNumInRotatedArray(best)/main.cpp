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
    while ( left < right )
    {
        /* Need to be careful here. Calculating "middle" as "(left + right) / 2"
           may result in overflow */
        int middle = left + (right - left) / 2;

        if ( arr[left] < arr[middle] )
        {
            if ( val >= arr[left] && val <= arr[middle] )
                right = middle;
            else
                left = middle + 1;
        } else
        {
            if ( val >= arr[middle + 1] && val <= arr[right] )
                left = middle + 1;
            else
                right = middle;
        }
    }

    if ( arr[left] == val )
        return left;
    else
        return -1;
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

    cout << "Index: " << findIndex( arr, 12, 1) << '\n';

    return 0;
}

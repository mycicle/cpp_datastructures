#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void quicksort(double a[], int L, int R) {
    /*
    We will recursively sort the pivot values of all of the lists we generate
    until they are lists of 1
    */
    if ((R - L) < 1) {
        return; 
    }

    int i = L;
    int j = R;
    int pivotIndex = rand() % (R - L + 1) + L;
    int pivot = a[pivotIndex];

    while (i < j) {
        if (a[i] == a[j]) {
            i++;
            continue;
        }
        while ((a[i] < pivot && i < j)) {
            i++;
        }
        while ((a[j] >= pivot && i < j)) {
            j--;
        }

        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    if ((i - L) > 0) {
        quicksort(a, L, i-1);
    }
    if ((R-j) > 0) {
        quicksort(a, j, R);
    }

    return;
}

void testExampleArrayPermutations(double arr[], double sorted[], int length, int start, int end)
{
    static int count = 0;
    if (count % 1000 == 0)
        cout << "count: " << count << endl;
    if(start==end)
    {
        quicksort(arr, 0, length-1);
        for (int i =0; i < length ;i ++) {
            if (arr[i] != sorted[i]) {
                cout << "UNSORTED ELEMENT" << endl;
                return;
            }
        }
        count ++;
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap(arr[i], arr[start]);
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        testExampleArrayPermutations(arr, sorted, length, start+1, end);
        swap(arr[i], arr[start]);
    }
}

void testExampleArray(double a[], double sorted[], int length) {
    cout << "Original array: ";
    for (int i = 0; i < length; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;

    quicksort(a, 0, length-1);

    cout << "Sorted output: ";
    for (int i = 0; i < length; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;

    bool success = true;
    for (int i = 0; i < length; i ++) {
        if (a[i] != sorted[i]) {
            cout << "Sorted array and input array do not match at element: " << i << endl;
            cout << "Sorted[" << i << "]: " << sorted[i] << endl;
            cout << "input[" << i << "]: " << a[i] << endl;
            success = false;
            break;
        }
    }
    cout << "Successful sorting: " << success << endl;
    cout << endl;

    return;
}
int main() {
    // initialize random seed
    srand(time(NULL));


    double testing[] = {0, 2, 1, 4, 5, 7, 6, 9, 11, 10, 3, 8};
    double testingSorted[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // be careful here, if this array is too long you will run the function tens of millions
    // of times, it will literally do length! operations
    // testExampleArrayPermutations(testing, testingSorted, 12, 0, 11);
    testExampleArray(testing, testingSorted, 12);
    cout << "done sorting" << endl;
    return 0;
}
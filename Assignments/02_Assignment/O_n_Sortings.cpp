#include <iostream>
using namespace std;

void CountingSort(int arr[], int n)
{
    // Step 1: Find the maximum value to know the range
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    int count[100] = {0};
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    int index = 0;
    for (int num = 0; num <= maxVal; num++)
    {
        while (count[num] > 0)
        {
            arr[index] = num;
            index++;
            count[num]--;
        }
    }
}
void BucketSort(int arr[], int n)
{
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    int numBuckets = 10;
    int bucketSize = (maxVal / numBuckets) + 1;

    int buckets[10][20];       // 10 buckets, each can hold up to 20 numbers
    int bucketCount[10] = {0}; // how many numbers are currently in each bucket

    // Step 1: Place each number into the correct bucket
    for (int i = 0; i < n; i++)
    {
        int bucketIndex = arr[i] / bucketSize;
        buckets[bucketIndex][bucketCount[bucketIndex]] = arr[i];
        bucketCount[bucketIndex]++;
    }

    // Step 2: Sort each bucket using simple insertion sort (small buckets, so still fast)
    for (int b = 0; b < numBuckets; b++)
    {
        for (int i = 1; i < bucketCount[b]; i++)
        {
            int key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key)
            {
                buckets[b][j + 1] = buckets[b][j];
                j--;
            }
            buckets[b][j + 1] = key;
        }
    }

    // Step 3: Combine all buckets back into the original array
    int index = 0;
    for (int b = 0; b < numBuckets; b++)
    {
        for (int i = 0; i < bucketCount[b]; i++)
        {
            arr[index] = buckets[b][i];
            index++;
        }
    }
}
void CountSortByDigit(int arr[], int n, int place)
{
    int output[20];
    int count[10] = {0};

    // Count occurrences of each digit (0-9) at this place value
    for (int i = 0; i < n; i++)
    {
        int digit = (arr[i] / place) % 10;
        count[digit]++;
    }

    // Change count[i] so it contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (go backwards to keep it stable)
    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / place) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void RadixSort(int arr[], int n)
{
    // Find the maximum number to know the number of digits
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Do counting sort for every digit place (1s, 10s, 100s, ...)
    for (int place = 1; maxVal / place > 0; place *= 10)
    {
        CountSortByDigit(arr, n, place);
    }
}
void PrintArray(int arr[], int n)
{
    cout << "[";
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
            cout << arr[i] << ", ";
        else
            cout << arr[i];
    }
    cout << " ]" << endl;
}
int main()
{
    int n = 20;
    int original[20] = {12, 45, 3, 67, 23, 89, 5, 34, 78, 1,
                        56, 90, 22, 11, 99, 4, 60, 33, 18, 27};

    int arr1[20], arr2[20], arr3[20];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = original[i];
        arr2[i] = original[i];
        arr3[i] = original[i];
    }

    cout << "Original array: ";
    PrintArray(original, n);

    CountingSort(arr1, n);
    cout << "\nSorted using Counting Sort: ";
    PrintArray(arr1, n);

    BucketSort(arr2, n);
    cout << "Sorted using Bucket Sort: ";
    PrintArray(arr2, n);

    RadixSort(arr3, n);
    cout << "Sorted using Radix Sort: ";
    PrintArray(arr3, n);

    return 0;
}
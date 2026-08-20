#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void countingSort(int arr[], int n)
{
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];

    int *count = new int[maxVal + 1];
    for (int i = 0; i <= maxVal; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    int index = 0;
    for (int i = 0; i <= maxVal; i++)
    {
        while (count[i] > 0)
        {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }

    delete[] count;
}
int getMax(int arr[], int n)
{
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

void countSortForRadix(int arr[], int n, int exp)
{
    int *output = new int[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
}

void radixSort(int arr[], int n)
{
    int maxVal = getMax(arr, n);

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countSortForRadix(arr, n, exp);
}
void insertionSortForBucket(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(int arr[], int n, int maxValue)
{
    int bucketCount = n;
    int **buckets = new int *[bucketCount];
    int *bucketSize = new int[bucketCount];

    for (int i = 0; i < bucketCount; i++)
    {
        buckets[i] = new int[n];
        bucketSize[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int bucketIndex = (arr[i] * bucketCount) / (maxValue + 1);
        buckets[bucketIndex][bucketSize[bucketIndex]] = arr[i];
        bucketSize[bucketIndex]++;
    }

    for (int i = 0; i < bucketCount; i++)
        insertionSortForBucket(buckets[i], bucketSize[i]);

    int index = 0;
    for (int i = 0; i < bucketCount; i++)
    {
        for (int j = 0; j < bucketSize[i]; j++)
        {
            arr[index] = buckets[i][j];
            index++;
        }
    }

    for (int i = 0; i < bucketCount; i++)
        delete[] buckets[i];
    delete[] buckets;
    delete[] bucketSize;
}
void PrintArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter array size: ";
    cin >> n;

    srand(time(0));

    int *original = new int[n];
    for (int i = 0; i < n; i++)
        original[i] = rand() % 10000;

    int *arr1 = new int[n];
    int *arr2 = new int[n];
    int *arr3 = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr1[i] = original[i];
        arr2[i] = original[i];
        arr3[i] = original[i];
    }

    if (n <= 20)
    {
        cout << "\nOriginal Array:\n";
        PrintArray(original, n);
    }

    // Find max value for bucket sort range
    int maxValue = original[0];
    for (int i = 1; i < n; i++)
        if (original[i] > maxValue)
            maxValue = original[i];

    int repetitions = 1;
    if (n < 1000)
        repetitions = 100;
    else if (n < 10000)
        repetitions = 10;

    // ---------------- Counting Sort ----------------
    clock_t start1 = clock();
    for (int r = 0; r < repetitions; r++)
    {
        int *temp = new int[n];
        for (int i = 0; i < n; i++)
            temp[i] = original[i];

        countingSort(temp, n);

        if (r == repetitions - 1)
            for (int i = 0; i < n; i++)
                arr1[i] = temp[i];

        delete[] temp;
    }
    clock_t end1 = clock();
    clock_t ticks1 = end1 - start1;

    // ---------------- Radix Sort ----------------
    clock_t start2 = clock();
    for (int r = 0; r < repetitions; r++)
    {
        int *temp = new int[n];
        for (int i = 0; i < n; i++)
            temp[i] = original[i];

        radixSort(temp, n);

        if (r == repetitions - 1)
            for (int i = 0; i < n; i++)
                arr2[i] = temp[i];

        delete[] temp;
    }
    clock_t end2 = clock();
    clock_t ticks2 = end2 - start2;

    // ---------------- Bucket Sort ----------------
    clock_t start3 = clock();
    for (int r = 0; r < repetitions; r++)
    {
        int *temp = new int[n];
        for (int i = 0; i < n; i++)
            temp[i] = original[i];

        bucketSort(temp, n, maxValue);

        if (r == repetitions - 1)
            for (int i = 0; i < n; i++)
                arr3[i] = temp[i];

        delete[] temp;
    }
    clock_t end3 = clock();
    clock_t ticks3 = end3 - start3;

    if (n <= 20)
    {
        cout << "\nCounting Sort:\n";
        PrintArray(arr1, n);

        cout << "\nRadix Sort:\n";
        PrintArray(arr2, n);

        cout << "\nBucket Sort:\n";
        PrintArray(arr3, n);
    }

    cout << "\nSORTING ALGORITHM PERFORMANCE\n";
    cout << "\nAlgorithm\t\tClock Ticks\n";
    cout << "--------------------------------------------\n";
    cout << "Counting Sort\t\t" << ticks1 << endl;
    cout << "Radix Sort\t\t" << ticks2 << endl;
    cout << "Bucket Sort\t\t" << ticks3 << endl;
    return 0;
}
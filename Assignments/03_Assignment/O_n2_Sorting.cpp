#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void SelectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}
void InsertionSort(int arr[], int n)
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

    clock_t start1 = clock();
    BubbleSort(arr1, n);
    clock_t end1 = clock();
    clock_t ticks1 = end1 - start1;

    clock_t start2 = clock();
    SelectionSort(arr2, n);
    clock_t end2 = clock();
    clock_t ticks2 = end2 - start2;

    clock_t start3 = clock();
    InsertionSort(arr3, n);
    clock_t end3 = clock();
    clock_t ticks3 = end3 - start3;

    if (n <= 20)
    {
        cout << "\nBubble Sort:\n";
        PrintArray(arr1, n);

        cout << "\nSelection Sort:\n";
        PrintArray(arr2, n);

        cout << "\nInsertion Sort:\n";
        PrintArray(arr3, n);
    }
    cout << "\nAlgorithm\t\tClock Ticks\n";
    cout << "--------------------------------------------\n";
    cout << "Bubble Sort\t\t" << ticks1 << endl;
    cout << "Selection Sort\t\t" << ticks2 << endl;
    cout << "Insertion Sort\t\t" << ticks3 << endl;
    return 0;
}
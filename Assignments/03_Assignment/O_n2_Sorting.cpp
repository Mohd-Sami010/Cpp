#include <iostream>
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

    BubbleSort(arr1, n);
    cout << "\nSorted using Bubble Sort: ";
    PrintArray(arr1, n);

    SelectionSort(arr2, n);
    cout << "Sorted using Selection Sort: ";
    PrintArray(arr2, n);

    InsertionSort(arr3, n);
    cout << "Sorted using Insertion Sort: ";
    PrintArray(arr3, n);

    return 0;
}
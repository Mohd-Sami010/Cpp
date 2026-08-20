#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// ---------------- Merge Sort ----------------
void Merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSortHelper(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        MergeSortHelper(arr, left, mid);
        MergeSortHelper(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

void MergeSort(int arr[], int n)
{
    MergeSortHelper(arr, 0, n - 1);
}

// ---------------- Quick Sort ----------------
int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void QuickSortHelper(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        QuickSortHelper(arr, low, pi - 1);
        QuickSortHelper(arr, pi + 1, high);
    }
}

void QuickSort(int arr[], int n)
{
    QuickSortHelper(arr, 0, n - 1);
}

// ---------------- Heap Sort ----------------
void Heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        Heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        Heapify(arr, i, 0);
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
    MergeSort(arr1, n);
    clock_t end1 = clock();
    clock_t ticks1 = end1 - start1;

    clock_t start2 = clock();
    QuickSort(arr2, n);
    clock_t end2 = clock();
    clock_t ticks2 = end2 - start2;

    clock_t start3 = clock();
    HeapSort(arr3, n);
    clock_t end3 = clock();
    clock_t ticks3 = end3 - start3;

    if (n <= 20)
    {
        cout << "\nMerge Sort:\n";
        PrintArray(arr1, n);

        cout << "\nQuick Sort:\n";
        PrintArray(arr2, n);

        cout << "\nHeap Sort:\n";
        PrintArray(arr3, n);
    }
    cout << "\nAlgorithm      Clock Ticks\n";
    cout << "--------------------------------------------\n";
    cout << "Type: Merge Sort" << endl;
    cout << "Ticks: " << ticks1 << endl
         << endl;
    cout << "Type: Quick Sort" << endl;
    cout << "Ticks: " << ticks2 << endl
         << endl;
    cout << "Type: Heap Sort" << endl;
    cout << "Ticks: " << ticks3 << endl
         << endl;

    return 0;
}
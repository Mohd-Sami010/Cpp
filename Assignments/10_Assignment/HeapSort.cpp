#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void maxHeapify(vector<int> &arr, int n, int i)
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
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(vector<int> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, n, i);
    }
}
void minHeapify(vector<int> &arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(vector<int> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        minHeapify(arr, n, i);
    }
}
void heapSortIncreasingUsingMaxHeap(vector<int> arr)
{
    int n = arr.size();
    buildMaxHeap(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);  // move current max to the end
        maxHeapify(arr, i, 0); // restore heap on the reduced array
    }

    cout << "Sorted Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}
void heapSortDecreasingUsingMaxHeap(vector<int> arr)
{
    int n = arr.size();
    buildMaxHeap(arr, n);

    vector<int> result(n);
    int heapSize = n;

    for (int i = 0; i < n; i++)
    {
        result[i] = arr[0]; // current max
        arr[0] = arr[heapSize - 1];
        heapSize--;
        maxHeapify(arr, heapSize, 0);
    }
    // result already holds elements from max to min -> decreasing order

    cout << "Sorted Array: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;
}
void heapSortIncreasingUsingMinHeap(vector<int> arr)
{
    int n = arr.size();
    buildMinHeap(arr, n);

    vector<int> result(n);
    int heapSize = n;

    for (int i = 0; i < n; i++)
    {
        result[i] = arr[0]; // current min
        arr[0] = arr[heapSize - 1];
        heapSize--;
        minHeapify(arr, heapSize, 0);
    }
    // result already holds elements from min to max -> increasing order

    cout << "Sorted Array: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;
}
void heapSortDecreasingUsingMinHeap(vector<int> arr)
{
    int n = arr.size();
    buildMinHeap(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);  // move current min to the end
        minHeapify(arr, i, 0); // restore heap on the reduced array
    }

    cout << "Sorted Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}
int main()
{
    vector<int> originalArray = {15, 16, 9, 8, 4, 6, 2, 18, 1, 11, 21, 26, 29, 20};

    // ---------------- 1. Increasing order using Max Heap ----------------
    {
        clock_t start = clock();
        heapSortIncreasingUsingMaxHeap(originalArray);
        clock_t end = clock();

        cout << "Type: Heap Sort - Increasing Order (Max Heap)" << endl;
        cout << "Ticks: " << (end - start) << endl;
        cout << endl;
    }

    // ---------------- 2. Decreasing order using Max Heap ----------------
    {
        clock_t start = clock();
        heapSortDecreasingUsingMaxHeap(originalArray);
        clock_t end = clock();

        cout << "Type: Heap Sort - Decreasing Order (Max Heap)" << endl;
        cout << "Ticks: " << (end - start) << endl;
        cout << endl;
    }

    // ---------------- 3. Increasing order using Min Heap ----------------
    {
        clock_t start = clock();
        heapSortIncreasingUsingMinHeap(originalArray);
        clock_t end = clock();

        cout << "Type: Heap Sort - Increasing Order (Min Heap)" << endl;
        cout << "Ticks: " << (end - start) << endl;
        cout << endl;
    }

    // ---------------- 4. Decreasing order using Min Heap ----------------
    {
        clock_t start = clock();
        heapSortDecreasingUsingMinHeap(originalArray);
        clock_t end = clock();

        cout << "Type: Heap Sort - Decreasing Order (Min Heap)" << endl;
        cout << "Ticks: " << (end - start) << endl;
        cout << endl;
    }

    return 0;
}
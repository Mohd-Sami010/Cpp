#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int Partition(vector<int> &arr, int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // final position of pivot
}
int QuickSelect(vector<int> &arr, int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivotIndex = Partition(arr, low, high);

    if (k == pivotIndex)
    {
        return arr[k];
    }
    else if (k < pivotIndex)
    {
        return QuickSelect(arr, low, pivotIndex - 1, k);
    }
    else
    {
        return QuickSelect(arr, pivotIndex + 1, high, k);
    }
}
double FindMedian(vector<int> arr)
{
    int n = arr.size();

    if (n % 2 == 1)
    {
        // single middle element
        vector<int> temp = arr;
        int mid = QuickSelect(temp, 0, n - 1, n / 2);
        return (double)mid;
    }
    else
    {
        vector<int> temp1 = arr;
        int mid1 = QuickSelect(temp1, 0, n - 1, n / 2 - 1);

        vector<int> temp2 = arr;
        int mid2 = QuickSelect(temp2, 0, n - 1, n / 2);

        return (mid1 + mid2) / 2.0;
    }
}

int main()
{
    srand((unsigned int)time(0));

    int n;
    cout << "Enter the size of data to generate: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid size. Please enter a positive integer." << endl;
        return 1;
    }
    vector<int> data(n);
    for (int i = 0; i < n; i++)
    {
        data[i] = rand() % 100000; // random values in [0, 99999]
    }
    clock_t startTicks = clock();

    double median = FindMedian(data);

    clock_t endTicks = clock();
    clock_t totalTicks = endTicks - startTicks;

    cout << "\n--- Median Order Statistic (Quick Sort / Quickselect) ---\n";
    cout << "Data size       : " << n << endl;
    cout << "Median found    : " << median << endl
         << endl;
    cout << "Type: Median Order Statistic" << endl;
    cout << "Ticks: " << totalTicks << endl;

    return 0;
}
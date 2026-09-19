#include <iostream>
#include <algorithm>
using namespace std;

struct Activity
{
    int start, finish;
};

// Comparator to sort activities by finish time
bool activityCompare(Activity a1, Activity a2)
{
    return (a1.finish < a2.finish);
}

void printMaxActivities(Activity arr[], int n)
{
    // Step 1: Sort activities by finish time
    sort(arr, arr + n, activityCompare);

    cout << "Selected Activities:\n";

    // First activity always selected
    int i = 0;
    cout << "(" << arr[i].start << ", " << arr[i].finish << ")\n";

    for (int j = 1; j < n; j++)
    {
        // Select activity if its start time
        // is >= finish time of previously selected activity
        if (arr[j].start >= arr[i].finish)
        {
            cout << "(" << arr[j].start << ", " << arr[j].finish << ")\n";
            i = j;
        }
    }
}

int main()
{
    Activity arr[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printMaxActivities(arr, n);
    return 0;
}
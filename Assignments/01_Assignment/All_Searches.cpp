#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 1000000;

struct Student
{
    string name;
    int enrollment;
    int marks;
};
Student students[MAX_SIZE];

string firstNames[10] = {"Mohd", "Arman", "Ayaz", "Lakshay", "Vansh",
                         "Priyanshu", "Bhaumik", "Kartik", "Vinit", "Karampreet"};
string lastNames[10] = {"Sami", "Saifi", "Panchal", "Singh", "Kumar",
                        "Jain", "Vats", "Tiwari", "Chowdhary", "Tyagi"};

void GenerateStudents(int n)
{
    // cout << "Name, Enroll, Marks" << endl;
    for (int i = 0; i < n; i++)
    {
        int f = rand() % 10;
        int l = rand() % 10;
        students[i].name = firstNames[f] + " " + lastNames[l];
        students[i].enrollment = i + 1;
        students[i].marks = rand() % 101;

        // cout << students[i].name << ", " << students[i].enrollment << ", " << students[i].marks << endl;
    }
}

float LinearSearch(int n, int key, int &foundIndex)
{
    clock_t startTime = clock();

    foundIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (students[i].enrollment == key)
        {
            foundIndex = i;
            break;
        }
    }

    clock_t endTime = clock();
    return float(endTime - startTime);
}

float binarySearch(int n, int key, int &foundIndex)
{
    clock_t startTime = clock();

    foundIndex = -1;
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (students[mid].enrollment == key)
        {
            foundIndex = mid;
            break;
        }
        else if (students[mid].enrollment < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    clock_t endTime = clock();
    return float(endTime - startTime);
}
float directSearch(int n, int key, int &foundIndex)
{
    clock_t startTime = clock();

    foundIndex = -1;
    int index = key - 1;
    if (index >= 0 && index < n && students[index].enrollment == key)
    {
        foundIndex = index;
    }

    clock_t endTime = clock();
    return float(endTime - startTime);
}
int main()
{
    srand(time(0)); // seed random number generator using current time

    int n;
    cout << "Enter the size of the dataset (number of students): ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE)
    {
        cout << "Please enter a size between 1 and " << MAX_SIZE << endl;
        return 0;
    }

    GenerateStudents(n);

    // Pick 5 random enrollment numbers to search for
    const int numKeys = 5;
    int keys[numKeys];
    for (int i = 0; i < numKeys; i++)
    {
        keys[i] = (rand() % n) + 1;
    }

    float totalLinear = 0, totalBinary = 0, totalDirect = 0;

    cout << "\n--- Searching " << numKeys << " random keys ---\n";
    for (int i = 0; i < numKeys; i++)
    {
        int key = keys[i];
        cout << "\nSearching for Enrollment Number: " << key << endl;

        int idx1, idx2, idx3;
        float tLinear = LinearSearch(n, key, idx1);
        float tBinary = binarySearch(n, key, idx2);
        float tDirect = directSearch(n, key, idx3);

        cout << "Linear Search : found at index " << idx1
             << " | Time = " << tLinear << " clock ticks" << endl;
        cout << "Binary Search : found at index " << idx2
             << " | Time = " << tBinary << " clock ticks" << endl;
        cout << "Direct Search : found at index " << idx3
             << " | Time = " << tDirect << " clock ticks" << endl;

        totalLinear += tLinear;
        totalBinary += tBinary;
        totalDirect += tDirect;
    }

    cout << "\n--- Average Time Taken (over " << numKeys << " searches) ---\n";
    cout << "Average Linear Search Time : " << (totalLinear / numKeys)
         << " clock ticks" << endl;
    cout << "Average Binary Search Time : " << (totalBinary / numKeys)
         << " clock ticks" << endl;
    cout << "Average Direct Search Time : " << (totalDirect / numKeys)
         << " clock ticks" << endl;

    return 0;
}
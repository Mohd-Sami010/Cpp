#include <iostream>
#include <random>
using namespace std;

int main()
{
    cout << "WELCOME TO NUMBER GUESSING GAME" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 100);

    int randNum = distrib(gen);
    int userNum;
    do
    {
        cout << "Enter number: ";
        cin >> userNum;

        if (userNum > randNum)
            cout << "Chosen number is big" << endl;
        else if (userNum < randNum)
            cout << "Chosen number is small" << endl;

    } while (userNum != randNum);
    cout << "CORRECT" << endl;

    return 0;
}

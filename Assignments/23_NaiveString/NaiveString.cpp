#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    vector<size_t> matches;
    if (pattern.size() <= text.size())
    {
        for (size_t start = 0; start <= text.size() - pattern.size(); ++start)
        {
            size_t offset = 0;
            while (offset < pattern.size() &&
                   text[start + offset] == pattern[offset])
                ++offset;

            if (offset == pattern.size())
                matches.push_back(start);
        }
    }

    if (matches.empty())
    {
        cout << "Pattern not found.\n";
        return 0;
    }

    cout << "Pattern found at starting indices: ";
    for (size_t i = 0; i < matches.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << matches[i];
    }
    cout << '\n';

    return 0;
}
